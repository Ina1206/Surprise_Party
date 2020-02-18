#include "CPlayUI.h"

CPlayUI::CPlayUI()
	: m_pCSpriteUI	()
	, m_vUIPos		()
	, m_vUIScale	()
	, m_vPatternNo	()
	, m_fUIAlpha	()
{

}

CPlayUI::~CPlayUI()
{

}

//==========================================.
//		描画処理関数.
//==========================================.
void CPlayUI::Render()
{
	if (m_pCSpriteUI.size() == 0) {
		return;
	}

	for (unsigned int UI = 0; UI < m_pCSpriteUI.size(); UI++) {
		//パターン番号.
		m_pCSpriteUI[UI]->SetPattern(m_vPatternNo[UI]);
		//座標.
		m_pCSpriteUI[UI]->SetPosition(m_vUIPos[UI]);
		//大きさ.
		m_pCSpriteUI[UI]->SetEachSizeScale(m_vUIScale[UI]);
		//透過値.
		m_pCSpriteUI[UI]->SetAlpha(m_fUIAlpha[UI]);
		//描画処理関数.
		m_pCDepthStencil->SetDepth(false);
		m_pCSpriteUI[UI]->Render();
		m_pCDepthStencil->SetDepth(true);
	}
}