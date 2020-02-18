#include "CGameGimmickCursor.h"

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
	m_vPos.z = -3.0f;
	m_vPos.y = 4.0f + m_fUpDownDistance;

	//透過値変更処理関数.
	AlphaChange(m_bUnSelectableFlag);
}

//======================================.
//		初期化処理関数.
//======================================.
void CGameGimmickCursor::Init()
{
	m_pCSprite = m_pCResourceManager->GetSprite(enSprite::Cursol);
	m_fScale = 2.5f;
	m_vColor = D3DXVECTOR3(0.5f, 1.0f, 0.5f);
}

//======================================.
//		解放処理関数.
//======================================.
void CGameGimmickCursor::Release()
{

}