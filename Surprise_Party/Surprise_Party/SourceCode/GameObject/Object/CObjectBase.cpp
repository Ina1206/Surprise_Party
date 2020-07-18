#include "CObjectBase.h"

/********************************************
*		�I�u�W�F�N�g���N���X.
******************/
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
//		�`�揈���֐�.
//==============================================.
void CObjectBase::Render()
{
	//���W�ݒ�.
	m_pCMesh->SetPosition(m_vPos);
	//�p�x�ݒ�.
	m_pCMesh->SetRotation(m_vRot);
	//�傫���ݒ�.
	m_pCMesh->SetScale(m_fScale);
	//���ߒl��ݒ�.
	m_pCMesh->SetAlpha(m_fAlpha);
	//�`�揈���֐�.
	m_pCMesh->SetAlphaDepth(true);
	m_pCMesh->Render(m_mView, m_mProj, m_vCameraPos, m_stLight);
	m_pCMesh->SetAlphaDepth(false);
}