#include "CTutorialBlackScreen.h"

/******************************************
*		チュートリアル時の黒画面.
**************/
CTutorialBlackScreen::CTutorialBlackScreen()
	: m_vCenterPos	(0.0f, 0.0f, 0.0f)
	, m_bDispFlag	(false)
{
	//初期化処理関数.
	Init();
}

CTutorialBlackScreen::~CTutorialBlackScreen()
{
	//解放処理関数.
	Release();
}

//==========================================.
//		更新処理関数.
//==========================================.
void CTutorialBlackScreen::Update()
{
	//座標設定処理関数.
	SettingPos();
}

//===========================================.
//		初期化処理関数.
//===========================================.
void CTutorialBlackScreen::Init()
{
	m_pCSpriteUI.push_back(m_pCResourceManager->GetSpriteUI(enSpriteUI::DescriptionBlack));
	//初期設定処理.
	SettingInit();
	const int SpriteNum = static_cast<int>(m_pCSpriteUI.size()) - 1;
	m_vUIPos[SpriteNum].y -= 90.0f;
	m_vUIScale[SpriteNum] = D3DXVECTOR3(1.2f, 1.2f, 1.2f);
}

//============================================.
//		解放処理関数.
//============================================.
void CTutorialBlackScreen::Release()
{

}

//============================================.
//		座標設定処理関数.
//============================================.
void CTutorialBlackScreen::SettingPos()
{
	const int SpriteNum = static_cast<int>(m_pCSpriteUI.size()) - 1;
	if (m_vCenterPos.x < HALF_SCREEN_SIZE) {
		m_vUIPos[SpriteNum].x = 0.0f;
		return;
	}

	m_vUIPos[SpriteNum].x = 1300.0f;
	m_vUIRot[SpriteNum].y = 3.1f;
}