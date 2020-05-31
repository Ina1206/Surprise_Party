#include "CQuestionEffect.h"

/************************************
*		疑問エフェクトクラス.
***************/
CQuestionEffect::CQuestionEffect()
{
	//初期化処理.
	Init();
}

CQuestionEffect::~CQuestionEffect()
{
	//解放処理関数.
	Release();
}

//========================================.
//		更新処理関数.
//========================================.
void CQuestionEffect::Update()
{

}

//========================================.
//		エフェクト開始初期化処理関数.
//========================================.
void CQuestionEffect::PlayStartInit(const int& num)
{

}

//========================================.
//		初期化処理関数.
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
//		解放処理関数.
//========================================.
void CQuestionEffect::Release()
{

}

//========================================.
//		表示判定処理関数.
//========================================.
void CQuestionEffect::AppeartJudgement(const int& num)
{

}

//========================================.
//		移動処理関数.
//========================================.
void CQuestionEffect::Move(const int& num)
{

}