#include "CSurpriseRegreeBase.h"

/****************************************
*		驚かし度の基底クラス.
**********************/
CSurpriseRegreeBase::CSurpriseRegreeBase()
	: m_pCSpriteUI		(nullptr)
	, m_vEatchSizeScale	(EATCH_SCALE_MAX)
{

}

CSurpriseRegreeBase::~CSurpriseRegreeBase()
{

}

//========================================.
//		描画処理関数.
//========================================.
void CSurpriseRegreeBase::Render()
{
	m_pCSpriteUI->SetAlpha(m_fAlpha);
	m_pCSpriteUI->SetEachSizeScale(m_vEatchSizeScale);
	m_pCDepthStencil->SetDepth(false);
	m_pCSpriteUI->Render();
	m_pCDepthStencil->SetDepth(true);
}
