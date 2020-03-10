//��۰��ٕϐ�.
//ø���-�́Aڼ޽�� t(n).
Texture2D		g_Texture	: register(t0);
//�����-�́Aڼ޽�� s(n).
SamplerState	g_SamLinear	: register(s0);

//�ݽ����ޯ̧.
//ү���P��.
cbuffer per_mesh	: register(b0)
{
	matrix	g_mW;	//ܰ��ލs��.
	matrix	g_mWVP;	//ܰ���,�ޭ�,��ۼު���݂̍����s��.
};
//��رْP��.
cbuffer per_material: register(b1)
{
	float4	g_Ambient;	//����.
	float4	g_Diffuse;	//�g�U���ˌ�.
	float4	g_Specular;	//���ʔ��ˌ�.
};
//�ڰђP��.
cbuffer per_frame	: register(b2)
{
	float4	g_vCamPos;			//��׈ʒu.
	float4	g_vLightPos;		//ײĈʒu.
	matrix	g_mLightRot;		//ײĉ�]�s��.
	float4	g_fIntensity;		//ײċ��x(���邳). ��x�̂ݎg�p����.
	float4	g_fLightWidth;		//���C�g�̍L��.
	float4	g_vLightColor;		//���C�g�F.
	float4	g_vAlpha;			//���ߒl.
	float4	g_vUv;				//UV.
	float4	g_vLightPosWidth;	//���C�g�z�u��.
	float4	g_vLightMax;		//���C�g�ő�l.
};

//���_����ނ̏o�����Ұ�.
struct VS_OUT
{
	float4	Pos		: SV_Position;
	float4	Color	: COLOR;
	float3	Normal	: TEXCOORD0;
	float2	Tex		: TEXCOORD1;
	float4	PosWorld: TEXCOORD2;
};

//---------------------------------------
//	���_�����.
//---------------------------------------
VS_OUT VS_Main(float4 Pos	: POSITION,
	float4 Norm : NORMAL,
	float2 Tex : TEXCOORD)
{
	VS_OUT Out = (VS_OUT)0;

	//��ۼު���ݕϊ�(ܰ��ށ��ޭ�����ۼު����).
	Out.Pos = mul(Pos, g_mWVP);

	//�@�������ق̎p���ɍ��킹��.
	// (���ق���]����Ζ@������]������K�v�����邽��).
	Out.Normal = mul(Norm, (float3x3)g_mW);

	//ܰ��ލ��W�n�ł̈ʒu���W.
	Out.PosWorld = mul(Pos, g_mW);

	//ø������W.
	Out.Tex = Tex;

	return Out;
}

//---------------------------------------
//	�߸�ټ����.
//---------------------------------------
float4 PS_Main(VS_OUT In) : SV_Target
{
	float4 AllColor = float4(0.0f, 0.0f, 0.0f, 0.0f);
	for (int light = 0; light < g_vLightMax.x; light++) {
		//ײĈʒu.
		float4 vLightPos = g_vLightPos;
		vLightPos.x += (g_vLightPosWidth.x * light) - g_vLightPosWidth.x;
		//ײ��޸��:�����߸�ق���ײČ��ݍ��W�Ɍ������޸��.
		float4 vLightVector = normalize(vLightPos - In.PosWorld);

		//�����޸��:�����߸�ق��王�_���W�Ɍ������޸��.
		float4 vEyeVector = normalize(g_vCamPos - In.PosWorld);
		//ײĂ̊�޸��.
		float4 vLightBaseVector = float4(0.0f, 1.0f, 0.0f, 1.0f);

		//ײĂ̊�޸�قɌ��݂�ײẲ�]�𔽉f.
		vLightBaseVector = mul(vLightBaseVector, g_mLightRot);

		//�����@�@.
		float4 ambient = g_Ambient;

		//�g�U���ˌ� �A.
		float NL = saturate(dot(In.Normal, vLightVector));
		float4 diffuse =
			(g_Diffuse / 2 + g_Texture.Sample(g_SamLinear, In.Tex) / 2)/**NL*/;

		//���ʔ��ˌ� �B.
		float3 reflect = normalize(2.0f * NL * In.Normal - vLightVector);
		float4 specular =
			pow(saturate(dot(reflect, vEyeVector)), 4)*g_Specular;
		//̫����ٍŏI�F�@�@�A�B�̍��v.
		float4 Color = ambient + diffuse + specular;
		Color.r *= g_vLightColor.x;
		Color.g *= g_vLightColor.y;
		Color.b *= g_vLightColor.z;
		//��߯�ײĂ͈͓̔��Ɣ͈͊O�̋��E�����炩�ɕω�������.
		float cos = saturate(dot(vLightBaseVector, vLightVector));
		//��݊p�x:�Ƃ肠���� 0.9f.
		if (cos < g_fLightWidth.x) {
			Color *= pow(cos / 3.0f, 12.0f *(0.9f - cos)) * Color;
		}

		//����.
		float Distance = length(vLightPos - In.PosWorld);
		//att = 1 �� 0 �� ( a + b * d + c * d^2 )
		//d:����
		//a,b,c:�萔.
		Color *= 1.0f / (0.0f + 0.0f * Distance + 0.3f * Distance * Distance);
		//ײċ��x�𔽉f.
		Color *= g_fIntensity.x;

		AllColor += Color;
	}
	//�x�[�X�̐F.
	float4 BaseColor = g_Texture.Sample(g_SamLinear, In.Tex) / 1.0f + In.Color / 1.0f;
	AllColor.a = BaseColor.a;
	AllColor.a *= g_vAlpha.x;

	//                 1
	// fatt = -------------------
	//        a + b * d + c * d^2
	// fatt :����.
	// a,b,c:�萔.
	// d    :����.

	return AllColor;
}


//============ ø��������̏ꍇ ===============================.
//---------------------------------------
//	���_�����.
//---------------------------------------
VS_OUT VS_NoTex(float4 Pos		: POSITION,
	float4 Norm : NORMAL)
{
	VS_OUT Out = (VS_OUT)0;

	//��ۼު���ݕϊ�(ܰ��ށ��ޭ�����ۼު����).
	Out.Pos = mul(Pos, g_mWVP);

	//�@�������ق̎p���ɍ��킹��.
	// (���ق���]����Ζ@������]������K�v�����邽��).
	Out.Normal = mul(Norm, (float3x3)g_mW);

	//ܰ��ލ��W�n�ł̈ʒu���W.
	Out.PosWorld = mul(Pos, g_mW);

	return Out;
}

//---------------------------------------
//	�߸�ټ����.
//---------------------------------------
float4 PS_NoTex(VS_OUT In) : SV_Target
{
	//ײĈʒu.
	float4 vLightPos = g_vLightPos;
	//�����޸��:�����߸�ق��王�_���W�Ɍ������޸��.
	float4 vEyeVector = normalize(g_vCamPos - In.PosWorld);
	//ײ��޸��:�����߸�ق���ײČ��ݍ��W�Ɍ������޸��.
	float4 vLightVector = normalize(vLightPos - In.PosWorld);
	//ײĂ̊�޸��.
	float4 vLightBaseVector = float4(0.0f, 1.0f, 0.0f, 1.0f);

	//ײĂ̊�޸�قɌ��݂�ײẲ�]�𔽉f.
	vLightBaseVector = mul(vLightBaseVector, g_mLightRot);

	//��{�F.
	float4 BaseColor = g_Texture.Sample(g_SamLinear, In.Tex) / 1.0f + In.Color / 1.0f;

	//�����@�@.
	float4 ambient = g_Ambient;

	//�g�U���ˌ� �A.
	float NL = saturate(dot(In.Normal, vLightVector));
	float4 diffuse = g_Diffuse * NL;

	//���ʔ��ˌ� �B.
	float3 reflect = normalize(2 * NL * In.Normal - vLightVector);
	float4 specular =
		pow(saturate(dot(reflect, vEyeVector)), 4)*g_Specular;

	//̫����ٍŏI�F�@�@�A�B�̍��v.
	float4 Color = ambient + diffuse + specular;

	//ײċ��x�𔽉f.
	Color *= g_fIntensity.x;

	//��߯�ײĂ͈͓̔��Ɣ͈͊O�̋��E�����炩�ɕω�������.
	float cos = saturate(dot(vLightBaseVector, vLightVector));
	//��݊p�x:�Ƃ肠���� 0.9f.
	if (cos < g_fLightWidth.x) {
		Color *= pow(cos / 3.0f, 12.0f *(0.9f - cos)) * Color;
	}

	//����.
	float Distance = length(g_vLightPos - In.PosWorld);
	// att = 1 �� 0 �� ( a + b * d + c * d^2 )
	// d:����
	// a,b,c:�萔.
	Color *=
		1.0f / (0.0f + 0.0f * Distance + 0.3f * Distance * Distance);

	//                 1
	// fatt = -------------------
	//        a + b * d + c * d^2
	// fatt :����.
	// a,b,c:�萔.
	// d    :����.

	Color.a *= g_vAlpha.x;


	return Color;
}