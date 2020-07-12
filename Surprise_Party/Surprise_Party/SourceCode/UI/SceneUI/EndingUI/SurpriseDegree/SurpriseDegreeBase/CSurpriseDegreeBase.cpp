#include "CSurpriseDegreeBase.h"

/****************************************
*		驚かし度の基底クラス.
**********************/
CSurpriseDegreeBase::CSurpriseDegreeBase()
	: m_pCSpriteUI			(nullptr)
	, m_vEatchSizeScale		(EATCH_SCALE_MAX)
	, m_bDispFlag			(false)
	, m_bDisplayAllAtOnce	(false)
{

}

CSurpriseDegreeBase::~CSurpriseDegreeBase()
{

}

//========================================.
//		描画処理関数.
//========================================.
void CSurpriseDegreeBase::Render()
{
	m_pCSpriteUI->SetAlpha(m_fAlpha);
	m_pCSpriteUI->SetEachSizeScale(m_vEatchSizeScale);
	m_pCSpriteUI->SetPosition(m_vPos);
	m_pCDepthStencil->SetDepth(false);
	m_pCSpriteUI->Render();
	m_pCDepthStencil->SetDepth(true);
}
