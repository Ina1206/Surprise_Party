#include "CBoyIcon.h"

/*************************************
*		男の子アイコンクラス.
******/
CBoyIcon::CBoyIcon()
{
	//初期化処理関数.
	Init();
}

CBoyIcon::~CBoyIcon()
{
	//解放処理関数.
	Release();
}

//=====================================.
//		初期化処理関数.
//=====================================.
void CBoyIcon::Init()
{
	//読み込み管理クラスからアドレス取得.
	m_pCSpriteUI = m_pCResourceManager->GetSpriteUI(enSpriteUI::Boy_Icon);

	//座標初期設定.
	m_vPos = START_POS;

	m_bShoutWoman = false;
}

//=====================================.
//		解放処理関数.
//=====================================.
void CBoyIcon::Release()
{
	m_pCSpriteUI = nullptr;	
}