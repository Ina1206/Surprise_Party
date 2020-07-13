#include "CPushEnter.h"

/********************************************
*		PushEnterクラス.
***********************/
CPushEnter::CPushEnter()
	: m_pCSpriteUI		(nullptr)
	, m_AlphaAddDirect	(1)
{
	//初期化処理関数.
	Init();
}

CPushEnter::~CPushEnter()
{
	//解放処理関数.
	Release();
}

//============================================.
//		更新処理関数.
//============================================.
void CPushEnter::Update()
{
	m_fAlpha += TRANSPARENT_SPEED * m_AlphaAddDirect;

	//最大値以上の処理.
	if (m_fAlpha > ALPHA_MAX) {
		m_fAlpha = ALPHA_MAX;
		m_AlphaAddDirect *= CHANGE_ALPHA_ADD_DIRECT;
		return;
	}

	//最小値以下の処理.
	if (m_fAlpha < ALPHA_MIN) {
		m_fAlpha = ALPHA_MIN;
		m_AlphaAddDirect *= CHANGE_ALPHA_ADD_DIRECT;
	}

}

//============================================.
//		描画処理関数.
//============================================.
void CPushEnter::Render()
{
	//透過値.
	m_pCSpriteUI->SetAlpha(m_fAlpha);
	//大きさ.
	m_pCSpriteUI->SetScale(SCALE_MAX);
	//座標.
	m_pCSpriteUI->SetPosition(POS);
	//描画.
	m_pCDepthStencil->SetDepth(false);
	m_pCSpriteUI->Render();
	m_pCDepthStencil->SetDepth(true);
}

//============================================.
//		初期化処理関数.
//============================================.
void CPushEnter::Init()
{
	m_pCSpriteUI = m_pCResourceManager->GetSpriteUI(enSpriteUI::PushEnterString);
	m_fAlpha = ALPHA_MIN;
}

//============================================.
//		解放処理関数.						  
//============================================.
void CPushEnter::Release()
{

}