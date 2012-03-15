texture gDiffuseTexture : DIFFUSE;
sampler2D gDiffuseSampler = 
sampler_state 
{
    Texture = <gDiffuseTexture>;
    FILTER = MIN_MAG_MIP_LINEAR;
    AddressU = Wrap;
    AddressV = Wrap;
};

float gTime;
float gRed;
float gGreen;
float gBlue;

float gAmbientA;
float gAmbientR;
float gAmbientG;
float gAmbientB;

bool  gPlayerPointLight;
float gPlayerPointA;
float gPlayerPointR;
float gPlayerPointG;
float gPlayerPointB;
float gPlayerPointPosX;
float gPlayerPointPosY;

bool  gItem4PointLight;
float gItem4PointA;
float gItem4PointR;
float gItem4PointG;
float gItem4PointB;
float gItem4PointPosX;
float gItem4PointPosY;

bool  gItem1PointLight;
float gItem1PointA;
float gItem1PointR;
float gItem1PointG;
float gItem1PointB;
float gItem1PointPosX;
float gItem1PointPosY;

bool  gItem2PointLight;
float gItem2PointA;
float gItem2PointR;
float gItem2PointG;
float gItem2PointB;
float gItem2PointPosX;
float gItem2PointPosY;

bool  gItem3PointLight;
float gItem3PointA;
float gItem3PointR;
float gItem3PointG;
float gItem3PointB;
float gItem3PointPosX;
float gItem3PointPosY;

float gPlayerPointRadius;
float gItemPointRadius;

struct VS_INPUT
{
	float3 untransformed_pos	: POSITION0;
	float2 untransformed_uv		: TEXCOORD0;
};
struct VS_OUTPUT
{
	float4 pos		: POSITION0;
	float2 uv		: TEXCOORD0;
};
VS_OUTPUT ScreenSpaceQuad(VS_INPUT input)
{
	VS_OUTPUT output;
	
	output.pos = float4( input.untransformed_pos, 1.0f );
	output.uv  = input.untransformed_uv;
	
	return output;
}

//INVERSION
float4 Inversion(VS_OUTPUT input) : COLOR
{
	float4 color = tex2D( gDiffuseSampler, input.uv);
	color.r = 1 - color.r;
	color.g = 1 - color.g;
	color.b = 1 - color.b;
	color.a = 1;
	return color;
}
//BLACK AND WHITE
float4 BlackAndWhite(VS_OUTPUT input) : COLOR
{	
	float4 color = tex2D( gDiffuseSampler, input.uv);
	float value = ( color.r + color.g + color.b )/ 3;
	color.r = value;
	color.g = value;
	color.b = value;
	return color;
}
//SEPHIA
float4 SepiaScale(VS_OUTPUT input) : COLOR
{
	float4 color = tex2D( gDiffuseSampler, input.uv);
	
	float4 outputColor = color;
	outputColor.r = ( color.r * 0.393 ) + ( color.g * 0.769 ) + ( color.b * 0.189 );
	outputColor.g = ( color.r * 0.349 ) + ( color.g * 0.686 ) + ( color.b * 0.168 );
	outputColor.b = ( color.r * 0.272 ) + ( color.g * 0.534 ) + ( color.b * 0.131 );
	return outputColor;
}
//COLOR CYCLE
float4 ColorCycle(VS_OUTPUT input) : COLOR
{
	float4 color = tex2D( gDiffuseSampler, input.uv );
	float value1 = (gRed * color.r ) + ( gRed * color.g ) + ( gRed * color.b );
	float value2 = (gGreen * color.r ) + ( gGreen * color.g ) + ( gGreen * color.b );
	float value3 = (gBlue * color.r ) + ( gBlue * color.g ) + ( gBlue * color.b );
	
	float4 newColor;
	newColor.r = value1;
	newColor.g = value2;
	newColor.b = value3;
	newColor.a = 1.0f;
	return newColor;
}
//TRON
float4 TronLines(VS_OUTPUT input) : COLOR
{
	float4 color = tex2D( gDiffuseSampler, input.uv );
	input.uv.x -= gTime * 0.25f;
	
	if( color.r >= 0.6f && color.b >= 0.6f && color.g <= 0.5f )
	{
	color.r = cos( input.uv.x * 10 ) * gRed;
	//color.g = cos( input.uv.x * 10 ) * gGreen*.3f;
	//color.b = cos( input.uv.x * 10 ) * gBlue;
	color.g = 0.0f;
	color.b = 0.0f;
	color.a = 1.0f;
	}
	return color;
}
//DAY CYCLE
float4 DayCycle(VS_OUTPUT input) : COLOR
{	
	float4 color = tex2D( gDiffuseSampler, input.uv);

	// AMBIENT POINT LIGHT
	float4 gAmbientColor;
	gAmbientColor.a = gAmbientA;
	gAmbientColor.r = gAmbientR;
	gAmbientColor.g = gAmbientG;
	gAmbientColor.b = gAmbientB;
	
	////////////////////////////////////////////////////////
	// PLAYER POINT LIGHT
	////////////////////////////////////////////////////////
	float4 PlayerPointLightColor;	
	if( gPlayerPointLight == true )
	{
		PlayerPointLightColor.a = gPlayerPointA;
		PlayerPointLightColor.r = gPlayerPointR;
		PlayerPointLightColor.g = gPlayerPointG;
		PlayerPointLightColor.b = gPlayerPointB;
		
		float2 PlayerPointLightPos;
		PlayerPointLightPos.x = gPlayerPointPosX;
		PlayerPointLightPos.y = gPlayerPointPosY;
		
		float  PlayerPointLightRadius;
		float2 PlayerVectorBetweenTwo;
		float  PlayerMag;
		float  PlayerRatio;
		
		PlayerVectorBetweenTwo = input.uv - PlayerPointLightPos; 
		PlayerMag = length( PlayerVectorBetweenTwo );
		PlayerPointLightRadius = gPlayerPointRadius;
		PlayerRatio = 1.0f - saturate( PlayerMag / PlayerPointLightRadius );
		PlayerPointLightColor *= PlayerRatio;
	}
	////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////
	
	////////////////////////////////////////////////////////
	// ITEM1 POINT LIGHT
	////////////////////////////////////////////////////////
	float4 Item1PointLightColor = { 0, 0, 0, 0 };	
	
		Item1PointLightColor.a = gItem1PointA;
		Item1PointLightColor.r = gItem1PointR;
		Item1PointLightColor.g = gItem1PointG;
		Item1PointLightColor.b = gItem1PointB;
		
		float2 Item1PointLightPos;
		Item1PointLightPos.x = gItem1PointPosX;
		Item1PointLightPos.y = gItem1PointPosY;
		
		float  Item1PointLightRadius;
		float2 Item1VectorBetweenTwo;
		float  Item1Mag;
		float  Item1Ratio;
		
		Item1VectorBetweenTwo = input.uv - Item1PointLightPos; 
		Item1Mag = length( Item1VectorBetweenTwo );
		Item1PointLightRadius = gItemPointRadius;
		Item1Ratio = 1.0f - saturate( Item1Mag / Item1PointLightRadius );
		Item1PointLightColor *= Item1Ratio;

	
	////////////////////////////////////////////////////////
	// ITEM2 POINT LIGHT
	////////////////////////////////////////////////////////
	float4 Item2PointLightColor = { 0, 0, 0, 0 };	

		Item2PointLightColor.a = gItem2PointA;
		Item2PointLightColor.r = gItem2PointR;
		Item2PointLightColor.g = gItem2PointG;
		Item2PointLightColor.b = gItem2PointB;
		
		float2 Item2PointLightPos;
		Item2PointLightPos.x = gItem2PointPosX;
		Item2PointLightPos.y = gItem2PointPosY;
		
		float  Item2PointLightRadius;
		float2 Item2VectorBetweenTwo;
		float  Item2Mag;
		float  Item2Ratio;
		
		Item2VectorBetweenTwo = input.uv - Item2PointLightPos; 
		Item2Mag = length( Item2VectorBetweenTwo );
		Item2PointLightRadius = gItemPointRadius;
		Item2Ratio = 1.0f - saturate( Item2Mag / Item2PointLightRadius );
		Item2PointLightColor *= Item2Ratio;

	
	////////////////////////////////////////////////////////
	// ITEM3 POINT LIGHT
	////////////////////////////////////////////////////////
	float4 Item3PointLightColor = { 0, 0, 0, 0 };	

		Item3PointLightColor.a = gItem3PointA;
		Item3PointLightColor.r = gItem3PointR;
		Item3PointLightColor.g = gItem3PointG;
		Item3PointLightColor.b = gItem3PointB;
		
		float2 Item3PointLightPos;
		Item3PointLightPos.x = gItem3PointPosX;
		Item3PointLightPos.y = gItem3PointPosY;
		
		float  Item3PointLightRadius;
		float2 Item3VectorBetweenTwo;
		float  Item3Mag;
		float  Item3Ratio;
		
		Item3VectorBetweenTwo = input.uv - Item3PointLightPos; 
		Item3Mag = length( Item3VectorBetweenTwo );
		Item3PointLightRadius = gItemPointRadius;
		Item3Ratio = 1.0f - saturate( Item3Mag / Item3PointLightRadius );
		Item3PointLightColor *= Item3Ratio;
	
	////////////////////////////////////////////////////////
	// ITEM4 POINT LIGHT
	////////////////////////////////////////////////////////
	float4 Item4PointLightColor = { 0, 0, 0, 0 };

		Item4PointLightColor.a = gItem4PointA;
		Item4PointLightColor.r = gItem4PointR;
		Item4PointLightColor.g = gItem4PointG;
		Item4PointLightColor.b = gItem4PointB;
	
		float2 Item4PointLightPos;
		Item4PointLightPos.x = gItem4PointPosX;
		Item4PointLightPos.y = gItem4PointPosY;
	
		float  Item4PointLightRadius;
		float2 Item4VectorBetweenTwo;
		float  Item4Mag;
		float  Item4Ratio;
	
		Item4VectorBetweenTwo = input.uv - Item4PointLightPos; 
		Item4Mag = length( Item4VectorBetweenTwo );
		Item4PointLightRadius = gItemPointRadius;
		Item4Ratio = 1.0f - saturate( Item4Mag / Item4PointLightRadius );
		Item4PointLightColor *= Item4Ratio;
	
	////////////////////////////////////////
	// RENDER EVERYTHING
	////////////////////////////////////////
	return (color * Item4PointLightColor) + (color * Item1PointLightColor) + (color * Item2PointLightColor) + (color * Item3PointLightColor) + (color * PlayerPointLightColor) + ( color * gAmbientColor );
	////////////////////////////////////////
	////////////////////////////////////////
	////////////////////////////////////////
}

technique Invert
{
	pass FirstPass
    {
	vertexShader = compile vs_2_0 ScreenSpaceQuad();
	pixelShader = compile ps_2_0 Inversion();
    }
} 
technique Monochrome
{
	pass FirstPass
    {
	vertexShader = compile vs_2_0 ScreenSpaceQuad();
	pixelShader = compile ps_2_0 BlackAndWhite();
    }
}
technique Sepia
{
	pass FirstPass
    {
	vertexShader = compile vs_2_0 ScreenSpaceQuad();
	pixelShader = compile ps_2_0 SepiaScale();
    }
}
technique ColorLoop
{
	pass FirstPass
    {
	vertexShader = compile vs_2_0 ScreenSpaceQuad();
	pixelShader = compile ps_2_0 ColorCycle();
    }
} 
technique TronEnergy
{
	pass FirstPass
    {
	vertexShader = compile vs_2_0 ScreenSpaceQuad();
	pixelShader = compile ps_2_0 TronLines();
    }
}
technique DayCycleEffect
{
	pass FirstPass
    {
	vertexShader = compile vs_3_0 ScreenSpaceQuad();
	pixelShader = compile ps_3_0 DayCycle();
    }
}