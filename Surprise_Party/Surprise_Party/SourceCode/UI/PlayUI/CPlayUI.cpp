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
//		�����ݒ菈���֐�.
//==========================================.
void CPlayUI::SettingInit()
{
	_ASSERT_EXPR(m_pCSpriteUI.size() != 0, L"m_pCSpriteUI.size() == 0");

	m_vUIPos.resize(m_pCSpriteUI.size());
	m_vUIScale.resize(m_pCSpriteUI.size());
	m_vPatternNo.resize(m_pCSpriteUI.size());
	m_fUIAlpha.resize(m_pCSpriteUI.size());

	for (unsigned int ui = 0; ui < m_pCSpriteUI.size(); ui++) {
		m_vUIPos[ui]		= INIT_POS;
		m_vUIScale[ui]		= SCALE_MAX;
		m_vPatternNo[ui]	= INIT_PATTARN_NO;
		m_fUIAlpha[ui]		= ALPHA_MAX;
	}
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