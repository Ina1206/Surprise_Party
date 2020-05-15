#include "CMoveNoteEffect.h"

/*************************************
*	�����ړ��G�t�F�N�g�N���X.
*************/
CMoveNoteEffect::CMoveNoteEffect()
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
		}
		m_bRenderFlag = true;
	}

	if (m_bRenderFlag == false) {
		return;
	}

	m_DispTime++;

	for (unsigned int Effect = 0; Effect < m_pCSprite.size(); Effect++) {
		//�\�����菈���֐�.
		AppeartJudgement(Effect);
		//�ړ������֐�.
		Move(Effect);
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
	for (unsigned int Effect = 0; Effect < m_pCSprite.size(); Effect++) {
		//�����l�ݒ菈���֐�.
		SettingDefaultValue(Effect);

		m_fAlpha[Effect] = 1.0f;
		m_fScale[Effect] = 2.0f;
	}
	m_vPart[0] = D3DXVECTOR2(0.0f, 1.0f);
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
	if (m_DispTime < 10) {
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

	m_vPos[num].y -= 0.05f;
	m_vPos[num].x -= 0.05f;
}