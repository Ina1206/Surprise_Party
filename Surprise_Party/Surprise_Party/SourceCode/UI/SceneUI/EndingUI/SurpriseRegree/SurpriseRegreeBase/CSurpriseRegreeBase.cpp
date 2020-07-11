#include "CSurpriseRegreeBase.h"

/****************************************
*		�������x�̊��N���X.
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
//		�`�揈���֐�.
//========================================.
void CSurpriseRegreeBase::Render()
{
	m_pCSpriteUI->SetAlpha(m_fAlpha);
	m_pCSpriteUI->SetEachSizeScale(m_vEatchSizeScale);
	m_pCDepthStencil->SetDepth(false);
	m_pCSpriteUI->Render();
	m_pCDepthStencil->SetDepth(true);
}