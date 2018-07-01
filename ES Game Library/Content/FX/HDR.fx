//==============================================================
// 定数
float4x4 World;
float4x4 WView;
float4x4 WVProj;
float4 Diffuse;
float4 Ambient;
float3 Light;
float3 LightVPos;
float3 LightColor;
texture MeshTex;
texture InputTex;
texture BloomTex;
float2 SampleOffset[16];
float SampleWeight[16];
float MinBright;
float ToneScale;
float IntScale;

//==============================================================
// テクスチャサンプラ
sampler MeshSmp=sampler_state {
	Texture=<MeshTex>;
	MipFilter=LINEAR;
	MinFilter=LINEAR;
	MagFilter=LINEAR;
};
sampler InputSmp :register(s0) =sampler_state {
	MipFilter=LINEAR;
	MinFilter=LINEAR;
	MagFilter=LINEAR;
	AddressU=BORDER;
	AddressV=BORDER;
};
sampler BloomSmp=sampler_state {
	Texture=<BloomTex>;
	MipFilter=LINEAR;
	MinFilter=LINEAR;
	MagFilter=LINEAR;
	AddressU=BORDER;
	AddressV=BORDER;
};

//==============================================================
// シェーダ（HDRシーン）

// 頂点シェーダ
void HDRSceneVS(
	float4 pos : POSITION,
	float3 normal : NORMAL,
	float2 mesh_uv : TEXCOORD0,
	out float4 Pos : POSITION,
	out float2 MeshUV : TEXCOORD0,
	out float3 VPos : TEXCOORD1, 
	out float3 VNormal : TEXCOORD2
) {
	// 頂点座標、テクスチャ座標
	Pos=mul(pos, WVProj);
	MeshUV=mesh_uv;

	// 頂点座標のビュー変換
	VPos=mul(pos, WView);
	VNormal=normalize(mul(normal, (float3x3)WView));
}

// ピクセルシェーダ
float4 HDRScenePS(
	float2 MeshUV : TEXCOORD0,
	float3 VPos : TEXCOORD1, 
	float3 VNormal : TEXCOORD2
) : COLOR {
	
	// 頂点からライトへのベクトル
	float3 lp=LightVPos-VPos;

	// 法線とライトの角度、頂点とライトの距離から明るさを計算
	float3 color=Ambient+
		max(0, dot(normalize(lp), VNormal))*LightColor
		/(dot(lp, lp)+1);
	
	// 明るさをテクスチャ色、ディフューズ色と合成
	return float4(tex2D(MeshSmp, MeshUV)*color*Diffuse*IntScale, 1);
}

//==============================================================
// シェーダ（高輝度部分の抽出）
float4 BrightPS(
	float2 UV : TEXCOORD0
) : COLOR {
	float4   color = max(0, tex2D(InputSmp, UV) / IntScale - MinBright);
	//color.r = 0.0f;
	//color.b = 0.0f;
	//color.g = 0.0f;
	//color.a = 1.0f;
	return color;
//	return float4(max(0, tex2D(InputSmp, UV) / IntScale - MinBright).rgb, 1);
}

//==============================================================
// シェーダ（ブルームの作成）
float4 BloomPS(
	float2 UV : TEXCOORD0
) : COLOR {
	float3 color=0;
	for (int i=0; i<15; i++) {
		color+=tex2D(InputSmp, UV+SampleOffset[i])*SampleWeight[i];
	}
	return float4(color, 1);
}

//==============================================================
// シェーダ（最終出力）
float4 FinishPS(
	float2 UV : TEXCOORD0
) : COLOR {
	float3 color=
		tex2D(InputSmp, UV)*ToneScale/IntScale+tex2D(BloomSmp, UV);
	return float4(color, 1);
}

//==============================================================
// テクニック
technique HDRScene {
	pass P0 {
		VertexShader=compile vs_1_1 HDRSceneVS();
		PixelShader=compile ps_2_0 HDRScenePS();
	}
}
technique Bright {
	pass P0 {
		PixelShader=compile ps_2_0 BrightPS();
	}
}
technique Bloom {
	pass P0 {
		PixelShader=compile ps_2_0 BloomPS();
	}
}
technique Finish {
	pass P0 {
		PixelShader=compile ps_2_0 FinishPS();
	}
}

