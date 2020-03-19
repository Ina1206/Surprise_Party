#include "CSpeakBigGhost.h"

CSpeakBigGhost::CSpeakBigGhost()
	: m_pCSpriteUI	()
	, m_vPos		()
	, m_vRot		()
	, m_fAlpha		()
	, m_fScale		()
	, m_bSelectFlag	(false)
{
	//初期化処理関数.
	Init();
}

CSpeakBigGhost::~CSpeakBigGhost()
{
	//解放処理関数.
	Release();
}

//====================================.
//		更新処理関数.
//====================================.
void CSpeakBigGhost::Update()
{

}

//====================================.
//		描画処理関数.
//====================================.
void CSpeakBigGhost::Render()
{
	for (unsigned int ui = 0; ui < m_pCSpriteUI.size(); ui++) {
		m_pCSpriteUI[ui]->SetAlpha(m_fAlpha[ui]);
		m_pCSpriteUI[ui]->SetScale(m_fScale[ui]);
		m_pCSpriteUI[ui]->SetPosition(m_vPos[ui]);
		m_pCDepthStencil->SetDepth(false);
		m_pCSpriteUI[ui]->Render();
		m_pCDepthStencil->SetDepth(true);
	}

	//文字の描画.
	m_pCFontResource->SetFontScale(m_fFontScale);
	m_pCFontResource->SetStartPos(m_vPos)
}

//====================================.
//		初期化処理関数.
//====================================.
void CSpeakBigGhost::Init()
{
	m_pCSpriteUI.resize(3);
	m_vPos.resize(m_pCSpriteUI.size());
	m_vRot.resize(m_pCSpriteUI.size());
	m_fAlpha.resize(m_pCSpriteUI.size());
	m_fScale.resize(m_pCSpriteUI.size());

	m_pCSpriteUI[0] = m_pCResourceManager->GetSpriteUI(enSpriteUI::TextBox);
	for (int ui = 1; ui < m_pCSpriteUI.size(); ui++) {
		m_pCSpriteUI[ui] = m_pCResourceManager->GetSpriteUI(enSpriteUI::TextBoxSmall);
	}

}

//====================================.
//		解放処理関数.
//====================================.
void CSpeakBigGhost::Release()
{

}