/***************************************************************************************************
*	SkinMeshCode Version 2.00
*	LastUpdate	: 2019/10/09
*	Auther		: an.
**/
//��`.
#define MAX_BONE_MATRICES (255)

//�O���[�o��.
Texture2D		g_Texture	: register( t0 );	//�e�N�X�`���[�� ���W�X�^�[t(n).
SamplerState	g_Sampler	: register( s0 );	//�T���v���[�̓��W�X�^�[s(n).


//�R���X�^���g�o�b�t�@(���b�V������).
cbuffer per_mesh		: register( b0 )
{
	matrix g_mW;		//���[���h�s��.
	matrix g_mWVP;		//���[���h����ˉe�܂ł̕ϊ��s��.
};
//�R���X�^���g�o�b�t�@(�}�e���A������).
cbuffer per_material	: register( b1 )
{
	float4 g_Ambient	= float4( 0, 0, 0, 0 );	//�A���r�G���g��.
	float4 g_Diffuse	= float4( 1, 0, 0, 0 );	//�g�U����(�F�j
	float4 g_Specular	= float4( 1, 1, 1, 1 );	//���ʔ���.
};
//�R���X�^���g�o�b�t�@(�t���[������).
cbuffer per_frame		: register( b2 )
{
	float4	g_vEye;				//�J�����ʒu.
	float4	g_vLightPos;		//ײĈʒu.
	matrix	g_mLightRot;		//ײĉ�]�s��.
	float4	g_fIntensity;		//ײċ��x(���邳). ��x�̂ݎg�p����.
	float4	g_fLightWidth;		//���C�g�L��.
	float4	g_vLightColor;		//���C�g�F.
	float4	g_fAlpha;			//���ߒl.
	float4	g_vUV;				//UV.
	float4	g_vLightPosWidth;	//���C�g�̔z�u��.
	float4	g_vLightMax;		//���C�g�ő�l.
};
//�{�[���̃|�[�Y�s�񂪓���.
cbuffer per_bones		: register( b3 )
{
	matrix g_mConstBoneWorld[MAX_BONE_MATRICES];
};

//�X�L�j���O��̒��_�E�@��������.
struct Skin
{
	float4 Pos;
	float3 Norm;
};
//�o�[�e�b�N�X�o�b�t�@�[�̓���.
struct VSSkinIn
{
	float3 Pos		: POSITION;		//�ʒu.  
	float3 Norm		: NORMAL;		//���_�@��.
	float2 Tex		: TEXCOORD;		//�e�N�X�`���[���W.
	uint4  Bones	: BONE_INDEX;	//�{�[���̃C���f�b�N�X.
	float4 Weights	: BONE_WEIGHT;	//�{�[���̏d��.
};

//�s�N�Z���V�F�[�_�[�̓��́i�o�[�e�b�N�X�o�b�t�@�[�̏o�́j�@
struct PSSkinIn
{
	float4 Pos		: SV_Position;	//�ʒu.
	float3 Norm		: NORMAL;		//���_�@��.
	float2 Tex		: TEXCOORD0;	//�e�N�X�`���[���W.
	float3 Normal	: TEXCOORD1;
	float4 PosWorld	: TEXCOORD2;		
	float4 Color	: COLOR0;		//�ŏI�J���[�i���_�V�F�[�_�[�ɂ����Ắj.
};


//�w�肵���ԍ��̃{�[���̃|�[�Y�s���Ԃ�.
//�T�u�֐��i�o�[�e�b�N�X�V�F�[�_�[�Ŏg�p�j.
matrix FetchBoneMatrix( uint iBone )
{
	return g_mConstBoneWorld[iBone];
}


//���_���X�L�j���O�i�{�[���ɂ��ړ��j����.
//�T�u�֐��i�o�[�e�b�N�X�V�F�[�_�[�Ŏg�p�j.
Skin SkinVert( VSSkinIn Input )
{
	Skin Output = (Skin)0;

	float4 Pos = float4(Input.Pos,1);
	float3 Norm = Input.Norm;
	//�{�[��0.
	uint iBone	=Input.Bones.x;
	float fWeight= Input.Weights.x;
	matrix m	=  FetchBoneMatrix( iBone );
	Output.Pos	+= fWeight * mul( Pos, m );
	Output.Norm	+= fWeight * mul( Norm, (float3x3)m );
	//�{�[��1.
	iBone	= Input.Bones.y;
	fWeight	= Input.Weights.y;
	m		= FetchBoneMatrix( iBone );
	Output.Pos	+= fWeight * mul( Pos, m );
	Output.Norm	+= fWeight * mul( Norm, (float3x3)m );
	//�{�[��2.
	iBone	= Input.Bones.z;
	fWeight	= Input.Weights.z;
	m		= FetchBoneMatrix( iBone );
	Output.Pos	+= fWeight * mul( Pos, m );
	Output.Norm	+= fWeight * mul( Norm, (float3x3)m );
	//�{�[��3.
	iBone	= Input.Bones.w;
	fWeight	= Input.Weights.w;
	m		= FetchBoneMatrix( iBone );
	Output.Pos	+= fWeight * mul( Pos, m );
	Output.Norm	+= fWeight * mul( Norm, (float3x3)m );

	return Output;
}

// �o�[�e�b�N�X�V�F�[�_.
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


// �s�N�Z���V�F�[�_.
float4 PS_Main( PSSkinIn input ) : SV_Target
{

	float4 AllColor = float4(0.0f, 0.0f, 0.0f, 0.0f);
	for (int light = 0; light < g_vLightMax.x; light++) {
		//ײĈʒu.
		float4 vLightPos = g_vLightPos;
		vLightPos.x += (g_vLightPosWidth.x * light) - g_vLightPosWidth.x;
		//ײ��޸��:�����߸�ق���ײČ��ݍ��W�Ɍ������޸��.
		float4 vLightVector = normalize(vLightPos - input.PosWorld);
		//�����޸��:�����߸�ق��王�_���W�Ɍ������޸��.
		float4 vEyeVector = normalize(g_vEye - input.PosWorld);
		//ײĂ̊�޸��.
		float4 vLightBaseVector = float4(0.0f, 1.0f, 0.0f, 1.0f);

		//ײĂ̊�޸�قɌ��݂�ײẲ�]�𔽉f.
		vLightBaseVector = mul(vLightBaseVector, g_mLightRot);


		//�����@�@.
		float4 ambient = g_Ambient;

		//�g�U���ˌ� �A.
		float NL = saturate(dot(input.Norm, vLightVector));
		float4 diffuse =
			(g_Diffuse / 2 + g_Texture.Sample(g_Sampler, input.Tex) / 2)/**NL*/;


		//���ʔ��ˌ� �B.
		float3 reflect = normalize(2.0f * NL * input.Normal - vLightVector);
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
		float Distance = length(vLightPos - input.PosWorld);
		//att = 1 �� 0 �� ( a + b * d + c * d^2 )
		//d:����
		//a,b,c:�萔.
		Color *=
			1.0f / (0.0f + 0.0f * Distance + 0.3f * Distance * Distance);

		//ײċ��x�𔽉f.
		Color *= g_fIntensity.x;

		AllColor += Color;
	}
   //                 1
   // fatt = -------------------
   //        a + b * d + c * d^2
   // fatt :����.
   // a,b,c:�萔.
   // d    :����.
	
	return AllColor;
}
