#include "CNextSpeakCursor.h"

/*****************************************
*		次の会話のカーソルクラス.
*****************/
CNextSpeakCursor::CNextSpeakCursor()
	: m_pCSprite	(nullptr)
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

	m_fAcc -= 0.05f;
	if (m_vPos.y < m_vStartPos.y) {
		m_fAcc = 1.0f;
	}

	m_vPos.y += m_fAcc - 0.5f;
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

	m_pCSprite->SetAlpha(m_fAlpha);
	m_pCSprite->SetColor(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pCSprite->SetPosition(m_vPos);
	m_pCSprite->SetScale(D3DXVECTOR3(m_fScale, m_fScale, m_fScale));
	m_pCSprite->Render(m_mView, m_mProj, m_vCameraPos);
}

//========================================.
//		初期化処理関数.
//========================================.
void CNextSpeakCursor::Init()
{
	m_pCSprite = m_pCResourceManager->GetSprite(enSprite::Cursol);

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