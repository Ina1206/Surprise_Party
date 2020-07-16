#include "CEnding.h"
#include "HightEvaluationStage\CHightEvaluationStage.h"
#include "IntermediateEvaluationStage\CIntermediateEvaluationStage.h"
#include "LowEvaluationStage\CLowEvaluationStage.h"
#include "..\..\Sound\PlaySoundManager\CPlaySoundManager.h"

CEnding::CEnding()
	: m_pCEndingStageBase	(nullptr)
	, m_ChangeStageCnt		(0)
{
	//初期化処理関数.
	Init();
}

CEnding::~CEnding()
{
	//解放処理関数.
	Release();
}

//=================================.
//		更新処理関数.
//=================================.
void CEnding::UpDate()
{
	//評価置換処理関数.
	m_pCEndingStageBase->SetEvaluation(m_Evaluation);

	//更新処理関数.
	m_pCEndingStageBase->Update();

	//ステージ変更処理.
	if (m_pCEndingStageBase->GetChangeStage() == true) {
		ChangeStage();
	}
}

//==================================.
//		描画処理関数.
//==================================.
void CEnding::Render()
{
	m_pCEndingStageBase->RenderInitSetting(m_mProj);
	m_pCEndingStageBase->Render();
}

//==================================.
//		初期化処理関数.
//==================================.
void CEnding::Init()
{
	m_pCEndingStageBase.reset(new CBeforeResultStage());
}

//==================================.
//		解放処理関数.
//==================================.
void CEnding::Release()
{

}

//==================================.
//		ステージ変更処理関数.
//==================================.
void CEnding::ChangeStage()
{
	if (m_ChangeStageCnt > 0) {
		m_bChangeScene = true;
		return;
	}

	//ステージ決定処理関数.
	m_pCEndingStageBase.reset(DecideStage());

	m_ChangeStageCnt++;
}

//==================================.
//		ステージ決定処理関数.
//==================================.
CEndingStageBase*	CEnding::DecideStage()
{
	//音を流す管理クラス.
	CPlaySoundManager* m_pCPlaySoundManager = CPlaySoundManager::GetPlaySoundManager();

	if (m_Evaluation == 0) {
		//低評価クラス.
		m_pCPlaySoundManager->ChangePlayingBGM(enBGMType::LowEvaluationStage);
		return new CLowEvaluationStage(m_Evaluation);
	}

	if (m_Evaluation == 1) {
		//中間評価クラス.
		m_pCPlaySoundManager->ChangePlayingBGM(enBGMType::IntermediateEvaluationStage);
		return new CIntermediateEvaluationStage(m_Evaluation);
	}

	//高評価クラス.
	m_pCPlaySoundManager->ChangePlayingBGM(enBGMType::HightEvaluationStage);
	return new CHightEvaluationStage(m_Evaluation);
}