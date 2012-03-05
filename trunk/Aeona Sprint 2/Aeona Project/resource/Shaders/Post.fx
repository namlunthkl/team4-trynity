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
	input.uv.y -= gTime * 0.25f;
	
	if( color.r >= 0.6f && color.b >= 0.6f && color.g <= 0.5f )
	{
	color.r = cos( input.uv.y * 10 ) * gRed;
	color.g = cos( input.uv.y * 10 ) * gGreen;
	color.b = cos( input.uv.y * 10 ) * gBlue;
	color.a = 1.0f;
	}
	return color;
}
//DAY CYCLE
float4 DayCycle(VS_OUTPUT input) : COLOR
{	
	float4 color = tex2D( gDiffuseSampler, input.uv);

	float4 gAmbientColor;
	gAmbientColor.a = gAmbientA;
	gAmbientColor.r = gAmbientR;
	gAmbientColor.g = gAmbientG;
	gAmbientColor.b = gAmbientB;

		
	float2 pointLightPos;
	float4 pointLightColor;
	float  pointLightRadius;
	
	float2 vectorBetweenTwo;
	float  mag;
	float  ratio;

	pointLightPos.x = 0.5f;
	pointLightPos.y = 0.5f;
	
	vectorBetweenTwo = input.uv - pointLightPos; 
	
	mag = length( vectorBetweenTwo );
	
	pointLightColor.a = 1.0f;
	pointLightColor.r = 1.0f;
	pointLightColor.g = 0.0f;
	pointLightColor.b = 0.0f;
	
	pointLightRadius = .25f;
	
	ratio = 1.0f - saturate( mag / pointLightRadius );
	
	pointLightColor *= ratio;
	
	return (color * pointLightColor) + ( color * gAmbientColor) ;
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
	vertexShader = compile vs_2_0 ScreenSpaceQuad();
	pixelShader = compile ps_2_0 DayCycle();
    }
}