#include "CTitle.h"

/**********************************
*		�^�C�g���N���X.
******/
CTitle::CTitle()
	: m_pCCameraTitle	(nullptr)
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
}

//======================================.
//		�`�揈���֐�.
//======================================.
void CTitle::Render()
{
	//�J�������W.
	const D3DXVECTOR3 m_vCameraPos = m_pCCameraTitle->GetPos();

}

//======================================.
//		�����������֐�.
//======================================.
void CTitle::Init()
{
	m_vBackColor = D3DXVECTOR4(0.5f, 0.0f, 0.0f, 1.0f);

	//�N���X���C���X�^���X��.
	m_pCCameraTitle.reset(new CCameraTitle());
}

//======================================.
//		��������֐�.
//======================================.
void CTitle::Release()
{

}