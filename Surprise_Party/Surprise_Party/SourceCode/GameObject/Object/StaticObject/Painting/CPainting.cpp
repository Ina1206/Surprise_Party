#include "CPainting.h"

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
void CPainting::UpDate()
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
	m_fScale = 0.3f;
}

//==============================.
//		��������֐�.
//==============================.
void CPainting::Release()
{
	m_pCMesh = nullptr;
}