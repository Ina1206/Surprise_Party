#include "CSpeakBigGhost.h"

CSpeakBigGhost::CSpeakBigGhost()
	: m_pCSpriteUI	()
	, m_vPos		()
	, m_vRot		()
	, m_fAlpha		()
	, m_fScale		()
	, m_bSelectFlag	(false)
{
	//‰Šú‰»ˆ—ŠÖ”.
	Init();
}

CSpeakBigGhost::~CSpeakBigGhost()
{
	//‰ğ•úˆ—ŠÖ”.
	Release();
}

//====================================.
//		XVˆ—ŠÖ”.
//====================================.
void CSpeakBigGhost::Update()
{

}

//====================================.
//		•`‰æˆ—ŠÖ”.
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

	//•¶š‚Ì•`‰æ.
	m_pCFontResource->SetFontScale(m_fFontScale);
	m_pCFontResource->SetStartPos(m_vPos)
}

//====================================.
//		‰Šú‰»ˆ—ŠÖ”.
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
//		‰ğ•úˆ—ŠÖ”.
//====================================.
void CSpeakBigGhost::Release()
{

}