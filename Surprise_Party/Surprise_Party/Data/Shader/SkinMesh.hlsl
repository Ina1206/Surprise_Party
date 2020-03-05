/***************************************************************************************************
*	SkinMeshCode Version 2.00
*	LastUpdate	: 2019/10/09
*	Auther		: an.
**/
//定義.
#define MAX_BONE_MATRICES (255)

//グローバル.
Texture2D		g_Texture	: register( t0 );	//テクスチャーは レジスターt(n).
SamplerState	g_Sampler	: register( s0 );	//サンプラーはレジスターs(n).


//コンスタントバッファ(メッシュごと).
cbuffer per_mesh		: register( b0 )
{
	matrix g_mW;		//ワールド行列.
	matrix g_mWVP;		//ワールドから射影までの変換行列.
};
//コンスタントバッファ(マテリアルごと).
cbuffer per_material	: register( b1 )
{
	float4 g_Ambient	= float4( 0, 0, 0, 0 );	//アンビエント光.
	float4 g_Diffuse	= float4( 1, 0, 0, 0 );	//拡散反射(色）
	float4 g_Specular	= float4( 1, 1, 1, 1 );	//鏡面反射.
};
//コンスタントバッファ(フレームごと).
cbuffer per_frame		: register( b2 )
{
	float4	g_vEye;				//カメラ位置.
	float4	g_vLightPos;		//ﾗｲﾄ位置.
	matrix	g_mLightRot;		//ﾗｲﾄ回転行列.
	float4	g_fIntensity;		//ﾗｲﾄ強度(明るさ). ※xのみ使用する.
	float4	g_fLightWidth;		//ライト広さ.
	float4	g_vLightColor;		//ライト色.
	float4	g_fAlpha;			//透過値.
	float4	g_vUV;				//UV.
	float4	g_vLightPosWidth;	//ライトの配置幅.
	float4	g_vLightMax;		//ライト最大値.
};
//ボーンのポーズ行列が入る.
cbuffer per_bones		: register( b3 )
{
	matrix g_mConstBoneWorld[MAX_BONE_MATRICES];
};

//スキニング後の頂点・法線が入る.
struct Skin
{
	float4 Pos;
	float3 Norm;
};
//バーテックスバッファーの入力.
struct VSSkinIn
{
	float3 Pos		: POSITION;		//位置.  
	float3 Norm		: NORMAL;		//頂点法線.
	float2 Tex		: TEXCOORD;		//テクスチャー座標.
	uint4  Bones	: BONE_INDEX;	//ボーンのインデックス.
	float4 Weights	: BONE_WEIGHT;	//ボーンの重み.
};

//ピクセルシェーダーの入力（バーテックスバッファーの出力）　
struct PSSkinIn
{
	float4 Pos		: SV_Position;	//位置.
	float3 Norm		: NORMAL;		//頂点法線.
	float2 Tex		: TEXCOORD0;	//テクスチャー座標.
	float3 Normal	: TEXCOORD1;
	float4 PosWorld	: TEXCOORD2;		
	float4 Color	: COLOR0;		//最終カラー（頂点シェーダーにおいての）.
};


//指定した番号のボーンのポーズ行列を返す.
//サブ関数（バーテックスシェーダーで使用）.
matrix FetchBoneMatrix( uint iBone )
{
	return g_mConstBoneWorld[iBone];
}


//頂点をスキニング（ボーンにより移動）する.
//サブ関数（バーテックスシェーダーで使用）.
Skin SkinVert( VSSkinIn Input )
{
	Skin Output = (Skin)0;

	float4 Pos = float4(Input.Pos,1);
	float3 Norm = Input.Norm;
	//ボーン0.
	uint iBone	=Input.Bones.x;
	float fWeight= Input.Weights.x;
	matrix m	=  FetchBoneMatrix( iBone );
	Output.Pos	+= fWeight * mul( Pos, m );
	Output.Norm	+= fWeight * mul( Norm, (float3x3)m );
	//ボーン1.
	iBone	= Input.Bones.y;
	fWeight	= Input.Weights.y;
	m		= FetchBoneMatrix( iBone );
	Output.Pos	+= fWeight * mul( Pos, m );
	Output.Norm	+= fWeight * mul( Norm, (float3x3)m );
	//ボーン2.
	iBone	= Input.Bones.z;
	fWeight	= Input.Weights.z;
	m		= FetchBoneMatrix( iBone );
	Output.Pos	+= fWeight * mul( Pos, m );
	Output.Norm	+= fWeight * mul( Norm, (float3x3)m );
	//ボーン3.
	iBone	= Input.Bones.w;
	fWeight	= Input.Weights.w;
	m		= FetchBoneMatrix( iBone );
	Output.Pos	+= fWeight * mul( Pos, m );
	Output.Norm	+= fWeight * mul( Norm, (float3x3)m );

	return Output;
}

// バーテックスシェーダ.
PSSkinIn VS_Main( VSSkinIn input )
{
	PSSkinIn output;
	Skin vSkinned = SkinVert( input);

	output.Pos	= mul( vSkinned.Pos, g_mWVP );
	output.Norm	= normalize( mul( vSkinned.Norm, (float3x3)g_mW ) );
	output.Tex	= input.Tex;
	output.Color	= g_Ambient;

	output.Normal = mul(vSkinned.Norm, (float3x3)g_mW);
	output.PosWorld = mul(vSkinned.Pos, g_mW);

	return output;
}


// ピクセルシェーダ.
float4 PS_Main( PSSkinIn input ) : SV_Target
{

	float4 AllColor = float4(0.0f, 0.0f, 0.0f, 0.0f);
	for (int light = 0; light < g_vLightMax.x; light++) {
		//ﾗｲﾄ位置.
		float4 vLightPos = g_vLightPos;
		vLightPos.x += (g_vLightPosWidth.x * light) - g_vLightPosWidth.x;
		//ﾗｲﾄﾍﾞｸﾄﾙ:このﾋﾟｸｾﾙからﾗｲﾄ現在座標に向かうﾍﾞｸﾄﾙ.
		float4 vLightVector = normalize(vLightPos - input.PosWorld);
		//視線ﾍﾞｸﾄﾙ:このﾋﾟｸｾﾙから視点座標に向かうﾍﾞｸﾄﾙ.
		float4 vEyeVector = normalize(g_vEye - input.PosWorld);
		//ﾗｲﾄの基準ﾍﾞｸﾄﾙ.
		float4 vLightBaseVector = float4(0.0f, 1.0f, 0.0f, 1.0f);

		//ﾗｲﾄの基準ﾍﾞｸﾄﾙに現在のﾗｲﾄの回転を反映.
		vLightBaseVector = mul(vLightBaseVector, g_mLightRot);


		//環境光　①.
		float4 ambient = g_Ambient;

		//拡散反射光 ②.
		float NL = saturate(dot(input.Norm, vLightVector));
		float4 diffuse =
			(g_Diffuse / 2 + g_Texture.Sample(g_Sampler, input.Tex) / 2)/**NL*/;


		//鏡面反射光 ③.
		float3 reflect = normalize(2.0f * NL * input.Normal - vLightVector);
		float4 specular =
			pow(saturate(dot(reflect, vEyeVector)), 4)*g_Specular;

		//ﾌｫﾝﾓﾃﾞﾙ最終色　①②③の合計.
		float4 Color = ambient + diffuse + specular;
		Color.r *= g_vLightColor.x;
		Color.g *= g_vLightColor.y;
		Color.b *= g_vLightColor.z;

		//ｽﾎﾟｯﾄﾗｲﾄの範囲内と範囲外の境界を滑らかに変化させる.
		float cos = saturate(dot(vLightBaseVector, vLightVector));
		//ｺｰﾝ角度:とりあえず 0.9f.
		if (cos < g_fLightWidth.x) {
			Color *= pow(cos / 3.0f, 12.0f *(0.9f - cos)) * Color;
		}

		//減衰.
		float Distance = length(vLightPos - input.PosWorld);
		//att = 1 ÷ 0 ÷ ( a + b * d + c * d^2 )
		//d:距離
		//a,b,c:定数.
		Color *=
			1.0f / (0.0f + 0.0f * Distance + 0.3f * Distance * Distance);

		//ﾗｲﾄ強度を反映.
		Color *= g_fIntensity.x;

		AllColor += Color;
	}
   //                 1
   // fatt = -------------------
   //        a + b * d + c * d^2
   // fatt :減衰.
   // a,b,c:定数.
   // d    :距離.
	
	return AllColor;
}
