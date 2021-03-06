#include "CMapGhostCursor.h"

/************************************
*	マップ上のお化けカーソルクラス.
**********/
CMapGhostCursor::CMapGhostCursor()
{
	//初期化処理関数.
	Init();
}

CMapGhostCursor::~CMapGhostCursor()
{
	//解放処理関数.
	Release();
}

//=======================================.
//		更新処理関数.
//=======================================.
void CMapGhostCursor::UpDate()
{
	//ゲーム内からマップ内に座標変換処理関数.
	GameMapConversion();
	m_vPos.y = 0.0f;
	m_vPos -= CURSOR_UI_ADJUSTMENT;
}

//=======================================.
//		初期化処理関数.
//=======================================.
void CMapGhostCursor::Init()
{
	//読み込んだテクスチャのアドレス取得.
	m_pCSpriteUI = m_pCResourceManager->GetSpriteUI(enSpriteUI::Ghost_Icon);

	//大きさ設定.
	m_fScale = SCALE;
	//色設定.
	m_vColor = COLOR;
}

//=======================================.
//		解放処理関数.
//=======================================.
void CMapGhostCursor::Release()
{
	m_pCSpriteUI = nullptr;
}