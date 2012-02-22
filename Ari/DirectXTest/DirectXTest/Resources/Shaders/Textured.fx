// application exposed variables
float4x4 gWorld : WORLD;
float4x4 gViewProjection : VIEWPROJECTION;

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

// vertex shader inputs (must match the vertex declaration in C++)
struct VS_INPUT
{
    float3 untransformed_pos	: POSITION0;
	float2 uv					: TEXCOORD0;
};
// vertex shader outputs
struct VS_OUTPUT
{
    float4 transformed_pos	: POSITION0;
	float2 uv				: TEXCOORD1;
};
// the vertex shader, run once for each vertex
VS_OUTPUT myVertexShader(VS_INPUT input)
{
	VS_OUTPUT output; // what we will output
   	// TODO: compute world vertex position
	float4 worldloc = float4( input.untransformed_pos, 1.0f );
	// TODO: transform the incoming world vertex into camera, then clip space.
	worldloc = mul(worldloc, gWorld );
	output.transformed_pos = mul( worldloc, gViewProjection );
	// TODO: transfer UVs
	output.uv = input.uv;
	// send data along to the pixel shader (will be interpolated)
	return output; 
}
// the pixel shader, each rasterized triangle's pixels will run through this 
float4 myPixelShader(VS_OUTPUT input) : COLOR
{
	// TODO: return texture color
	return tex2D( gDiffuseSampler, input.uv );
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
		//ShadeMode = GOURAUD; // smooth color interpolation across triangles
        //FillMode = POINT; // no wireframes, no point drawing.
        //CullMode = CCW; // cull any clockwise polygons.
    }
}