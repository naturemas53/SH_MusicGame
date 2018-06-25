// File: Raster.fx
//
// The effect file for the Raster HLSL sample.
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// Global variables
//-----------------------------------------------------------------------------
sampler tex0 : register(s0) = sampler_state {
	MipFilter = LINEAR;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	AddressU = WRAP;
	AddressV = WRAP;
};

float AddV = 1.0f / 720.0f;

	//êUïù
	float amplitude = 20.0f;
	//ï™äÑ
	float division = 1.0f;
	//Ç‰Ç™Ç›
	float distortion = 1.0f;
//-----------------------------------------------------------------------------
// pass0 PixelShader Main Function
//-----------------------------------------------------------------------------
float4 PS_P0_Main(float2 UV : TEXCOORD0) : COLOR0
{
	//distortionÇÇΩÇµÇƒäÓì_ÇÇ∏ÇÁÇ∑
	UV.x += sin(UV.y * 3.14  *division + distortion) * amplitude;

	
	
	

return tex2D(tex0, UV);
}
//-----------------------------------------------------------------------------
// Techniques
//-----------------------------------------------------------------------------
technique Raster
{
pass P0
	{
		VertexShader = NULL;
		PixelShader = compile ps_3_0 PS_P0_Main();
	}

}