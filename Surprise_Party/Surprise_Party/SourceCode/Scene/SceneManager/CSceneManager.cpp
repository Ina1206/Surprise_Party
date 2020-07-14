#include "CSceneManager.h"

CSceneManager::CSceneManager()
	: m_pDevice11			(nullptr)
	, m_pContext11			(nullptr)
	, m_pCDepthStencil		(nullptr)
	, m_pCSceneBase			()
	, m_Color				(0.0f, 0.0f, 0.0f, 0.0f)
	, m_ChangeSceneCnt		(0)
	, m_SceneType			(0)
	, m_PausingFlag			(false)
	, m_StartFlag			(0)
	, m_pCDebugText			(nullptr)
	, m_FlyToSceneNum		(0)
	, m_FlyToSceneMax		(0)
	, m_bFlyToSceneFlag		(false)
	, m_pCPlaySoundManager	(nullptr)
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
	CSoundPlayManager* m_pCSoundPlayManager = CSoundPlayManager::GetSEPlayManagerInstance();
	m_pCSoundPlayManager->SetLoopSEPlay(CSoundResource::enBGM::Title, true);
	m_pCSoundPlayManager->Play();

	//シーンフェード更新処理関数.
	m_pCSceneFade->Update();

	m_Color = m_pCSceneBase[NORMAL_SCENE_NUM]->GetBackColor();

	//シーンに飛ぶ処理関数.
	FlyToScene();

	if (m_pCSceneFade->GetShutterFlag() & m_pCSceneFade->CHANGE_SCENE_FLAG) {
		//シーン変更処理関数.
		ChangeScene();
	}

	//フェード中はシーン関係の処理をさせない.
	if (m_pCSceneFade->GetShutterFlag() != 0) {
		if (m_StartFlag & INIT_SETTED_FLAG) {
			return;
		}
		m_StartFlag = INIT_SETTED_FLAG;
	}

#ifdef _DEBUG
	m_pCSceneBase[NORMAL_SCENE_NUM]->DebugSceneChange();
#endif	//#ifdef _DEBUG.

	//シーン変更時はシーン更新処理をさせない.
	if (m_pCSceneBase[NORMAL_SCENE_NUM]->GetChangeSceneFlag() == true) {
		m_pCSceneFade->SetShutterFlag(m_pCSceneFade->CLOSE_FLAG);
		return;
	}

	//ポーズ処理関数.
	Pause();

	//シーンの更新処理関数.
	int m_UsingSceneNum = NORMAL_SCENE_NUM;
	for (unsigned int scene = 0; scene < m_pCSceneBase.size(); scene++) {
		m_pCSceneBase[scene]->SetPauseFlag(m_PausingFlag);
	}
	if (m_PausingFlag == true) {
		m_UsingSceneNum = PAUSE_SCENE_NUM;
	}
	m_pCSceneBase[m_UsingSceneNum]->UpDate();
	m_PausingFlag = m_pCSceneBase[m_UsingSceneNum]->GetPauseFlag();
}

//===========================================.
//		描画処理関数.
//===========================================.
void CSceneManager::Render(const D3DXMATRIX& mProj)
{
	for (unsigned int scene = 0; scene < m_pCSceneBase.size(); scene++) {
		//シーンの描画初期設定処理関数.
		m_pCSceneBase[scene]->RenderInitSetting(mProj);
		//シーンの描画処理関数.
		m_pCSceneBase[scene]->Render();

		if (m_PausingFlag == false) {
			break;
		}
	}

	//デバッグ用のフォント描画処理関数.
	if (m_bFlyToSceneFlag == true) {
		RenderDebugFont();
	}

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

	CSoundPlayManager* m_pCPlaySoundManager = CSoundPlayManager::GetSEPlayManagerInstance();
	m_pCPlaySoundManager->Init(m_hWnd);


	//デプスステンシル.
	m_pCDepthStencil = CDepth_Stencil::GetDepthStencilInstance();
	m_pCDepthStencil->Init(m_pDevice11, m_pContext11);

	//フェード.
	m_pCSceneFade.reset(new CSceneFade());

	//デバッグテキスト.
	m_pCDebugText = m_pCResourceManager->GetDebugText();


	//シーン初期設定.
	m_SceneType = static_cast<int>(enSceneType::Title);
	m_pCSceneBase.emplace_back(std::make_unique<CTitle>());

	m_pCSceneBase.emplace_back(std::make_unique<CPause>());

	m_pCSceneFade->SetShutterFlag(m_pCSceneFade->OPEN_FLAG);

}

//=============================================.
//		シーン変更処理関数.
//=============================================.
void CSceneManager::ChangeScene()
{
	if (m_bFlyToSceneFlag == false) {
		//次のシーンに進む処理関数.
		NextScene();
	}


	switch (static_cast<enSceneType>(m_SceneType)) {
	case enSceneType::Title:
		m_pCSceneBase[NORMAL_SCENE_NUM].reset();
		m_pCSceneBase[NORMAL_SCENE_NUM] = std::make_unique<CTitle>();
		break;
	case enSceneType::GameMain:
		m_pCSceneBase[NORMAL_SCENE_NUM].reset();
		m_pCSceneBase[NORMAL_SCENE_NUM] = std::make_unique<CGameMain>();
		break;
	case enSceneType::Ending:
		const int Evaluation = m_pCSceneBase[NORMAL_SCENE_NUM]->GetEvaluation();
		m_pCSceneBase[NORMAL_SCENE_NUM].reset();
		m_pCSceneBase[NORMAL_SCENE_NUM] = std::make_unique<CEnding>();
		m_pCSceneBase[NORMAL_SCENE_NUM]->SetEvaluation(Evaluation);
		if (m_bFlyToSceneFlag == true) {
			m_pCSceneBase[NORMAL_SCENE_NUM]->SetEvaluation(m_FlyToSceneEvaluation);
		}
		break;
	}

	m_StartFlag = 0;
	//フェード開ける処理.
	m_pCSceneFade->SetShutterFlag(m_pCSceneFade->OPEN_FLAG);

	//シーンへ飛んだ場合はフラグを降ろす.
	if (m_bFlyToSceneFlag == true) {
		m_bFlyToSceneFlag = false;
	}
}

//==========================================.
//		次のシーンに進む処理関数.
//==========================================.
void CSceneManager::NextScene()
{
	//次のシーンへ.
	m_SceneType++;
	if (m_SceneType >= static_cast<int>(enSceneType::Max)) {
		m_SceneType = static_cast<int>(enSceneType::Start);
	}

	//タイトルに移動.
	if (m_pCSceneBase[NORMAL_SCENE_NUM]->GetTitleFlag() == true) {
		m_SceneType = static_cast<int>(enSceneType::Title);
	}
}

//==========================================.
//		ポーズ処理関数.
//==========================================.
void CSceneManager::Pause()
{
	//ゲームメイン以外では処理しない.
	if (m_SceneType != static_cast<int>(enSceneType::GameMain)) {
		return;
	}

	if (GetAsyncKeyState(VK_F1) & 0x0001) {
		if (m_PausingFlag == true) {
			m_PausingFlag = false;
		}
		else {
			m_PausingFlag = true;
		}
	}

}

//===========================================.
//		シーンに飛ぶ処理関数.
//===========================================.
void CSceneManager::FlyToScene()
{
	//シーンに飛ぶ処理開始.
	if (GetAsyncKeyState(VK_F2) & 0x0001) {
		if (m_bFlyToSceneFlag == true) {
			m_bFlyToSceneFlag = false;
			return;
		}
		m_bFlyToSceneFlag = true;
	}

	//例外処理.
	if (m_bFlyToSceneFlag == false) {
		return;
	}

	if (GetAsyncKeyState(VK_UP) & 0x0001) {
		m_FlyToSceneNum--;
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x0001) {
		m_FlyToSceneNum++;
	}

	//上限設定.
	if (m_FlyToSceneNum < 0) {
		m_FlyToSceneNum = 0;
	}
	if (m_FlyToSceneNum > m_FlyToSceneMax - 1) {
		m_FlyToSceneNum = m_FlyToSceneMax - 1;
	}

	//飛ぶシーン決定処理.
	if(GetAsyncKeyState(VK_RETURN) & 0x0001){
		//シャッターを閉じるよう処理.
		m_pCSceneFade->SetShutterFlag(m_pCSceneFade->CLOSE_FLAG);

		//エンディングの3つの設定処理.
		if (m_FlyToSceneNum >= static_cast<int>(enSceneType::Ending)) {
			m_SceneType = static_cast<int>(enSceneType::Ending);
			m_FlyToSceneEvaluation = m_FlyToSceneNum - m_SceneType;
			return;
		}

		m_SceneType = m_FlyToSceneNum;
	}
}

//===========================================.
//		デバッグ用のフォント描画処理関数.
//===========================================.
void CSceneManager::RenderDebugFont()
{
	//飛ぶシーン名.
	const std::vector<std::string> stSceneName = {
		"Title",
		"GameMain",
		"LowEvaluationEnding",
		"IntermediateEvaluationEnding",
		"HightEvaluationEnding",
		">"
	};

	//飛ぶシーン名最大値.
	const int SceneMax = static_cast<int>(stSceneName.size()) - 1;
	//カーソル番号.
	const int CursorNum = static_cast<int>(stSceneName.size()) - 1;
	//描画処理.
	m_pCDepthStencil->SetDepth(false);
	for (int Scene = 0; Scene < SceneMax; Scene++) {
		m_pCDebugText->Render(stSceneName[Scene].c_str(), 50.0f, 200.0f + (30.0f * Scene));
	}
	m_pCDebugText->Render(stSceneName[CursorNum].c_str(), 20.0f, 200.0f + (30.0f * m_FlyToSceneNum));
	m_pCDepthStencil->SetDepth(true);

	m_FlyToSceneMax = SceneMax;
}