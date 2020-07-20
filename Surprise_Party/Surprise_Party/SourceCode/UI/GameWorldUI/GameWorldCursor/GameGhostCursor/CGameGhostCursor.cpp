#include "CGameGhostCursor.h"

/*********************************************
*	ゲーム内のお化けのカーソルクラス.
*************/
CGameGhostCursor::CGameGhostCursor()
	: m_bRestFlag	(false)
{
	//初期化処理関数.
	Init();
}

CGameGhostCursor::~CGameGhostCursor()
{
	//解放処理関数.
	Release();
}

//=========================================.
//		更新処理関数.
//=========================================.
void CGameGhostCursor::UpDate()
{
	//カーソル上下動き処理関数.
	CursorUpDown();

	m_vPos = m_vCharacterPos;
	m_vPos.y = CURSOL_BASE_HIGHT + m_fUpDownDistance;

	//透過値変更処理関数.
	AlphaChange(m_bRestFlag);
}

//=========================================.
//		初期化処理関数.
//=========================================.
void CGameGhostCursor::Init()
{
	m_pCSprite = m_pCResourceManager->GetSprite(enSprite::Cursol);
	m_fScale = SCALE;
}

//=========================================.
//		解放処理関数.
//=========================================.
void CGameGhostCursor::Release()
{
	m_pCSprite = nullptr;
}