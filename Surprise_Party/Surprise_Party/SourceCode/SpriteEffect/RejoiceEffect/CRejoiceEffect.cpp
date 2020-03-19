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
	for (unsigned int sprite = 0; sprite < m_pCSprite.size(); sprite++) {
		static bool flag = false;
		if (GetAsyncKeyState(VK_F1) & 0x0001) {
			if (flag == false) {
				flag = true;
			}
			else {
				flag = false;
			}
		}

		D3DXVECTOR3 vChange;
		if (flag == false) {
			vChange = m_vPos[sprite];
		}
		else {
			vChange = m_vRot[sprite];
		}

		if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
			vChange.x += 0.01f;
		}
		if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
			vChange.x -= 0.01f;
		}
		if (GetAsyncKeyState(VK_UP) & 0x8000) {
			vChange.y += 0.01f;
		}
		if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
			vChange.y -= 0.01f;
		}
		if (GetAsyncKeyState('Z') & 0x8000) {
			vChange.z += 0.01f;
		}
		if (GetAsyncKeyState('X') & 0x8000) {
			vChange.z -= 0.01f;
		}

		if (flag == false) {
			m_vPos[sprite] = vChange;
		}
		else {
			m_vRot[sprite] = vChange;
		}

		//if (m_vPos[sprite] == D3DXVECTOR3(0.0f, 0.0f, 0.0f)) {
			m_vPos[sprite] = m_vCenterPos;
		//}
	}
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

		m_vPos[sprite] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_fAlpha[sprite] = ALPHA_MAX;
		m_fScale[sprite] = SCALE_MAX;
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
	switch (static_cast<enRejoiceSpriteType>(num % SPRITE_TYPE_MAX)) {
	case enRejoiceSpriteType::YellowEightPartNote:
		m_pCSprite[num] = m_pCResourceManager->GetSprite(enSprite::eight_part_note);
		m_vPart[num] = D3DXVECTOR2(0.0f, 2.0f);
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
		m_vPart[num] = D3DXVECTOR2(1.0f, 1.0f);
		break;
	}
}