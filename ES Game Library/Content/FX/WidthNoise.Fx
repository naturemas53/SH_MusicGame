//----------------------------------------------------------------------------
// File: WidthNoise.fx 
// 
// The effect file for the Mosaic HLSL sample. 
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
// Global variables 
//----------------------------------------------------------------------------
sampler tex0 : register(s0) = sampler_state {
	MipFilter = LINEAR;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	AddressU = WRAP;
	AddressV = WRAP;
};

float time = 1.0f;
float random = 0.0f;

//----------------------------------------------------------------------------
// pass0 PixelShader Main Function 
//----------------------------------------------------------------------------
float4 PS_P0_Main(float2 UV : TEXCOORD0) : COLOR0
{
	UV.x += sin(UV.y * time * random);

	return color;
}
//----------------------------------------------------------------------------
// Techniques 
//----------------------------------------------------------------------------
technique WidthNoise {
	pass P0
	{
		VertexShader = NULL;
		PixelShader = compile ps_3_0 PS_P0_Main();
	}
}