#include "CSurpriseDegreeBase.h"

/****************************************
*		�������x�̊��N���X.
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
//		�`�揈���֐�.
//========================================.
void CSurpriseDegreeBase::Render()
{
	m_pCSpriteUI->SetAlpha(m_fAlpha);
	m_pCSpriteUI->SetEachSizeScale(m_vEatchSizeScale);
	m_pCDepthStencil->SetDepth(false);
	m_pCSpriteUI->Render();
	m_pCDepthStencil->SetDepth(true);
}
