//ｸﾞﾛｰﾊﾞﾙ変数.
//ﾃｸｽﾁｬ-は、ﾚｼﾞｽﾀｰ t(n).
Texture2D		g_Texture	: register(t0);
//ｻﾝﾌﾟﾗ-は、ﾚｼﾞｽﾀｰ s(n).
SamplerState	g_SamLinear	: register(s0);

//ｺﾝｽﾀﾝﾄﾊﾞｯﾌｧ.
//ﾒｯｼｭ単位.
cbuffer per_mesh	: register(b0)
{
	matrix	g_mW;	//ﾜｰﾙﾄﾞ行列.
	matrix	g_mWVP;	//ﾜｰﾙﾄﾞ,ﾋﾞｭｰ,ﾌﾟﾛｼﾞｪｸｼｮﾝの合成行列.
};
//ﾏﾃﾘｱﾙ単位.
cbuffer per_material: register(b1)
{
	float4	g_Ambient;	//環境光.
	float4	g_Diffuse;	//拡散反射光.
	float4	g_Specular;	//鏡面反射光.
};
//ﾌﾚｰﾑ単位.
cbuffer per_frame	: register(b2)
{
	float4	g_vCamPos;			//ｶﾒﾗ位置.
	float4	g_vLightPos;		//ﾗｲﾄ位置.
	matrix	g_mLightRot;		//ﾗｲﾄ回転行列.
	float4	g_fIntensity;		//ﾗｲﾄ強度(明るさ). ※xのみ使用する.
	float4	g_fLightWidth;		//ライトの広さ.
	float4	g_vLightColor;		//ライト色.
	float4	g_vAlpha;			//透過値.
	float4	g_vUv;				//UV.
	float4	g_vLightPosWidth;	//ライト配置幅.
	float4	g_vLightMax;		//ライト最大値.
};

//頂点ｼｪｰﾀﾞの出力ﾊﾟﾗﾒｰﾀ.
struct VS_OUT
{
	float4	Pos		: SV_Position;
	float4	Color	: COLOR;
	float3	Normal	: TEXCOORD0;
	float2	Tex		: TEXCOORD1;
	float4	PosWorld: TEXCOORD2;
};

//---------------------------------------
//	頂点ｼｪｰﾀﾞ.
//---------------------------------------
VS_OUT VS_Main(float4 Pos	: POSITION,
	float4 Norm : NORMAL,
	float2 Tex : TEXCOORD)
{
	VS_OUT Out = (VS_OUT)0;

	//ﾌﾟﾛｼﾞｪｸｼｮﾝ変換(ﾜｰﾙﾄﾞ→ﾋﾞｭｰ→ﾌﾟﾛｼﾞｪｸｼｮﾝ).
	Out.Pos = mul(Pos, g_mWVP);

	//法線をﾓﾃﾞﾙの姿勢に合わせる.
	// (ﾓﾃﾞﾙが回転すれば法線も回転させる必要があるため).
	Out.Normal = mul(Norm, (float3x3)g_mW);

	//ﾜｰﾙﾄﾞ座標系での位置座標.
	Out.PosWorld = mul(Pos, g_mW);

	//ﾃｸｽﾁｬ座標.
	Out.Tex = Tex;

	return Out;
}

//---------------------------------------
//	ﾋﾟｸｾﾙｼｪｰﾀﾞ.
//---------------------------------------
float4 PS_Main(VS_OUT In) : SV_Target
{
	float4 AllColor = float4(0.0f, 0.0f, 0.0f, 0.0f);
	for (int light = 0; light < g_vLightMax.x; light++) {
		//ﾗｲﾄ位置.
		float4 vLightPos = g_vLightPos;
		vLightPos.x += (g_vLightPosWidth.x * light) - g_vLightPosWidth.x;
		//ﾗｲﾄﾍﾞｸﾄﾙ:このﾋﾟｸｾﾙからﾗｲﾄ現在座標に向かうﾍﾞｸﾄﾙ.
		float4 vLightVector = normalize(vLightPos - In.PosWorld);

		//視線ﾍﾞｸﾄﾙ:このﾋﾟｸｾﾙから視点座標に向かうﾍﾞｸﾄﾙ.
		float4 vEyeVector = normalize(g_vCamPos - In.PosWorld);
		//ﾗｲﾄの基準ﾍﾞｸﾄﾙ.
		float4 vLightBaseVector = float4(0.0f, 1.0f, 0.0f, 1.0f);

		//ﾗｲﾄの基準ﾍﾞｸﾄﾙに現在のﾗｲﾄの回転を反映.
		vLightBaseVector = mul(vLightBaseVector, g_mLightRot);

		//環境光　①.
		float4 ambient = g_Ambient;

		//拡散反射光 ②.
		float NL = saturate(dot(In.Normal, vLightVector));
		float4 diffuse =
			(g_Diffuse / 2 + g_Texture.Sample(g_SamLinear, In.Tex) / 2)/**NL*/;

		//鏡面反射光 ③.
		float3 reflect = normalize(2.0f * NL * In.Normal - vLightVector);
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
		float Distance = length(vLightPos - In.PosWorld);
		//att = 1 ÷ 0 ÷ ( a + b * d + c * d^2 )
		//d:距離
		//a,b,c:定数.
		Color *= 1.0f / (0.0f + 0.0f * Distance + 0.3f * Distance * Distance);
		//ﾗｲﾄ強度を反映.
		Color *= g_fIntensity.x;

		AllColor += Color;
	}
	//ベースの色.
	float4 BaseColor = g_Texture.Sample(g_SamLinear, In.Tex) / 1.0f + In.Color / 1.0f;
	AllColor.a = BaseColor.a;
	AllColor.a *= g_vAlpha.x;

	//                 1
	// fatt = -------------------
	//        a + b * d + c * d^2
	// fatt :減衰.
	// a,b,c:定数.
	// d    :距離.

	return AllColor;
}


//============ ﾃｸｽﾁｬ無しの場合 ===============================.
//---------------------------------------
//	頂点ｼｪｰﾀﾞ.
//---------------------------------------
VS_OUT VS_NoTex(float4 Pos		: POSITION,
	float4 Norm : NORMAL)
{
	VS_OUT Out = (VS_OUT)0;

	//ﾌﾟﾛｼﾞｪｸｼｮﾝ変換(ﾜｰﾙﾄﾞ→ﾋﾞｭｰ→ﾌﾟﾛｼﾞｪｸｼｮﾝ).
	Out.Pos = mul(Pos, g_mWVP);

	//法線をﾓﾃﾞﾙの姿勢に合わせる.
	// (ﾓﾃﾞﾙが回転すれば法線も回転させる必要があるため).
	Out.Normal = mul(Norm, (float3x3)g_mW);

	//ﾜｰﾙﾄﾞ座標系での位置座標.
	Out.PosWorld = mul(Pos, g_mW);

	return Out;
}

//---------------------------------------
//	ﾋﾟｸｾﾙｼｪｰﾀﾞ.
//---------------------------------------
float4 PS_NoTex(VS_OUT In) : SV_Target
{
	//ﾗｲﾄ位置.
	float4 vLightPos = g_vLightPos;
	//視線ﾍﾞｸﾄﾙ:このﾋﾟｸｾﾙから視点座標に向かうﾍﾞｸﾄﾙ.
	float4 vEyeVector = normalize(g_vCamPos - In.PosWorld);
	//ﾗｲﾄﾍﾞｸﾄﾙ:このﾋﾟｸｾﾙからﾗｲﾄ現在座標に向かうﾍﾞｸﾄﾙ.
	float4 vLightVector = normalize(vLightPos - In.PosWorld);
	//ﾗｲﾄの基準ﾍﾞｸﾄﾙ.
	float4 vLightBaseVector = float4(0.0f, 1.0f, 0.0f, 1.0f);

	//ﾗｲﾄの基準ﾍﾞｸﾄﾙに現在のﾗｲﾄの回転を反映.
	vLightBaseVector = mul(vLightBaseVector, g_mLightRot);

	//基本色.
	float4 BaseColor = g_Texture.Sample(g_SamLinear, In.Tex) / 1.0f + In.Color / 1.0f;

	//環境光　①.
	float4 ambient = g_Ambient;

	//拡散反射光 ②.
	float NL = saturate(dot(In.Normal, vLightVector));
	float4 diffuse = g_Diffuse * NL;

	//鏡面反射光 ③.
	float3 reflect = normalize(2 * NL * In.Normal - vLightVector);
	float4 specular =
		pow(saturate(dot(reflect, vEyeVector)), 4)*g_Specular;

	//ﾌｫﾝﾓﾃﾞﾙ最終色　①②③の合計.
	float4 Color = ambient + diffuse + specular;

	//ﾗｲﾄ強度を反映.
	Color *= g_fIntensity.x;

	//ｽﾎﾟｯﾄﾗｲﾄの範囲内と範囲外の境界を滑らかに変化させる.
	float cos = saturate(dot(vLightBaseVector, vLightVector));
	//ｺｰﾝ角度:とりあえず 0.9f.
	if (cos < g_fLightWidth.x) {
		Color *= pow(cos / 3.0f, 12.0f *(0.9f - cos)) * Color;
	}

	//減衰.
	float Distance = length(g_vLightPos - In.PosWorld);
	// att = 1 ÷ 0 ÷ ( a + b * d + c * d^2 )
	// d:距離
	// a,b,c:定数.
	Color *=
		1.0f / (0.0f + 0.0f * Distance + 0.3f * Distance * Distance);

	//                 1
	// fatt = -------------------
	//        a + b * d + c * d^2
	// fatt :減衰.
	// a,b,c:定数.
	// d    :距離.

	Color.a *= g_vAlpha.x;


	return Color;
}