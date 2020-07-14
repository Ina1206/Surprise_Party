#include "CNextSpeakCursor.h"

/*****************************************
*		次の会話のカーソルクラス.
*****************/
CNextSpeakCursor::CNextSpeakCursor()
	: m_pCSpriteUI	(nullptr)
	, m_vDispPos	(0.0f, 0.0f, 0.0f)
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
		m_vPos = m_vDispPos;
		m_fAcc = 0.0f;
		return;
	}

	if (m_fAcc < ACC_SPEED) {
		m_vPos.y = m_vDispPos.y;
	}

	//上下移動.
	m_vPos.x = m_vDispPos.x;
	m_fAcc += ACC_SPEED;
	if (m_vPos.y > m_vDispPos.y) {
		m_fAcc = 0.0f;
	}

	m_vPos.y += m_fAcc - GRAVITY;
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
	m_pCSpriteUI = m_pCResourceManager->GetSpriteUI(enSpriteUI::NextSpeakCursor);

	m_fAcc = 0.0f;

	m_fAlpha = ALPHA_MAX;
	m_fScale = SCALE_MAX;
}

//========================================.
//		解放処理関数.
//========================================.
void CNextSpeakCursor::Release()
{

}