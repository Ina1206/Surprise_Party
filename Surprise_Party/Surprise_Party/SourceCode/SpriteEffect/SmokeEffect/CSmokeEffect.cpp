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
	m_pCSprite.push_back(m_pCResourceManager->GetSprite(enSprite::Smoke));
	m_pCSprite.push_back(m_pCResourceManager->GetSprite(enSprite::Smoke));
	SettingElementsCount();

	for (unsigned int SpriteNum = 0; SpriteNum < m_pCSprite.size(); SpriteNum++) {
		SettingDefaultValue(SpriteNum);
	}
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