#include "CWhiteScreenFade.h"

/******************************************
*		白スクリーンフェードクラス.
************/
CWhiteScreenFade::CWhiteScreenFade()
	: m_pCSpriteUI	(nullptr)
	, m_vPos		(0.0f, 0.0f, 0.0f)
	, m_fAlpha		(ALPHA_MIN)
	, m_FadeFlag	(0)
	, m_OldFadeFlag	(0)
{
	//初期化処理関数.
	Init();
}

CWhiteScreenFade::~CWhiteScreenFade()
{
	//解放処理関数.
	Release();
}

//=========================================.
//		更新処理化数.
//=========================================.
void CWhiteScreenFade::Update()
{
	if (m_FadeFlag != m_OldFadeFlag) {
		//フェード前の初期化処理関数.
		InitFade();
	}

	m_OldFadeFlag = m_FadeFlag;

	if (m_FadeFlag & FADE_IN_FLAG) {
		FadeIn();
		return;
	}
}

//=========================================.
//		描画処理関数.
//=========================================.
void CWhiteScreenFade::Render()
{
	//描画例外処理.
	if (m_FadeFlag == 0) {
		return;
	}

	m_pCSpriteUI->SetPosition(m_vPos);
	m_pCSpriteUI->SetAlpha(m_fAlpha);
	CDepth_Stencil* m_pCDepthStencil = CDepth_Stencil::GetDepthStencilInstance();
	m_pCDepthStencil->SetDepth(false);
	m_pCSpriteUI->Render();
	m_pCDepthStencil->SetDepth(true);
}

//=========================================.
//		初期化処理関数.
//=========================================.
void CWhiteScreenFade::Init()
{
	m_pCSpriteUI = m_pCResourceManager->GetSpriteUI(enSpriteUI::WhiteScreen);
}

//=========================================.
//		解放処理関数.
//=========================================.
void CWhiteScreenFade::Release()
{

}

//=========================================.
//		フェードイン処理関数.
//=========================================.
void CWhiteScreenFade::FadeIn()
{
	m_fAlpha += ALPHA_SPEED;

	if (m_fAlpha > ALPHA_MAX) {
		m_fAlpha = ALPHA_MAX;
		m_FadeFlag = FADE_FINISH_FLAG;
	}
}

//===========================================.
//		フェード前の初期化処理関数.
//===========================================.
void CWhiteScreenFade::InitFade()
{
	if (m_FadeFlag & FADE_IN_FLAG) {
		m_fAlpha = ALPHA_MIN;
		return;
	}
}