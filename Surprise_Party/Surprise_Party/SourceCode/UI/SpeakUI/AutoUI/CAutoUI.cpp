#include "CAutoUI.h"

/**********************************
*		自動再生時のUIクラス.
************/
CAutoUI::CAutoUI()
	: m_pCSpriteUI			(nullptr)
	, m_FlashingFlag		(0)
	, m_TransparentDirect	(1)
	, m_bTutorialFlag		(false)
{
	//初期化処理関数.
	Init();
}

CAutoUI::~CAutoUI()
{
	//解放処理関数.
	Release();
}

//=================================.
//		更新処理関数.
//=================================.
void CAutoUI::Update()
{
	m_vPos = NORMAL_POS;
	if (m_bTutorialFlag == true) {
		m_vPos = TUTORIAL_POS;
	}

	m_fAlpha += ALPHA_SPEED * m_TransparentDirect;

	//消えていく処理の時.
	if (m_FlashingFlag & DISAPPEAR_FLAG) {
		if (m_fAlpha < ALPHA_MIN) {
			m_fAlpha = ALPHA_MIN;
			m_FlashingFlag = APPEAR_FLAG;
			m_TransparentDirect *= CHANGE_DIRECT;
		}
		return;
	}

	//現れる処理の時.
	if (m_fAlpha > ALPHA_MAX) {
		m_fAlpha = ALPHA_MAX;
		m_FlashingFlag = DISAPPEAR_FLAG;
		m_TransparentDirect *= CHANGE_DIRECT;
	}
}

//=================================.
//		描画処理関数.
//=================================.
void CAutoUI::Render()
{
	//透過値.
	m_pCSpriteUI->SetAlpha(m_fAlpha);
	//座標.
	m_pCSpriteUI->SetPosition(m_vPos);
	//描画.
	m_pCDepthStencil->SetDepth(false);
	m_pCSpriteUI->Render();
	m_pCDepthStencil->SetDepth(true);
}

//=================================.
//		初期化処理関数.
//=================================.
void CAutoUI::Init()
{
	m_pCSpriteUI = m_pCResourceManager->GetSpriteUI(enSpriteUI::AutoString);
	m_TransparentDirect *= CHANGE_DIRECT;
	m_FlashingFlag = DISAPPEAR_FLAG;
	m_vPos.x -= m_pCResourceManager->GetSpriteUIState(enSpriteUI::AutoString).Disp.w;
}

//=================================.
//		解放処理関数.
//=================================.
void CAutoUI::Release()
{

}