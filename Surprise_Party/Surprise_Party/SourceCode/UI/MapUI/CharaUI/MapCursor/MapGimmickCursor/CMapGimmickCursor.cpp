#include "CMapGimmickCursor.h"

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
	m_vPos.y = 60.0f;
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
	m_fScale = 1.3f;
	//色.
	m_vColor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
}

//============================================.
//		解放処理関数.
//============================================.
void CMapGimmickCursor::Release()
{
	m_pCSpriteUI = nullptr;
}