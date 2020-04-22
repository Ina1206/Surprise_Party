#include "CTutorialBlackScreen.h"

/******************************************
*		チュートリアル時の黒画面.
**************/
CTutorialBlackScreen::CTutorialBlackScreen()
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
	m_vUIPos[SpriteNum].y += 20.0f;
	m_vUIScale[SpriteNum] = D3DXVECTOR3(1.1f, 1.1f, 1.1f);
}

//============================================.
//		解放処理関数.
//============================================.
void CTutorialBlackScreen::Release()
{

}