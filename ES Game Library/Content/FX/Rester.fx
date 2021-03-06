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

	//振幅
	float amplitude = 20.0f;
	//分割
	float division = 1.0f;
	//ゆがみ
	float distortion = 1.0f;
//-----------------------------------------------------------------------------
// pass0 PixelShader Main Function
//-----------------------------------------------------------------------------
float4 PS_P0_Main(float2 UV : TEXCOORD0) : COLOR0
{
	//distortionをたして基点をずらす
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