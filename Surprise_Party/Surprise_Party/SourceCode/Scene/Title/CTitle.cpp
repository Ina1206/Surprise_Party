#include "CTitle.h"

/**********************************
*		タイトルクラス.
******/
CTitle::CTitle()
	: m_pCCameraTitle			(nullptr)
	, m_pCFrontstageLight		(nullptr)
	, m_pCStaticObjectManager	(nullptr)
	, m_pCMoveObjectManager		(nullptr)
	, m_pCWorkGhostManager		(nullptr)
	, m_pCTitleUI				(nullptr)
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

	//動的オブジェクトの更新処理関数.
	m_pCMoveObjectManager->SetCameraPos(m_vCameraPos);
	m_pCMoveObjectManager->UpDate();

	//お化け更新処理関数.
	m_pCWorkGhostManager->Update();

	//タイトルUI更新処理関数.
	m_pCTitleUI->Update();
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

	//ビュー行列の設定処理関数.
	SettingView();

	//お化けの描画処理関数.
	m_pCWorkGhostManager->Render(m_mView, m_mProj, m_Light, m_vCameraPos);
	//スイッチの描画処理関数.
	m_pCMoveObjectManager->RenderSwitch(m_mView, m_mProj, m_Light);
	//静的オブジェクトの描画処理関数.
	m_pCStaticObjectManager->Render(m_mView, m_mProj, m_vCameraPos, m_Light);
	//動的オブジェクトの描画処理関数.
	m_pCMoveObjectManager->Render(m_mView, m_mProj, m_Light);
	//動的オブジェクト前エフェクトの描画処理関数.
	m_pCMoveObjectManager->EffectRender();

	//タイトルUI描画処理関数.
	m_pCTitleUI->Render();
}

//======================================.
//		初期化処理関数.
//======================================.
void CTitle::Init()
{
	const int FILE_NUM = 0;	//ファイル番号.
	const int STAGE_NUM = 0;//ステージ番号.

	//クラスをインスタンス化.
	m_pCCameraTitle.reset(new CCameraTitle());
	m_pCFrontstageLight.reset(new CFrontstageLight());
	m_pCStaticObjectManager.reset(new CStaticObjectManager(FILE_NUM, STAGE_NUM));
	m_pCMoveObjectManager.reset(new CMoveObjectManager(FILE_NUM, STAGE_NUM));
	m_pCWorkGhostManager.reset(new CMainStageWorkGhostManager());
	m_pCTitleUI.reset(new CTitleUI());

	//初期処理関数.
	m_pCWorkGhostManager->Init(6, STAGE_NUM, m_pCStaticObjectManager->OBJECT_WIDTH);

	//ステージの最大値.
	const float m_fStageDistanceMax = m_pCStaticObjectManager->GetStageDistanceMax();

	//ステージの最大値設定.
	m_pCFrontstageLight->SettingAllLightPos(m_fStageDistanceMax);

	//UIを描画させない.
	m_pCMoveObjectManager->SetRenderUI(false);
}

//======================================.
//		解放処理関数.
//======================================.
void CTitle::Release()
{

}

//=======================================.
//		ビュー行列の設定処理関数.
//=======================================.
void CTitle::SettingView()
{
	const D3DXVECTOR3 m_vCameraLook = m_pCCameraTitle->GetLook();
	const D3DXVECTOR3 m_vCameraPos = m_pCCameraTitle->GetPos();

	const D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);	//上方(ベクトル).
	D3DXMatrixLookAtLH(
		&m_mView,								//(out)ビュー計算結果.
		&m_vCameraPos, &m_vCameraLook, &vUpVec);
}