#include "CBookShelf.h"

/************************************
*		本棚クラス.
*****************/
CBookShelf::CBookShelf()
{
	//初期化処理関数.
	Init();
}

CBookShelf::~CBookShelf()
{
	//解放処理関数.
	Release();
}

//===================================.
//		更新処理関数.
//===================================.
void CBookShelf::Update()
{
	//オブジェクト透過値変更処理関数.
	ObjectAlpha();
}

//===================================.
//		初期化処理関数.
//===================================.
void CBookShelf::Init()
{
	m_pCMesh = m_pCResourceManager->GetStaticMesh(enStaticMeshType::BookShelf);
	m_fScale = 0.1f;
}

//==================================.
//		解放処理関数.
//==================================.
void CBookShelf::Release()
{

}