#include "CPainting.h"

/************************************
*	�G��N���X.
****************/
CPainting::CPainting()
{
	//�����������֐�.
	Init();
}

CPainting::~CPainting()
{
	//��������֐�.
	Release();
}

//==============================.
//		�X�V�����֐�.
//==============================.
void CPainting::Update()
{
	//�I�u�W�F�N�g���ߒl�ύX�����֐�.
	ObjectAlpha();
}

//==============================.
//		�����������֐�.
//==============================.
void CPainting::Init()
{
	m_pCMesh = m_pCResourceManager->GetStaticMesh(enStaticMeshType::Painting);
	m_fScale = SCALE;
}

//==============================.
//		��������֐�.
//==============================.
void CPainting::Release()
{
	m_pCMesh = nullptr;
}