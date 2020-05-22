#include "CSmokeEffect.h"

/*************************************
*		���G�t�F�N�g�N���X.
**********/
CSmokeEffect::CSmokeEffect()
{
	//�����������֐�.
	Init();
}

CSmokeEffect::~CSmokeEffect()
{

}

//======================================.
//		�X�V�����֐�.
//======================================.
void CSmokeEffect::Update()
{
	for (unsigned int sprite = 0; sprite < m_pCSprite.size(); sprite++) {
		m_vPos[sprite] = m_vCenterPos;
	}
}

//======================================.
//		�G�t�F�N�g�J�n�����������֐�.
//======================================.
void CSmokeEffect::PlayStartInit(const int& num)
{

}

//======================================.
//		�����������֐�.
//======================================.
void CSmokeEffect::Init()
{
	//�v�f���̐ݒ�.
	m_pCSprite.push_back(m_pCResourceManager->GetSprite(enSprite::Smoke));
	m_pCSprite.push_back(m_pCResourceManager->GetSprite(enSprite::Smoke));
	SettingElementsCount();

	//�����l�ݒ�.
	for (unsigned int SpriteNum = 0; SpriteNum < m_pCSprite.size(); SpriteNum++) {
		SettingDefaultValue(SpriteNum);
		m_fScale[SpriteNum] = 1.0f;
		m_fAlpha[SpriteNum] = 1.0f;
	}
		m_bRenderFlag = true;
}

//======================================.
//		��������֐�.
//======================================.
void CSmokeEffect::Release()
{

}

//======================================.
//		�\�����菈���֐�.
//======================================.
void CSmokeEffect::AppeartJudgement(const int& num)
{

}

//======================================.
//		�ړ������֐�.
//======================================.
void CSmokeEffect::Move(const int& num)
{

}