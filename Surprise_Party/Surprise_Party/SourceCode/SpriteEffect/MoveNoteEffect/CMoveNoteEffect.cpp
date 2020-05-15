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
			m_vPos[Effect] = m_vCenterPos;
			m_ScalingFlag[Effect] = SCALE_FLAG;
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
		//�ړ������֐�.
		Move(Effect);
		//�g�k�����֐�.
		Scaling(Effect);
	}

}

//========================================.
//		�G�t�F�N�g�J�n�����������֐�.
//========================================.
void CMoveNoteEffect::PlayStartInit(const int& num)
{

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
	m_ScalingFlag.resize(2);
	for (unsigned int Effect = 0; Effect < m_pCSprite.size(); Effect++) {
		//�����l�ݒ菈���֐�.
		SettingDefaultValue(Effect);
		m_ScalingFlag[Effect] = SCALE_FLAG;

		m_fAlpha[Effect] = 1.0f;
		//m_fScale[Effect] = 1.0f;
	}
	m_vPart[0] = D3DXVECTOR2(0.0f, 1.0f);
	m_DispTime = 15;
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
	if (m_DispTime < 15) {
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
	if (m_bDispFlag[num] == false) {
		return;
	}

	m_fDistance[num] = 0.2f;

	//���W�A��.
	const float RADIAN = static_cast<float>(D3DXToRadian(m_fAngle[num]));

	m_vPos[num].x += cos(RADIAN) * m_fDistance[num];
	m_vPos[num].y += sin(RADIAN) * m_fDistance[num];

	if (num >= 1) {
		m_vRot[num].z = RADIAN;
	}
}

//========================================.
//		�g�k�����֐�.
//========================================.
void CMoveNoteEffect::Scaling(const int& num)
{
	if (m_ScalingFlag[num] & SCALE_FLAG) {
		m_fScale[num] += 0.05f;

		if (m_fScale[num] > SCALE_MAX) {
			m_fScale[num] = SCALE_MAX;
			m_ScalingFlag[num] = SCALE_DOWN_FLAG;
		}

		return;
	}

	m_fScale[num] -= 0.05f;
	if (m_fScale[num] < SCALE_MIN) {
		m_fScale[num] = SCALE_MIN;
	}
}