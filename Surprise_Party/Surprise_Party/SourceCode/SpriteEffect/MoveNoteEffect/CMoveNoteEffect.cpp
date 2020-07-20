#include "CMoveNoteEffect.h"

/*************************************
*	�����ړ��G�t�F�N�g�N���X.
*************/
CMoveNoteEffect::CMoveNoteEffect()
	: m_ScalingFlag	(0)
{
	//�����������֐�.
	Init();
}

CMoveNoteEffect::~CMoveNoteEffect()
{
	//��������֐�.
	Release();
}

//========================================.
//		�X�V�����֐�.
//========================================.
void CMoveNoteEffect::Update()
{
	if (m_bPlayFlag == true) {
		for (unsigned int Effect = 0; Effect < m_pCSprite.size(); Effect++) {
			PlayStartInit(Effect);
		}
		m_bRenderFlag = true;
	}

	//�`�悵�Ȃ��������O����.
	if (m_bRenderFlag == false) {
		return;
	}

	m_DispTime++;

	for (unsigned int Effect = 0; Effect < m_pCSprite.size(); Effect++) {
		//�\�����菈���֐�.
		AppeartJudgement(Effect);

		if (m_bDispFlag[Effect] == false) {
			continue;
		}

		//�ړ������֐�.
		Move(Effect);
		//�g�k�����֐�.
		if (ScalingTransparent(Effect) == true) {
			m_bRenderFlag = false;
		}
	}

}

//========================================.
//		�G�t�F�N�g�J�n�����������֐�.
//========================================.
void CMoveNoteEffect::PlayStartInit(const int& num)
{
	SettingDefaultValue(num);
	m_vPos[num] = m_vCenterPos;
	m_ScalingFlag[num] = SCALE_FLAG;
}

//========================================.
//		�����������֐�.
//========================================.
void CMoveNoteEffect::Init()
{
	m_pCSprite.push_back(m_pCResourceManager->GetSprite(enSprite::eight_part_note));
	m_pCSprite.push_back(m_pCResourceManager->GetSprite(enSprite::Wave));
	//�v�f���ݒ菈���֐�.
	SettingElementsCount();
	m_ScalingFlag.resize(m_pCSprite.size());
	for (unsigned int Effect = 0; Effect < m_pCSprite.size(); Effect++) {
		//�����l�ݒ菈���֐�.
		SettingDefaultValue(Effect);
		m_ScalingFlag[Effect] = SCALE_FLAG;

		m_fAlpha[Effect] = ALPHA_MAX;
	}
	m_vPart[NOTE_NUM] = NOTE_UV_POS;
	m_DispTime = TIME_MAX;
	m_fAlphaSpeed = ALPHA_SPEED;
	m_fScalingSpeed = SCALING_SPEED;
}

//========================================.
//		��������֐�.
//========================================.
void CMoveNoteEffect::Release()
{

}

//========================================.
//		�\�����菈���֐�.
//========================================.
void CMoveNoteEffect::AppeartJudgement(const int& num)
{
	if (m_DispTime < TIME_MAX) {
		return;
	}

	if (m_bDispFlag[num] == false) {
		m_bDispFlag[num] = true;
		m_DispTime = 0;
	}
}

//========================================.
//		�ړ������֐�.
//========================================.
void CMoveNoteEffect::Move(const int& num)
{
	m_fDistance[num] = DISTANCE;

	//���W�A��.
	const float RADIAN = static_cast<float>(D3DXToRadian(m_fAngle[num]));

	m_vPos[num].x += cos(RADIAN) * m_fDistance[num];
	m_vPos[num].y += sin(RADIAN) * m_fDistance[num];

	if (num >= 1) {
		m_vRot[num].z = RADIAN;
	}
}
