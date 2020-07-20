#include "CGameMain.h"

/**************************************************
*		ステージ管理クラス.
********/
CGameMain::CGameMain()
	: m_pCStageManager	(nullptr)
{
	//初期化処理関数.
	Init();
}

CGameMain::~CGameMain()
{
	//解放処理関数.
	Release();
}

//========================================.
//		更新処理関数.
//========================================.
void CGameMain::UpDate()
{
	//外部で音量を調整しないよう防止.
	m_bChangeVolume = false;
	
	//シーン管理クラスの更新処理関数.
	m_pCStageManager->UpDate();

	//シーン変更（タイトルへの処理).
	if (m_pCStageManager->GetFinishFlag() & m_pCStageManager->FINISH_NEXT_TITLE) {
		m_bChangeScene = true;
		m_bTitle = true;
	}
	//平均評価.
	if (m_pCStageManager->GetFinishFlag() & m_pCStageManager->FINISH_NEXT_ENDING) {
		m_Evaluation = m_pCStageManager->GetAverageEvaluation();
		m_bChangeScene = true;
	}

	//外部で音量を調整できるように処理.
	if (m_bChangeScene == true) {
		m_bChangeVolume = true;
	}
}

//========================================.
//		描画処理関数.
//========================================.
void CGameMain::Render()
{
	//ポーズフラグ.
	m_pCStageManager->SetPauseFlag(m_bPauseFlag);
	//シーン管理クラスの描画処理関数.
	m_pCStageManager->Render(m_mView, m_mProj);
}

//========================================.
//		初期化処理関数.
//========================================.
void CGameMain::Init()
{
	//シーン管理クラスの初期化.
	m_pCStageManager.reset(new CStageManager());
	m_pCStageManager->Init();

}

//========================================.
//		解放処理関数.
//========================================.
void CGameMain::Release()
{
	//ステージ管理クラスの解放処理関数.
	m_pCStageManager->Release();

}