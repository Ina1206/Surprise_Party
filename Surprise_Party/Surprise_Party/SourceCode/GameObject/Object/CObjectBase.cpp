#include "CObjectBase.h"

CObjectBase::CObjectBase()
	: m_pCMesh				(nullptr)
	, m_pCDepthStenceil		(nullptr)
	, m_fAlpha				(1.0f)
{
	m_pCDepthStenceil = CDepth_Stencil::GetDepthStencilInstance();
}

CObjectBase::~CObjectBase()
{
	m_pCDepthStenceil = nullptr;
}

//==============================================.
//		•`‰æˆ—ŠÖ”.
//==============================================.
void CObjectBase::Render()
{
	//À•WÝ’è.
	m_pCMesh->SetPosition(m_vPos);
	//Šp“xÝ’è.
	m_pCMesh->SetRotation(m_vRot);
	//‘å‚«‚³Ý’è.
	m_pCMesh->SetScale(m_fScale);
	//“§‰ß’l‚ðÝ’è.
	m_pCMesh->SetAlpha(m_fAlpha);
	//•`‰æˆ—ŠÖ”.
	m_pCMesh->SetAlphaDepth(true);
	m_pCMesh->Render(m_mView, m_mProj, m_vCameraPos, m_stLight);
	m_pCMesh->SetAlphaDepth(false);
}