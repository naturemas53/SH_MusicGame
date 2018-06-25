//-----------------------------------------------------------------------------
// File: Blur.fx
//
// The effect file for the Basic Blur HLSL sample.
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// Global variables
//-----------------------------------------------------------------------------
sampler tex0 : register(s0);

float AddU = 2.0f / 1280.0f;
float AddV = 2.0f / 720.0f;


//-----------------------------------------------------------------------------
// pass0 PixelShader Main Function
//-----------------------------------------------------------------------------
float4 PS_P0_Main(float2 UV : TEXCOORD0) : COLOR0
{
	//ADDU　隣のピクセルを参照
	//ADDV  下のピクセルを参照
	//FLOAT２第一引数のADDUプラスは真ん中から右のピクセル-は真ん中の左ピクセルを参照する　
	//第二引数のADDVは縦のピクセルを参照　＋なら下、‐なら上を参照する

	//今回は５×５の強力なぼかしをかける
	float4 color = tex2D(tex0, UV + float2(0.0f, 0.0f)) / 25.0f;

	color += tex2D(tex0, UV + float2(-AddU * 2.0f, -AddV * 2.0f))   / 25.0f;   //左上端
	color += tex2D(tex0, UV + float2(-AddU,        -AddV * 2.0f))   / 25.0f;  //左上端の左から二番目
	color += tex2D(tex0, UV + float2(0.0f, -AddV * 2.0f))           / 25.0f;          //真ん中の一番上
	color += tex2D(tex0, UV + float2(+AddU,        -AddV * 2.0f))   / 25.0f;   //真ん中の一つ右の一番上
	color += tex2D(tex0, UV + float2(+AddU * 2.0f, -AddV * 2.0f))   / 25.0f;  //右上端

	color += tex2D(tex0, UV + float2(-AddU * 2.0f, -AddV))          / 25.0f;         //真ん中の左端の一つ上
	color += tex2D(tex0, UV + float2(-AddU,        -AddV))          / 25.0f;         //真ん中の一つ上の左
	color += tex2D(tex0, UV + float2(0.0f, -AddV))				    / 25.0f;                 //真ん中の一つ上
	color += tex2D(tex0, UV + float2(+AddU,        -AddV))          / 25.0f;         //真ん中の右の上
	color += tex2D(tex0, UV + float2(+AddU * 2.0f, -AddV))		    / 25.0f;         //真ん中の右端の上

	color += tex2D(tex0, UV + float2(-AddU * 2.0f,         0.0f))   / 25.0f;//真ん中の左端
	color += tex2D(tex0, UV + float2(-AddU,                0.0f))   / 25.0f;//真ん中の左
	color += tex2D(tex0, UV + float2(+AddU,                0.0f))   / 25.0f;//真ん中の右
	color += tex2D(tex0, UV + float2(+AddU * 2.0f,         0.0f))   / 25.0f;//真ん中の右端

	color += tex2D(tex0, UV + float2(-AddU * 2.0f, +AddV))          / 25.0f;//左下端の一個上
	color += tex2D(tex0, UV + float2(-AddU,        +AddV))          / 25.0f;//左下端の一個上の右
	color += tex2D(tex0, UV + float2(0.0f, +AddV))                  / 25.0f;//真ん中の下
	color += tex2D(tex0, UV + float2(+AddU,        +AddV))          / 25.0f;//右下端の一個上の左
	color += tex2D(tex0, UV + float2(+AddU * 2.0f, +AddV))          / 25.0f;//右下端の一個上

	color += tex2D(tex0, UV + float2(-AddU * 2.0f, +AddV * 2.0f))   / 25.0f;//左下端
	color += tex2D(tex0, UV + float2(+AddU,        +AddV * 2.0f))   / 25.0f;//左下端から二番目
	color += tex2D(tex0, UV + float2(0.0f, +AddV * 2.0f))           / 25.0f;//真ん中の一番下
	color += tex2D(tex0, UV + float2(+AddU,        +AddV * 2.0f))   / 25.0f;//右下端から２番目
	color += tex2D(tex0, UV + float2(+AddU * 2.0f, +AddV * 2.0f))   / 25.0f;//右下端

	/*color.rgb = (color.r + color.g + color.b) / 3.0f;*/
	

	return color;
}
//-----------------------------------------------------------------------------
// Techniques
//-----------------------------------------------------------------------------
technique Blur
{
	pass P0
	{
		VertexShader = NULL;
		PixelShader = compile ps_3_0 PS_P0_Main();
	}
}