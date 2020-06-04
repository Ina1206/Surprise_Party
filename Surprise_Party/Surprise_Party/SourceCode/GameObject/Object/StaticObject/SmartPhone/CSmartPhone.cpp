#include "CSmartPhone.h"

/********************************************
*		�X�}�[�g�t�H���N���X
*************/
CSmartPhone::CSmartPhone()
{
	//�����������֐�.
	Init();
}

CSmartPhone::~CSmartPhone()
{
	//��������֐�.
	Release();
}

//============================================.
//		�X�V�����֐�.
//============================================.
void CSmartPhone::Update()
{

}

//============================================.
//		�`�揈���֐�.
//============================================.
void CSmartPhone::Render()
{
	m_pCMesh->SetPosition(m_vPos);
	m_pCMesh->SetScale(0.1f);
	m_pCMesh->Render(m_mView, m_mProj, m_vCameraPos, m_stLight);
}

//============================================.
//		�����������֐�.
//============================================.
void CSmartPhone::Init()
{
	m_pCMesh = m_pCResourceManager->GetStaticMesh(enStaticMeshType::Phone);
}

//============================================.
//		��������֐�.
//============================================.
void CSmartPhone::Release()
{

}