//----------------------------------------------------------------------------
// File: Noise.fx 
// 
// The effect file for the Mosaic HLSL sample. 
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
// Global variables 
//----------------------------------------------------------------------------
sampler tex0 : register(s0);

float Time = 1.0;
float noise_intensity = 0.4f;


float rand(float2 noise_roughness)
{
	return frac(sin(dot(noise_roughness.xy, float2(12.9898, 78.233))) * 43758.5453);
}

//----------------------------------------------------------------------------
// pass0 PixelShader Main Function 
//----------------------------------------------------------------------------
float4 PS_P0_Main(float2 UV : TEXCOORD0) : COLOR0
{
	float4 color = tex2D(tex0, UV);

	float2 pos = UV;
	pos *= sin(Time);
	float r = rand(pos);
	float4 noise = float4(r, r, r, color.a);
	

	//ここでのノイズはhlsl関数　パーリンノイズ（ランダムな値を生成)
	color = lerp(color, noise, noise_intensity);
	//if (color.r >= 0.1f)
	//	color.a = 1.0f;

	return color;
}
//----------------------------------------------------------------------------
// Techniques 
//----------------------------------------------------------------------------
technique Noise {
	pass P0
	{
		VertexShader = NULL;
		PixelShader = compile ps_3_0 PS_P0_Main();
	}
}