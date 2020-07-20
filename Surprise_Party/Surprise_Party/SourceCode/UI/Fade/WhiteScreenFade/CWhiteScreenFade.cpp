#include "CWhiteScreenFade.h"

/******************************************
*		白スクリーンフェードクラス.
************/
CWhiteScreenFade::CWhiteScreenFade()
	: m_pCSpriteUI	(nullptr)
	, m_vPos		(0.0f, 0.0f, 0.0f)
	, m_fAlpha		(ALPHA_MAX)
	, m_FadeFlag	(0)
	, m_OldFadeFlag	(0)
	, m_fAlphaRatio	(0.0f)
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
		//フェードイン処理関数.
		FadeIn();
		return;
	}

	//フェードアウト処理関数.
	FadeOut();
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
	//透過値の割合.
	const float ALPHA_LENGTH = fabsf(ALPHA_MIN - ALPHA_MAX);
	m_fAlphaRatio = fabsf(m_fAlpha - ALPHA_MAX) / ALPHA_LENGTH;

	if (m_fAlpha > ALPHA_MAX) {
		m_fAlpha = ALPHA_MAX;
		m_FadeFlag = FADE_FINISH_FLAG;
	}
}

//===========================================.
//		フェードアウト処理関数.
//===========================================.
void CWhiteScreenFade::FadeOut()
{
	m_fAlpha -= ALPHA_SPEED;
	//透過値の割合.
	const float ALPHA_LENGTH = fabsf(ALPHA_MIN - ALPHA_MAX);
	m_fAlphaRatio = ALPHA_MAX - fabsf(m_fAlpha - ALPHA_MIN) / ALPHA_LENGTH;

	if (m_fAlpha < ALPHA_MIN) {
		m_fAlpha = ALPHA_MIN;
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

	m_fAlpha = ALPHA_MAX;
}