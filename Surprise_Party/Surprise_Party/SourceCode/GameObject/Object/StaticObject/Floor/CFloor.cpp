#include "CFloor.h"

/**************************************
*	床クラス.
************/
CFloor::CFloor()
{
	//初期化処理関数.
	Init();
}

CFloor::~CFloor()
{
	//解放処理関数.
	Release();
}

//=================================.
//		更新処理関数.
//=================================.
void CFloor::Update()
{

}

//=================================.
//		初期化処理関数.
//=================================.
void CFloor::Init()
{
	m_pCMesh = m_pCResourceManager->GetStaticMesh(enStaticMeshType::Floor);
	m_fScale = SCALE;
}

//=================================.
//		解放処理関数.
//=================================.
void CFloor::Release()
{
	m_pCMesh = nullptr;
}