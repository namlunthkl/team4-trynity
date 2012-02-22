// application exposed variables
float4x4 gWorld : WORLD;
float4x4 gViewProjection : VIEWPROJECTION;
float4x4 gViewInverse : VIEWINVERSE;



// global direction of the directional light
float3 gLightDir : DIRECTION
< string Object = "DirectionalLight"; >
= { 0, 1, 0.25};



// position of the point light
float3 gLightPos : POSITION
< string Object = "PointLight"; >
= { -1, 3, -1};



// texture to be used
textureCUBE gReflectTexture : ENVMAP;

// the matching sampler
samplerCUBE gReflectSampler = 
sampler_state 
{
    Texture = <gReflectTexture>;
    FILTER = MIN_MAG_MIP_LINEAR;
    AddressU = Wrap;
    AddressV = Wrap;
};



// create vertex shader inputs (must match the vertex declaration in C++)
struct VS_INPUT
{
    float3 untransformed_pos	: POSITION0;
    float3 untransformed_norm	: NORMAL0;
};


// vertex shader outputs
struct VS_OUTPUT
{
    float4 transformed_pos	: POSITION0;
    float3 transformed_norm	: TEXCOORD0;
    float3 world		: TEXCOORD1;
};


// the vertex shader, run once for each vertex
VS_OUTPUT myVertexShader(VS_INPUT input)
{
	VS_OUTPUT output; // what we will output

   	// TODO: compute world vertex position
	float4 worldloc = float4( input.untransformed_pos, 1.0f );
   	float4 worldnrm = float4( input.untransformed_norm, 0.0f );
   	worldloc = mul( worldloc, gWorld );
	output.world	 = worldloc.xyz;


	// TODO: store world space normal for later
	output.transformed_norm = mul( input.untransformed_norm, gWorld );


	// TODO: transforming the incoming world vertex into camera, then clip space.
	output.transformed_pos = mul( worldloc, gViewProjection );


	// send data along to the pixel shader (will be interpolated)
	return output; 
}
// the pixel shader, each rasterized triangle's pixels will run through this 
float4 myPixelShader(VS_OUTPUT input) : COLOR
{
	// TODO: normalize the in coming normal
	float3 lightDir = -normalize( gLightDir );


	// TODO: normalize the light direction (for directional lighting)
	float3 worldNorm = normalize( input.transformed_norm );


	// TODO: normalize the light position (for point lighting)
	float3 lightPos = normalize( gLightPos - input.world );


	// TODO: get the reflect vector to be used for the reflection
	float3 invReflection = reflect( -gViewInverse[2], worldNorm );


	// TODO: 	replace this with your own code. You will need to preform a Dot for each light,
	//			add the lights together, and combine that with the color.
	float4 color;
	color.r = 1;
	color.g = 0.1;
	color.b = 0.5;
	color.a = 1;	

	float4 color2;
	color2.r = 1;
	color2.g = .5;
	color2.b = .5;
	color2.a = .5;

	return float4(( (  saturate(dot(lightDir, worldNorm) * color ) + saturate(dot( lightPos, worldNorm) * color2 ) ) * texCUBE( gReflectSampler, invReflection ).rgb ), 1.0f );


}
// Techniques are read in by the effect framework.
// They allow one to add variation to how a particular shader might be executed. 
technique myTechnique
{
	// Each pass in the technique corresponds to a single iteration over all 
	// verticies sent during a draw call and the subsequently created pixels. 
	// If we had a special effect that required us to draw our geometry and pixels more than once,
	// we could acheive this by adding more passes across our vertex and pixel data.
    pass FirstPass
    {
		// request what vertex and pixel shader are to be used, this can change for each pass.
        vertexShader = compile vs_2_0 myVertexShader();
        pixelShader  = compile ps_2_0 myPixelShader();
		// Setting a few of the many D3D renderstates via the effect framework
	//ShadeMode = Phong; // smooth color interpolation across triangles
        //FillMode = Point; // no wireframes, no point drawing.
        //CullMode = CCW; // cull any clockwise polygons.
    }
}