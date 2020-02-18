#include "CSceneManager.h"

CSceneManager::CSceneManager()
	: m_pDevice11		(nullptr)
	, m_pContext11		(nullptr)
	, m_pCSceneBase		(nullptr)
	, m_Color			(0.0f, 0.0f, 0.0f, 0.0f)
	, m_ChangeSceneCnt	(0)
	, m_SceneType		(0)
{

}

CSceneManager::~CSceneManager()
{

}

//==========================================.
//		初期化処理関数.
//==========================================.
void CSceneManager::Init(HWND hWnd, LPDIRECT3DDEVICE9 pDevice9, ID3D11Device* pDevice11, ID3D11DeviceContext* pContext11)
{
	m_hWnd			= hWnd;
	m_pDevice9		= pDevice9;
	m_pDevice11		= pDevice11;
	m_pContext11	= pContext11;
}

//==========================================.
//		更新処理関数.
//==========================================.
void CSceneManager::UpDate()
{

	//シーンフェード更新処理関数.
	m_pCSceneFade->UpDate();

	m_Color = m_pCSceneBase->GetBackColor();

	if (m_pCSceneFade->GetShutterFlag() & m_pCSceneFade->CHANGE_SCENE_FLAG) {
		//シーン変更処理関数.
		ChangeScene();
	}

	//フェード中はシーン関係の処理をさせない.
	if (m_pCSceneFade->GetShutterFlag() != 0) {
		return;
	}

#ifdef _DEBUG
	m_pCSceneBase->DebugSceneChange();
#endif	//#ifdef _DEBUG.

	//シーン変更時はシーン更新処理をさせない.
	if (m_pCSceneBase->GetChangeSceneFlag() == true) {
		m_pCSceneFade->SetShutterFlag(m_pCSceneFade->CLOSE_FLAG);
		return;
	}

	//シーンの更新処理関数.
	m_pCSceneBase->UpDate();

}

//===========================================.
//		描画処理関数.
//===========================================.
void CSceneManager::Render(const D3DXMATRIX& mView, const D3DXMATRIX& mProj, const D3DXVECTOR3& vLightPos, const D3DXVECTOR3& vCameraPos)
{
	//シーンの描画初期設定処理関数.
	m_pCSceneBase->RenderInitSetting(mView, mProj, vLightPos, vCameraPos);
	//シーンの描画処理関数.
	m_pCSceneBase->Render();

	//フェード描画処理関数.
	if (m_pCSceneFade->GetShutterFlag() != 0) {
		m_pCSceneFade->Render();
	}
}

//===========================================.
//		解放処理関数.
//===========================================.
void CSceneManager::Release()
{
	//リソースクラス削除.
	CResourceManager* m_pCResourceManager = CResourceManager::GetResourceManagerInstance();
	m_pCResourceManager->Release();

	m_pContext11	= nullptr;
	m_pDevice11		= nullptr;
}

//============================================.
//		読み込み処理関数.
//============================================.
void CSceneManager::Load()
{
	//描画用の読み込み管理クラスの読み込み処理関数.
	CResourceManager* m_pCResourceManager = CResourceManager::GetResourceManagerInstance();
	m_pCResourceManager->Load(m_hWnd, m_pDevice9, m_pDevice11, m_pContext11);

	//ファイル用読み込み管理クラスの読み込み処理関数.
	CFileResource*	m_pCFileResource = CFileResource::GetResourceInstance();
	m_pCFileResource->Load();


	CDepth_Stencil* m_pCDepthStencil = CDepth_Stencil::GetDepthStencilInstance();
	m_pCDepthStencil->Init(m_pDevice11, m_pContext11);

	//フェード.
	m_pCSceneFade.reset(new CSceneFade());


	//シーン初期設定.
	//m_SceneType = static_cast<int>(enSceneType::Title);
	//m_pCSceneBase.reset(new CTitle());
	m_SceneType = static_cast<int>(enSceneType::GameMain);
	m_pCSceneBase.reset(new CGameMain());
	m_pCSceneFade->SetShutterFlag(m_pCSceneFade->OPEN_FLAG);

}

//=============================================.
//		シーン変更処理関数.
//=============================================.
void CSceneManager::ChangeScene()
{
	//次のシーンへ.
	m_SceneType++;
	if (m_SceneType >= static_cast<int>(enSceneType::Max)) {
		m_SceneType = static_cast<int>(enSceneType::Start);
	}

	switch (static_cast<enSceneType>(m_SceneType)) {
	case enSceneType::Title:
		m_pCSceneBase.reset(new CTitle());
		break;
	case enSceneType::Tutorial:
		m_pCSceneBase.reset(new CTutorial());
		break;
	case enSceneType::GameMain:
		m_pCSceneBase.reset(new CGameMain());
		break;
	case enSceneType::Ending:
		m_pCSceneBase.reset(new CEnding());
		break;
	}

	m_pCSceneFade->SetShutterFlag(m_pCSceneFade->OPEN_FLAG);
}