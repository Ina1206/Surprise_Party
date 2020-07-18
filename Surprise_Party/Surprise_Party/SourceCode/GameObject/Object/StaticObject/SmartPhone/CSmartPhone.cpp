#include "CSmartPhone.h"

/********************************************
*		スマートフォンクラス
*************/
CSmartPhone::CSmartPhone()
	: m_vUV	(0.0f, 0.0f)
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
	//スクロール処理.
	m_vUV.y += SCROLL_SPEED;
	
	if(m_vUV.y >= SCROLL_MAX){
		m_vUV.y = 0.0f;
	}
	
}

//============================================.
//		描画処理関数.
//============================================.
void CSmartPhone::Render()
{
	m_pCMesh->SetPosition(m_vPos);
	m_pCMesh->SetRotation(m_vRot);
	m_pCMesh->SetScale(SCALE);
	m_pCMesh->SetUV(m_vUV);
	m_pCMesh->Render(m_mView, m_mProj, m_vCameraPos, m_stLight);
}

//============================================.
//		初期化処理関数.
//============================================.
void CSmartPhone::Init()
{
	m_pCMesh = m_pCResourceManager->GetStaticMesh(enStaticMeshType::Phone);
	
	m_vRot.x = static_cast<float>(D3DXToRadian(ROT.x));
	m_vRot.y = static_cast<float>(D3DXToRadian(ROT.y));
	m_vRot.z = static_cast<float>(D3DXToRadian(ROT.z));
}

//============================================.
//		解放処理関数.
//============================================.
void CSmartPhone::Release()
{

}