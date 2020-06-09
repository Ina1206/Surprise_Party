#include "CGameMain.h"

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
	m_vBackColor = D3DXVECTOR4(0.0f, 0.0f, 0.0f, 1.0f);

	//シーン管理クラスの更新処理関数.
	m_pCStageManager->UpDate();

	if (m_pCStageManager->GetFinishFlag() & m_pCStageManager->FINISH_NEXT_TITLE) {
		m_bChangeScene = true;
	}
	if (m_pCStageManager->GetFinishFlag() & m_pCStageManager->FINISH_NEXT_ENDING) {
		m_Evaluation = m_pCStageManager->GetAverageEvaluation();
		m_bChangeScene = true;
	}
}

//========================================.
//		描画処理関数.
//========================================.
void CGameMain::Render()
{
	//シーン管理クラスの描画処理関数.
	m_pCStageManager->Render(m_mView, m_mProj, m_vLightPos, m_vCameraPos);
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