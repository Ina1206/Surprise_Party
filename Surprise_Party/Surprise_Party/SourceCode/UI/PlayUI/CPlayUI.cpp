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
//		�`�揈���֐�.
//==========================================.
void CPlayUI::Render()
{
	if (m_pCSpriteUI.size() == 0) {
		return;
	}

	for (unsigned int UI = 0; UI < m_pCSpriteUI.size(); UI++) {
		//�p�^�[���ԍ�.
		m_pCSpriteUI[UI]->SetPattern(m_vPatternNo[UI]);
		//���W.
		m_pCSpriteUI[UI]->SetPosition(m_vUIPos[UI]);
		//�傫��.
		m_pCSpriteUI[UI]->SetEachSizeScale(m_vUIScale[UI]);
		//���ߒl.
		m_pCSpriteUI[UI]->SetAlpha(m_fUIAlpha[UI]);
		//�`�揈���֐�.
		m_pCDepthStencil->SetDepth(false);
		m_pCSpriteUI[UI]->Render();
		m_pCDepthStencil->SetDepth(true);
	}
}