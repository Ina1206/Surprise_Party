#include "CEndingUI.h"

/*******************************************
*		エンディングUIクラス.
********************/
CEndingUI::CEndingUI()
	: CEndingUI	(0)
{

}

CEndingUI::CEndingUI(const int& EvaluationNum)
	: m_pCSurpriseDegreeManager	(nullptr)
	, m_pCEvaluationManager		(nullptr)
	, m_pCPushEnter				(nullptr)
	, m_UpdateUIFlag			(0)
	, m_bFinishEvaluationFlag	(false)
	, m_EvaluationNum			(EvaluationNum)
	, m_bDisplayAllAtOnce		(false)
	, m_bChangeSceneFlag		(false)
{
	//初期化処理関数.
	Init();
}

CEndingUI::~CEndingUI()
{
	//解放処理関数.
	Release();
}

//==============================================.
//		更新処理関数.
//==============================================.
void CEndingUI::Update()
{
	if (m_UpdateUIFlag & PUSH_ENTER_FLAG) {
		//PushEnter更新処理関数.
		UpdatePushEnter();
	}

	if (m_bDisplayAllAtOnce == false) {
		//一気に描画するフラグ処理.
		if (GetAsyncKeyState(VK_RETURN) & 0x0001) {
			//スキップ音再生.
			if (m_bDisplayAllAtOnce == false) {
				m_pCPlaySoundManager->SetPlaySE(enSEType::Skip);
			}
			m_bDisplayAllAtOnce = true;
		}
	}

	if (m_UpdateUIFlag & SURPRISE_DEGREE_FLAG) {
		//驚かし度更新処理関数.
		UpdateSurpriseDegree();
	}

	if (m_UpdateUIFlag & EVALUATION_FLAG) {
		//評価更新処理関数.
		UpdateEvaluation();
	}
}

//==============================================.
//		描画処理関数.
//==============================================.
void CEndingUI::Render()
{
	//驚かし度描画処理関数.
	m_pCSurpriseDegreeManager->Render();
	//評価描画処理関数.
	m_pCEvaluationManager->Render();
	//PushEnter描画処理関数.
	m_pCPushEnter->Render();
}

//==============================================.
//		初期化処理関数.
//==============================================.
void CEndingUI::Init()
{
	//驚かし度.
	m_pCSurpriseDegreeManager = std::make_unique<CSurpriseDegreeManager>(m_EvaluationNum);
	//評価.
	m_pCEvaluationManager = std::make_unique<CEvaluationUIManager>(m_EvaluationNum);
	//PushEnter.
	m_pCPushEnter = std::make_unique<CPushEnter>();

	m_UpdateUIFlag = SURPRISE_DEGREE_FLAG;
}

//==============================================.
//		解放処理関数.
//==============================================.
void CEndingUI::Release()
{

}

//===============================================.
//		驚かし度更新処理関数.
//===============================================.
void CEndingUI::UpdateSurpriseDegree()
{
	//一気に描画するフラグ.
	m_pCSurpriseDegreeManager->SetDisplayAllAtOnce(m_bDisplayAllAtOnce);
	//更新処理関数.
	m_pCSurpriseDegreeManager->Update();
	if (m_pCSurpriseDegreeManager->GetAllDispFlag() == true) {
		m_UpdateUIFlag = EVALUATION_FLAG;
	}

}

//================================================.
//		評価更新処理関数.
//================================================.
void CEndingUI::UpdateEvaluation()
{
	//一気に描画するフラグ.
	m_pCEvaluationManager->SetDispAllAtOnce(m_bDisplayAllAtOnce);
	//更新処理関数.
	m_pCEvaluationManager->Update();

	if (m_pCEvaluationManager->GetFinishedAllDispFlag() == true) {
		m_bFinishEvaluationFlag = true;
		m_UpdateUIFlag = PUSH_ENTER_FLAG;
	}
}

//==================================================.
//		PushEnter更新処理関数.
//==================================================.
void CEndingUI::UpdatePushEnter()
{
	//更新処理関数.
	m_pCPushEnter->Update();

	//決定処理.
	if (GetAsyncKeyState(VK_RETURN) & 0x0001) {
		m_bChangeSceneFlag = true;
		m_pCPlaySoundManager->SetPlaySE(enSEType::SelectDecide);
	}
}