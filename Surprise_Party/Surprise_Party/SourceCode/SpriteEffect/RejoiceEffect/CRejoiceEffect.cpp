#include "CRejoiceEffect.h"

/*********************************************
*		喜びエフェクト.
*********/
CRejoiceEffect::CRejoiceEffect()
{
	//初期化処理関数.
	Init();
}

CRejoiceEffect::~CRejoiceEffect()
{
	//解放処理関数.
	Release();
}

//=========================================.
//		更新処理関数.
//=========================================.
void CRejoiceEffect::Update()
{

}

//=========================================.
//		初期化処理関数.
//=========================================.
void CRejoiceEffect::Init()
{
	//要素数設定処理.
	m_pCSprite.resize(SPRITE_MAX);
	SettingElementsCount();

	//初期化処理関数.
	for (unsigned int sprite = 0; sprite < m_pCSprite.size(); sprite++) {


	}
}

//=========================================.
//		解放処理関数.
//=========================================.
void CRejoiceEffect::Release()
{

}

//=========================================.
//		表示判定処理関数.
//=========================================.
void CRejoiceEffect::AppeartJudgement(const int& num)
{

}

//=========================================.
//		移動処理関数.
//=========================================.
void CRejoiceEffect::Move(const int& num)
{

}

//=========================================.
//		スプライト紐づけ処理関数.
//=========================================.
void CRejoiceEffect::LinkSprite(const int& num)
{
	//番号ごとの紐づけ.
	switch (static_cast<enRejoiceSpriteType>(num % SPRITE_MAX)) {
	case enRejoiceSpriteType::EightPartNote:
		m_pCSprite[num] = m_pCResourceManager->GetSprite(enSprite::eight_part_note);
		break;
	case enRejoiceSpriteType::SixteenPartNote:
		m_pCSprite[num] = m_pCResourceManager->GetSprite(enSprite::sixteen_part_note);
		break;
	case enRejoiceSpriteType::Flower:
		m_pCSprite[num] = m_pCResourceManager->GetSprite(enSprite::Flower);
		break;
	}
}