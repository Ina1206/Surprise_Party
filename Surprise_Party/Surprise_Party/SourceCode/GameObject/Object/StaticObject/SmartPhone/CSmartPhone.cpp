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
	m_pCMesh->SetRotation(m_vRot);
	m_pCMesh->SetScale(0.05f);
	m_pCMesh->Render(m_mView, m_mProj, m_vCameraPos, m_stLight);
}

//============================================.
//		初期化処理関数.
//============================================.
void CSmartPhone::Init()
{
	m_pCMesh = m_pCResourceManager->GetStaticMesh(enStaticMeshType::Phone);
	
	m_vRot.x = static_cast<float>(D3DXToRadian(30.0f));
	m_vRot.y = static_cast<float>(D3DXToRadian(45.0f));
	m_vRot.z = static_cast<float>(D3DXToRadian(-15.0f));
}

//============================================.
//		解放処理関数.
//============================================.
void CSmartPhone::Release()
{

}