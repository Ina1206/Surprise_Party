#include "CSurpriseDegreeBase.h"

/****************************************
*		‹Á‚©‚µ“x‚ÌŠî’êƒNƒ‰ƒX.
**********************/
CSurpriseDegreeBase::CSurpriseDegreeBase()
	: m_pCSpriteUI		(nullptr)
	, m_vEatchSizeScale	(EATCH_SCALE_MAX)
{

}

CSurpriseDegreeBase::~CSurpriseDegreeBase()
{

}

//========================================.
//		•`‰æˆ—ŠÖ”.
//========================================.
void CSurpriseDegreeBase::Render()
{
	m_pCSpriteUI->SetAlpha(m_fAlpha);
	m_pCSpriteUI->SetEachSizeScale(m_vEatchSizeScale);
	m_pCDepthStencil->SetDepth(false);
	m_pCSpriteUI->Render();
	m_pCDepthStencil->SetDepth(true);
}
