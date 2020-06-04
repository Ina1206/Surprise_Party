#include "CSmartPhone.h"

/********************************************
*		スマートフォンクラス
*************/
CSmartPhone::CSmartPhone()
{
	//初期化処理関数.
	Init();
}

CSmartPhone::~CSmartPhone()
{
	//解放処理関数.
	Release();
}

//============================================.
//		更新処理関数.
//============================================.
void CSmartPhone::Update()
{

}

//============================================.
//		描画処理関数.
//============================================.
void CSmartPhone::Render()
{
	m_pCMesh->SetPosition(m_vPos);
	m_pCMesh->SetScale(0.1f);
	m_pCMesh->Render(m_mView, m_mProj, m_vCameraPos, m_stLight);
}

//============================================.
//		初期化処理関数.
//============================================.
void CSmartPhone::Init()
{
	m_pCMesh = m_pCResourceManager->GetStaticMesh(enStaticMeshType::Phone);
}

//============================================.
//		解放処理関数.
//============================================.
void CSmartPhone::Release()
{

}