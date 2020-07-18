#include "CPainting.h"

/************************************
*	絵画クラス.
****************/
CPainting::CPainting()
{
	//初期化処理関数.
	Init();
}

CPainting::~CPainting()
{
	//解放処理関数.
	Release();
}

//==============================.
//		更新処理関数.
//==============================.
void CPainting::Update()
{
	//オブジェクト透過値変更処理関数.
	ObjectAlpha();
}

//==============================.
//		初期化処理関数.
//==============================.
void CPainting::Init()
{
	m_pCMesh = m_pCResourceManager->GetStaticMesh(enStaticMeshType::Painting);
	m_fScale = SCALE;
}

//==============================.
//		解放処理関数.
//==============================.
void CPainting::Release()
{
	m_pCMesh = nullptr;
}