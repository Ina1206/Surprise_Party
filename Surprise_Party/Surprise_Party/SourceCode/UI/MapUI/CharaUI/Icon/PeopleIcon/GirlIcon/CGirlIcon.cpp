#include "CGirlIcon.h"

CGirlIcon::CGirlIcon()
{
	//初期化処理関数.
	Init();
}

CGirlIcon::~CGirlIcon()
{
	//解放処理関数.
	Release();
}

//=====================================.
//		初期化処理関数.
//=====================================.
void CGirlIcon::Init()
{
	//女の子のアイコンUI読み込み管理からアドレス取得.
	m_pCSpriteUI = m_pCResourceManager->GetSpriteUI(enSpriteUI::Girl_Icon);
	//初期の座標.
	m_vPos = START_POS;

	m_bShoutWoman = true;
}

//=====================================.
//		解放処理関数.
//=====================================.
void CGirlIcon::Release()
{
	m_pCSpriteUI = nullptr;
}