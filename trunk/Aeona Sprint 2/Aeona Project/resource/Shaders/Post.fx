// texture to be used
texture gDiffuseTexture : DIFFUSE;
// the matching sampler
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

float4 ambient = { 0.1f, 0.1f, 0.1f, 1.0f };

// TODO: create vertex shader inputs (must match the vertex declaration in C++)
struct VS_INPUT
{
	float3 untransformed_pos	: POSITION0;
	float2 untransformed_uv		: TEXCOORD0;
};
// TODO: create vertex shader outputs
struct VS_OUTPUT
{
	float4 pos		: POSITION0;
	float2 uv		: TEXCOORD0;
};
// TODO: the vertex shader, run once for each vertex
VS_OUTPUT ScreenSpaceQuad(VS_INPUT input)
{
	VS_OUTPUT output;
	
	output.pos  = float4( input.untransformed_pos, 1.0f );
	output.uv 	= input.untransformed_uv;
	
	return output;
}
// the pixel shader, each rasterized triangle's pixels will run through this 
//Render the image without any effect
float4 PassAlong(VS_OUTPUT input) : COLOR
{
	// return texture color
	return tex2D( gDiffuseSampler, input.uv);
}
//Create the Inversion effect
float4 Inversion(VS_OUTPUT input) : COLOR
{
	// return texture color inverted
	
	float4 color = tex2D( gDiffuseSampler, input.uv);
	color.r = 1 - color.r;
	color.g = 1 - color.g;
	color.b = 1 - color.b;
	color.a = 1;
	return color;
}
//Create the Black and White effect
float4 BlackAndWhite(VS_OUTPUT input) : COLOR
{
	// return texture color flattened
	// convert to greyscale
	// return monochrome	
	float4 color = tex2D( gDiffuseSampler, input.uv);
	float value = ( color.r + color.g + color.b )/ 3;
	color.r = value;
	color.g = value;
	color.b = value;
	return color;
}
//Create the Sepia effect
float4 SepiaScale(VS_OUTPUT input) : COLOR
{
	// return texture color scaled
	float4 color = tex2D( gDiffuseSampler, input.uv);
	
	float4 outputColor = color;
	outputColor.r = ( color.r * 0.393 ) + ( color.g * 0.769 ) + ( color.b * 0.189 );
	outputColor.g = ( color.r * 0.349 ) + ( color.g * 0.686 ) + ( color.b * 0.168 );
	outputColor.b = ( color.r * 0.272 ) + ( color.g * 0.534 ) + ( color.b * 0.131 );
	
	// return sepia
	return outputColor;
}
//Create the ColorCycle effect
float4 ColorCycle(VS_OUTPUT input) : COLOR
{
	// similar to the Black and White effect
	float4 color = tex2D( gDiffuseSampler, input.uv );
	float value1 = (gRed * color.r ) + ( gRed * color.g ) + ( gRed * color.b );
	float value2 = (gGreen * color.r ) + ( gGreen * color.g ) + ( gGreen * color.b );
	float value3 = (gBlue * color.r ) + ( gBlue * color.g ) + ( gBlue * color.b );
	
	// convert to the passed in color values
	float4 newColor;
	newColor.r = value1;
	newColor.g = value2;
	newColor.b = value3;
	newColor.a = 1.0f;
	// return the new outcolor
	return newColor;
}
//Create the TronLines effect
float4 TronLines(VS_OUTPUT input) : COLOR
{
	// check for the magenta color of the texture (1,0,1)
	
	float4 color = tex2D( gDiffuseSampler, input.uv );
	
	input.uv.y -= gTime * 0.25f;
	
	if( color.r >= 0.6f && color.b >= 0.6f && color.g <= 0.5f )
	{
	// convert to the passed in color values
	color.r = cos( input.uv.y * 10 ) * gRed;
	color.g = cos( input.uv.y * 10 ) * gGreen;
	color.b = cos( input.uv.y * 10 ) * gBlue;
	color.a = 1.0f;
	// return the new outcolor
	}
	return color;
}

//Create the EveningTime effect
float4 EveningTime(VS_OUTPUT input) : COLOR
{	
	// return texture color scaled
	float4 color = tex2D( gDiffuseSampler, input.uv);
	
	float4 outputColor = color;
	outputColor.r = ( color.r * 0.10 ) + ( color.g * 0.10 ) + ( color.b * 0.10 );
	outputColor.g = ( color.r * 0.10 ) + ( color.g * 0.10 ) + ( color.b * 0.10 );
	outputColor.b = ( color.r * 0.05 ) + ( color.g * 0.05 ) + ( color.b * 0.05 );
	
	// return sepia
	return outputColor;
}

//Create the NightTime effect
float4 NightTime(VS_OUTPUT input) : COLOR
{	
	// return texture color scaled
	float4 color = tex2D( gDiffuseSampler, input.uv);
	
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
	pointLightColor.g = 1.0f;
	pointLightColor.b = 0.0f;
	
	pointLightRadius = .25f;
	
	//ratio = 1.0f - saturate( mag / pointLightRadius );
	ratio = 1.0f -  mag / pointLightRadius ;
	
	pointLightColor *= ratio;
	
	return (color * pointLightColor) + ( color * ambient ) ;
}
// Techniques are read in by the effect framework.
// They allow one to add variation to how a particular shader might be executed.
technique PassThrough
{
	// Each pass in the technique corresponds to a single iteration over all 
	// verticies sent during a draw call and the subsequently created pixels. 
	// If we had a special effect that required us to draw our geometry and pixels more than once,
	// we could acheive this by adding more passes across our vertex and pixel data.
    pass FirstPass
    {
		// request what vertex and pixel shader are to be used, this can change for each pass.
        vertexShader = compile vs_2_0 ScreenSpaceQuad();
		// TODO: Compile with the correct pixel shader
		pixelShader = compile ps_2_0 PassAlong();
    }
}
technique Invert
{
	pass FirstPass
    {
		// request what vertex and pixel shader are to be used, this can change for each pass.
        vertexShader = compile vs_2_0 ScreenSpaceQuad();
		// TODO: Compile with the correct pixel shader
		pixelShader = compile ps_2_0 Inversion();
    }
} 
technique Monochrome
{
	pass FirstPass
    {
		// request what vertex and pixel shader are to be used, this can change for each pass.
        vertexShader = compile vs_2_0 ScreenSpaceQuad();
		// TODO: Compile with the correct pixel shader
		pixelShader = compile ps_2_0 BlackAndWhite();
    }
}
technique Sepia
{
	pass FirstPass
    {
		// request what vertex and pixel shader are to be used, this can change for each pass.
        vertexShader = compile vs_2_0 ScreenSpaceQuad();
		// TODO: Compile with the correct pixel shader
		pixelShader = compile ps_2_0 SepiaScale();
    }
}
technique ColorLoop
{
	pass FirstPass
    {
		// request what vertex and pixel shader are to be used, this can change for each pass.
        vertexShader = compile vs_2_0 ScreenSpaceQuad();
		// TODO: Compile with the correct pixel shader
		pixelShader = compile ps_2_0 ColorCycle();
    }
} 
technique TronEnergy
{
	pass FirstPass
    {
		// request what vertex and pixel shader are to be used, this can change for each pass.
        vertexShader = compile vs_2_0 ScreenSpaceQuad();
		// TODO: Compile with the correct pixel shader
		pixelShader = compile ps_2_0 TronLines();
    }
}
technique EveningTimeEffect
{
	pass FirstPass
    {
		// request what vertex and pixel shader are to be used, this can change for each pass.
        vertexShader = compile vs_2_0 ScreenSpaceQuad();
		// TODO: Compile with the correct pixel shader
		pixelShader = compile ps_2_0 EveningTime();
    }
}

technique NightTimeEffect
{
	pass FirstPass
    {
		// request what vertex and pixel shader are to be used, this can change for each pass.
        vertexShader = compile vs_2_0 ScreenSpaceQuad();
		// TODO: Compile with the correct pixel shader
		pixelShader = compile ps_2_0 NightTime();
    }
}