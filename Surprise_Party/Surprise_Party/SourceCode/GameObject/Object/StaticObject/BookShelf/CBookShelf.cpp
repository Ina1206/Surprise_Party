#include "CBookShelf.h"

/************************************
*		�{�I�N���X.
*****************/
CBookShelf::CBookShelf()
{
	//�����������֐�.
	Init();
}

CBookShelf::~CBookShelf()
{
	//��������֐�.
	Release();
}

//===================================.
//		�X�V�����֐�.
//===================================.
void CBookShelf::Update()
{
	//�I�u�W�F�N�g���ߒl�ύX�����֐�.
	ObjectAlpha();
}

//===================================.
//		�����������֐�.
//===================================.
void CBookShelf::Init()
{
	m_pCMesh = m_pCResourceManager->GetStaticMesh(enStaticMeshType::BookShelf);
	m_fScale = 0.1f;
}

//==================================.
//		��������֐�.
//==================================.
void CBookShelf::Release()
{

}