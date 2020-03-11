#include "CFloor.h"

CFloor::CFloor()
{
	//‰Šú‰»ˆ—ŠÖ”.
	Init();
}

CFloor::~CFloor()
{
	//‰ğ•úˆ—ŠÖ”.
	Release();
}

//=================================.
//		XVˆ—ŠÖ”.
//=================================.
void CFloor::Update()
{

}

//=================================.
//		‰Šú‰»ˆ—ŠÖ”.
//=================================.
void CFloor::Init()
{
	m_pCMesh = m_pCResourceManager->GetStaticMesh(enStaticMeshType::Floor);
	m_fScale = 0.1f;
}

//=================================.
//		‰ğ•úˆ—ŠÖ”.
//=================================.
void CFloor::Release()
{
	m_pCMesh = nullptr;
}