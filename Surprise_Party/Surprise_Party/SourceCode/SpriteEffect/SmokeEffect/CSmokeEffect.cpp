#include "CSmokeEffect.h"

/*************************************
*		煙エフェクトクラス.
**********/
CSmokeEffect::CSmokeEffect()
{
	//初期化処理関数.
	Init();
}

CSmokeEffect::~CSmokeEffect()
{

}

//======================================.
//		更新処理関数.
//======================================.
void CSmokeEffect::Update()
{

}

//======================================.
//		エフェクト開始処理化処理関数.
//======================================.
void CSmokeEffect::PlayStartInit(const int& num)
{

}

//======================================.
//		初期化処理関数.
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
//		解放処理関数.
//======================================.
void CSmokeEffect::Release()
{

}

//======================================.
//		表示判定処理関数.
//======================================.
void CSmokeEffect::AppeartJudgement(const int& num)
{

}

//======================================.
//		移動処理関数.
//======================================.
void CSmokeEffect::Move(const int& num)
{

}