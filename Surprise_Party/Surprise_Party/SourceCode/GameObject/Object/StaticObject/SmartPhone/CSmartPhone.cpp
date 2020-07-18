#include "CSmartPhone.h"

/********************************************
*		�X�}�[�g�t�H���N���X
*************/
CSmartPhone::CSmartPhone()
	: m_vUV	(0.0f, 0.0f)
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
	//�X�N���[������.
	m_vUV.y += SCROLL_SPEED;
	
	if(m_vUV.y >= SCROLL_MAX){
		m_vUV.y = 0.0f;
	}
	
}

//============================================.
//		�`�揈���֐�.
//============================================.
void CSmartPhone::Render()
{
	m_pCMesh->SetPosition(m_vPos);
	m_pCMesh->SetRotation(m_vRot);
	m_pCMesh->SetScale(SCALE);
	m_pCMesh->SetUV(m_vUV);
	m_pCMesh->Render(m_mView, m_mProj, m_vCameraPos, m_stLight);
}

//============================================.
//		�����������֐�.
//============================================.
void CSmartPhone::Init()
{
	m_pCMesh = m_pCResourceManager->GetStaticMesh(enStaticMeshType::Phone);
	
	m_vRot.x = static_cast<float>(D3DXToRadian(ROT.x));
	m_vRot.y = static_cast<float>(D3DXToRadian(ROT.y));
	m_vRot.z = static_cast<float>(D3DXToRadian(ROT.z));
}

//============================================.
//		��������֐�.
//============================================.
void CSmartPhone::Release()
{

}