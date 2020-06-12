#include "CTitle.h"

/**********************************
*		タイトルクラス.
******/
CTitle::CTitle()
	: m_pCCameraTitle			(nullptr)
	, m_pCFrontstageLight		(nullptr)
	, m_pCStaticObjectManager	(nullptr)
{
	//初期化処理関数.
	Init();
}

CTitle::~CTitle()
{
	//解放処理関数.
	Release();
}

//======================================.
//		更新処理関数.
//======================================.
void CTitle::UpDate()
{
	//タイトル用カメラの更新処理関数.
	m_pCCameraTitle->Update();
	//カメラ座標.
	const D3DXVECTOR3 m_vCameraPos = m_pCCameraTitle->GetPos();

	//ライト更新処理関数.
	m_pCFrontstageLight->SetCameraPos(m_vCameraPos);
	m_pCFrontstageLight->Update();

	//静的オブジェクトの更新処理関数.
	m_pCStaticObjectManager->SetCameraPos(m_vCameraPos);
	m_pCStaticObjectManager->Updata();
}

//======================================.
//		描画処理関数.
//======================================.
void CTitle::Render()
{
	//カメラ座標.
	const D3DXVECTOR3 m_vCameraPos = m_pCCameraTitle->GetPos();
	//ライト情報.
	const LIGHT	m_Light = m_pCFrontstageLight->GetLight();


	//静的オブジェクトの描画処理関数.
	m_pCStaticObjectManager->Render(m_mView, m_mProj, m_vCameraPos, m_Light);
}

//======================================.
//		初期化処理関数.
//======================================.
void CTitle::Init()
{
	m_vBackColor = D3DXVECTOR4(0.5f, 0.0f, 0.0f, 1.0f);

	//クラスをインスタンス化.
	m_pCCameraTitle.reset(new CCameraTitle());
	m_pCFrontstageLight.reset(new CFrontstageLight());
	m_pCStaticObjectManager.reset(new CStaticObjectManager(0, 0));

	//ステージの最大値.
	const float m_fStageDistanceMax = m_pCStaticObjectManager->GetStageDistanceMax();

	//ステージの最大値設定.
	m_pCFrontstageLight->SettingAllLightPos(m_fStageDistanceMax);
}

//======================================.
//		解放処理関数.
//======================================.
void CTitle::Release()
{

}