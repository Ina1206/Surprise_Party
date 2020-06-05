#include "CWhiteScreenFade.h"

/******************************************
*		白スクリーンフェードクラス.
************/
CWhiteScreenFade::CWhiteScreenFade()
{
	//初期化処理関数.
	Init();
}

CWhiteScreenFade::~CWhiteScreenFade()
{
	//解放処理関数.
	Release();
}

//=========================================.
//		更新処理化数.
//=========================================.
void CWhiteScreenFade::Update()
{

}

//=========================================.
//		描画処理関数.
//=========================================.
void CWhiteScreenFade::Render()
{

}

//=========================================.
//		初期化処理関数.
//=========================================.
void CWhiteScreenFade::Init()
{
	m_pCSpriteUI = m_pCResourceManager->GetSpriteUI(enSpriteUI::WhiteScreen);
}

//=========================================.
//		解放処理関数.
//=========================================.
void CWhiteScreenFade::Release()
{

}