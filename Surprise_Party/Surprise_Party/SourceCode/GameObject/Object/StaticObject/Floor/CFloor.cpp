#include "CFloor.h"

/**************************************
*	���N���X.
************/
CFloor::CFloor()
{
	//�����������֐�.
	Init();
}

CFloor::~CFloor()
{
	//��������֐�.
	Release();
}

//=================================.
//		�X�V�����֐�.
//=================================.
void CFloor::Update()
{

}

//=================================.
//		�����������֐�.
//=================================.
void CFloor::Init()
{
	m_pCMesh = m_pCResourceManager->GetStaticMesh(enStaticMeshType::Floor);
	m_fScale = 0.1f;
}

//=================================.
//		��������֐�.
//=================================.
void CFloor::Release()
{
	m_pCMesh = nullptr;
}