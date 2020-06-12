#include "CTitle.h"

/**********************************
*		�^�C�g���N���X.
******/
CTitle::CTitle()
	: m_pCCameraTitle			(nullptr)
	, m_pCStaticObjectManager	(nullptr)
{
	//�����������֐�.
	Init();
}

CTitle::~CTitle()
{
	//��������֐�.
	Release();
}

//======================================.
//		�X�V�����֐�.
//======================================.
void CTitle::UpDate()
{
	//�^�C�g���p�J�����̍X�V�����֐�.
	m_pCCameraTitle->Update();
	//�J�������W.
	const D3DXVECTOR3 m_vCameraPos = m_pCCameraTitle->GetPos();

	//�ÓI�I�u�W�F�N�g�̍X�V�����֐�.
	m_pCStaticObjectManager->SetCameraPos(m_vCameraPos);
	m_pCStaticObjectManager->Updata();
}

//======================================.
//		�`�揈���֐�.
//======================================.
void CTitle::Render()
{
	//�J�������W.
	const D3DXVECTOR3 m_vCameraPos = m_pCCameraTitle->GetPos();

	//�ÓI�I�u�W�F�N�g�̕`�揈���֐�.
	//m_pCStaticObjectManager->Render(m_mView, m_mProj, );
}

//======================================.
//		�����������֐�.
//======================================.
void CTitle::Init()
{
	m_vBackColor = D3DXVECTOR4(0.5f, 0.0f, 0.0f, 1.0f);

	//�N���X���C���X�^���X��.
	m_pCCameraTitle.reset(new CCameraTitle());
	m_pCStaticObjectManager.reset(new CStaticObjectManager(0, 0));
}

//======================================.
//		��������֐�.
//======================================.
void CTitle::Release()
{

}