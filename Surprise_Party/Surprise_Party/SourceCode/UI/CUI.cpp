#include "CUI.h"

/*************************************
*		UIƒNƒ‰ƒX.
*****/
CUI::CUI()
	: m_pCResourceManager	(nullptr)
	, m_pCDepthStencil		(nullptr)
	, m_vPos				(0.0f, 0.0f, 0.0f)
	, m_vRot				(0.0f, 0.0f, 0.0f)
	, m_fScale				(UI_INIT_SCALE)
	, m_fAlpha				(ALPHA_MAX)
{
	m_pCResourceManager = CResourceManager::GetResourceManagerInstance();
	m_pCDepthStencil	= CDepth_Stencil::GetDepthStencilInstance();
}

CUI::~CUI()
{

}