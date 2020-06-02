#include "CWorkGhostBase.h"

CWorkGhostBase::CWorkGhostBase()
	: m_pCSkinMesh	(nullptr)
	, m_pAnimCtrl	(nullptr)
	, m_pCMesh		(nullptr)
{
}

CWorkGhostBase::~CWorkGhostBase()
{
}

//========================================.
//		アニメーション初期化処理関数.
//========================================.
void CWorkGhostBase::InitAnimation()
{
	//スキンメッシュのアドレス取得.
	m_pCSkinMesh = m_pCResourceManager->GetSkinMesh(enSkinMeshType::DispGhost);

	//アニメーションコントローラのクローン作成.
	LPD3DXANIMATIONCONTROLLER	pAC = m_pCSkinMesh->GetAnimationController();
	if (FAILED(pAC->CloneAnimationController(
		pAC->GetMaxNumAnimationOutputs(),
		pAC->GetMaxNumAnimationSets(),
		pAC->GetMaxNumTracks(),
		pAC->GetMaxNumEvents(),
		&m_pAnimCtrl))) {
		_ASSERT_EXPR(false, L"現れるお化けのアニメーションコントローラのクローン作成失敗");
	}


}

//========================================.
//		現れるお化け描画処理関数.
//========================================.
void CWorkGhostBase::RenderDispGhost(const D3DXVECTOR3& vPos)
{
	//座標.
	m_pCSkinMesh->SetPosition(vPos);
	//大きさ.
	m_pCSkinMesh->SetScale(m_fScale);
	//角度.
	//m_pCSkinMesh->SetRotation(m_vRot);
	m_pCSkinMesh->SetRot(m_mPoint);
	//描画.
	m_pCSkinMesh->Render(m_mView, m_mProj, m_vCameraPos, m_stLight, m_pAnimCtrl);
}

//=========================================.
//	静的オブジェクトお化け初期化処理関数.
//=========================================.
void CWorkGhostBase::InitStaticMeshGhost()
{
	//メッシュの読み込みアドレス取得.
	m_pCMesh = m_pCResourceManager->GetStaticMesh(enStaticMeshType::SwitchPushGhost);
}

//=========================================.
//		スイッチお化け描画処理関数.
//=========================================.
void CWorkGhostBase::RenderSwitchGhost(const D3DXVECTOR3& vPos)
{
	m_pCMesh->SetPosition(vPos);
	m_pCMesh->SetScale(m_fScale);
	m_pCMesh->SetPrePos(D3DXVECTOR3(0.0f, -23.0f, 0.0f));
	m_pCMesh->Render(m_mView, m_mProj, m_vCameraPos, m_stLight);

}