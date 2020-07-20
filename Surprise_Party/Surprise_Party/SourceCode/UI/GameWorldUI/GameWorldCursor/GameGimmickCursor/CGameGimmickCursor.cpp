#include "CGameGimmickCursor.h"

/***********************************
*		ギミックカーソルクラス.
********/
CGameGimmickCursor::CGameGimmickCursor()
	: m_bUnSelectableFlag	(false)
{
	//初期化処理関数.
	Init();
}

CGameGimmickCursor::~CGameGimmickCursor()
{
	//解放処理関数.
	Release();
}

//=====================================.
//		更新処理関数.
//=====================================.
void CGameGimmickCursor::UpDate()
{
	//カーソル上下動き.
	CursorUpDown();

	m_vPos = m_vCharacterPos;
	m_vPos.z = ADJUST_HEIGHT;
	m_vPos.y = ADJUST_WIDTH + m_fUpDownDistance;

	//透過値変更処理関数.
	AlphaChange(m_bUnSelectableFlag);
}

//======================================.
//		初期化処理関数.
//======================================.
void CGameGimmickCursor::Init()
{
	m_pCSprite = m_pCResourceManager->GetSprite(enSprite::Cursol);
	m_fScale = SCALE;
	m_vColor = COLOR;
}

//======================================.
//		解放処理関数.
//======================================.
void CGameGimmickCursor::Release()
{

}