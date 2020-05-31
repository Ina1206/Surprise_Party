#include "CQuestionEffect.h"

/************************************
*		�^��G�t�F�N�g�N���X.
***************/
CQuestionEffect::CQuestionEffect()
{
	//����������.
	Init();
}

CQuestionEffect::~CQuestionEffect()
{
	//��������֐�.
	Release();
}

//========================================.
//		�X�V�����֐�.
//========================================.
void CQuestionEffect::Update()
{

}

//========================================.
//		�G�t�F�N�g�J�n�����������֐�.
//========================================.
void CQuestionEffect::PlayStartInit(const int& num)
{

}

//========================================.
//		�����������֐�.
//========================================.
void CQuestionEffect::Init()
{
	m_pCSprite.push_back(m_pCResourceManager->GetSprite(enSprite::QuestionMark));
	SettingElementsCount();

	const int SpriteNum = 0;
	SettingDefaultValue(SpriteNum);
	m_fAlpha[SpriteNum] = 1.0f;
	m_fScale[SpriteNum] = 1.0f;
}

//========================================.
//		��������֐�.
//========================================.
void CQuestionEffect::Release()
{

}

//========================================.
//		�\�����菈���֐�.
//========================================.
void CQuestionEffect::AppeartJudgement(const int& num)
{

}

//========================================.
//		�ړ������֐�.
//========================================.
void CQuestionEffect::Move(const int& num)
{

}