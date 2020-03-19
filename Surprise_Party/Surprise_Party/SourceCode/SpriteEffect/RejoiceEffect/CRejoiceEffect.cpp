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
		//スプライト紐づけ処理関数.
		LinkSprite(sprite);

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
	m_vPos[num].x += cos((10.0f + (num * 20.0f) / CIRCLE_HALF_ANGLE * PI)) * 0.02f;
	m_vPos[num].y += sin((10.0f + (num * 20.0f) / CIRCLE_HALF_ANGLE * PI)) * 0.02f;
}

//=========================================.
//		スプライト紐づけ処理関数.
//=========================================.
void CRejoiceEffect::LinkSprite(const int& num)
{
	//番号ごとの紐づけ.
	switch (static_cast<enRejoiceSpriteType>(num % SPRITE_MAX)) {
	case enRejoiceSpriteType::PinkEightPartNote:
		m_pCSprite[num] = m_pCResourceManager->GetSprite(enSprite::eight_part_note);
		m_vPart[num] = D3DXVECTOR2(0.0f, 0.0f);
		break;
	case enRejoiceSpriteType::BlueEightPartNote:
		m_pCSprite[num] = m_pCResourceManager->GetSprite(enSprite::eight_part_note);
		m_vPart[num] = D3DXVECTOR2(2.0f, 0.0f);
		break;
	case enRejoiceSpriteType::PinkFlower:
		m_pCSprite[num] = m_pCResourceManager->GetSprite(enSprite::Flower);
		m_vPart[num] = D3DXVECTOR2(0.0f, 0.0f);
		break;
	case enRejoiceSpriteType::RedFlower:
		m_pCSprite[num] = m_pCResourceManager->GetSprite(enSprite::Flower);
		m_vPart[num] = D3DXVECTOR2(0.0f, 1.0f);
		break;
	}
}