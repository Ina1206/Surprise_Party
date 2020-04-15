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
}

//============================================.
//		解放処理関数.
//============================================.
void CTutorialBlackScreen::Release()
{

}