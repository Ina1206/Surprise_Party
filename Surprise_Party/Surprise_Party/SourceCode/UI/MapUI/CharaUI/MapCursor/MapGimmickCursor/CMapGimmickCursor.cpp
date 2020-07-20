#include "CMapGimmickCursor.h"

/****************************************
*	マップ上のギミック用カーソルクラス.
********/
CMapGimmickCursor::CMapGimmickCursor()
{
	//初期化処理関数.
	Init();
}

CMapGimmickCursor::~CMapGimmickCursor()
{
	//解放処理関数.
	Release();
}

//============================================.
//		更新処理関数.
//============================================.
void CMapGimmickCursor::UpDate()
{
	//ゲーム内からマップ内に座標変換処理関数.
	GameMapConversion();
	m_vPos.y = CURSOR_HEIGHT;
	m_vPos -= CURSOR_UI_ADJUSTMENT;
}

//============================================.
//		初期化処理関数.
//============================================.
void CMapGimmickCursor::Init()
{
	//アドレス取得.
	m_pCSpriteUI = m_pCResourceManager->GetSpriteUI(enSpriteUI::DispGimmick_Iccon);

	//大きさ.
	m_fScale = SCALE;
	//色.
	m_vColor = COLOR;
}

//============================================.
//		解放処理関数.
//============================================.
void CMapGimmickCursor::Release()
{
	m_pCSpriteUI = nullptr;
}