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
	for (unsigned int sprite = 0; sprite < m_pCSprite.size(); sprite++) {
		m_vPos[sprite] = m_vCenterPos;
	}
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
	//要素数の設定.
	m_pCSprite.push_back(m_pCResourceManager->GetSprite(enSprite::Smoke));
	m_pCSprite.push_back(m_pCResourceManager->GetSprite(enSprite::Smoke));
	SettingElementsCount();

	//初期値設定.
	for (unsigned int SpriteNum = 0; SpriteNum < m_pCSprite.size(); SpriteNum++) {
		SettingDefaultValue(SpriteNum);
		m_fScale[SpriteNum] = 1.0f;
		m_fAlpha[SpriteNum] = 1.0f;
	}
		m_bRenderFlag = true;
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