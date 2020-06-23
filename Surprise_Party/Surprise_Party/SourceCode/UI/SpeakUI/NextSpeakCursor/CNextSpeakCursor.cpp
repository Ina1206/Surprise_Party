#include "CNextSpeakCursor.h"

/*****************************************
*		次の会話のカーソルクラス.
*****************/
CNextSpeakCursor::CNextSpeakCursor()
	: m_pCSpriteUI	(nullptr)
	, m_vStartPos	(0.0f, 0.0f, 0.0f)
	, m_bDispFlag	(false)
{
	//初期化処理関数.
	Init();
}

CNextSpeakCursor::~CNextSpeakCursor()
{
	//解放処理関数.
	Release();
}

//========================================.
//		更新処理関数.
//========================================.
void CNextSpeakCursor::Update()
{
	//描画していない場合は処理終了.
	if (m_bDispFlag == false) {
		m_vPos = m_vStartPos;
		return;
	}
	m_vPos.x = m_vStartPos.x;
	//m_fAcc -= 0.05f;
	//if (m_vPos.y < m_vStartPos.y) {
	//	m_fAcc = 1.0f;
	//}

	//m_vPos.y += m_fAcc - 0.5f;
}

//========================================.
//		描画処理関数.
//========================================.
void CNextSpeakCursor::Render()
{
	//描画していない場合は処理終了.
	if (m_bDispFlag == false) {
		return;
	}

	m_pCSpriteUI->SetAlpha(m_fAlpha);
	//m_pCSpriteUI->SetColor(D3DXVECTOR3(0.01f, 0.01f, 0.01f));
	m_pCSpriteUI->SetPosition(m_vPos);
	m_pCSpriteUI->SetScale(m_fScale);
	m_pCDepthStencil->SetDepth(false);
	m_pCSpriteUI->Render();
	m_pCDepthStencil->SetDepth(true);
}

//========================================.
//		初期化処理関数.
//========================================.
void CNextSpeakCursor::Init()
{
	//m_pCSprite = m_pCResourceManager->GetSprite(enSprite::Cursol);
	m_pCSpriteUI = m_pCResourceManager->GetSpriteUI(enSpriteUI::NextSpeakCursor);

	m_fAcc = 1.0f;

	m_fAlpha = ALPHA_MAX;
	m_fScale = 1.0f;
}

//========================================.
//		解放処理関数.
//========================================.
void CNextSpeakCursor::Release()
{

}