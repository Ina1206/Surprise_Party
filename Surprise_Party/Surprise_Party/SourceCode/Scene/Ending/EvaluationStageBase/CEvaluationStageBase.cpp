#include "CEvaluationStageBase.h"

/**********************************************
*		評価ステージ基底クラス.
************************/
CEvaluationStageBase::CEvaluationStageBase()
{

}

CEvaluationStageBase::CEvaluationStageBase(const int& EvaluationNum)
	: CEndingStageBase				(EvaluationNum)
	, m_pCEndingUI					(nullptr)
{
	//UIの初期化処理関数.
	InitUI();
}

CEvaluationStageBase::~CEvaluationStageBase()
{

}

//========================================.
//				更新処理関数.		  
//========================================.
void CEvaluationStageBase::Update()
{
	//カメラの更新処理関数.
	m_pCCameraEnding->Update();

	if (m_UpdateFlag == 0) {
		//フェード更新処理関数.
		m_pCWhiteScreenFade->Update();

		//フェード終了後に驚かし度UIの処理開始.
		if (m_pCWhiteScreenFade->GetFadeFlag() & m_pCWhiteScreenFade->FADE_FINISH_FLAG) {
			m_UpdateFlag = SURPRISE_DEGREE_FLAG;
		}
		return;
	}

	//共通のUIの更新処理関数.
	UpdateCommonUI();
	
	if (m_UpdateFlag & GHOST_FLAG) {
		//お化けの更新処理.
		for (unsigned int ghost = 0; ghost < m_pCGhost.size(); ghost++) {
			m_pCGhost[ghost]->Update();
		}
	}


}

//=========================================.
//				描画処理関数.
//=========================================.
void CEvaluationStageBase::Render()
{
	//床の描画処理関数.
	RenderFloor();

	//お化け描画処理関数.
	RenderGhost();

	//白画面のフェード描画.
	if (!(m_pCWhiteScreenFade->GetFadeFlag() & m_pCWhiteScreenFade->FADE_FINISH_FLAG)) {
		m_pCWhiteScreenFade->Render();
		return;
	}

	//共通のUIの描画処理関数.
	RenderCommonUI();

}

//=========================================.
//		UIの初期化処理関数.
//=========================================.
void CEvaluationStageBase::InitUI()
{
	m_pCEndingUI = std::make_unique<CEndingUI>(m_Evaluation);
}

//=========================================.
//		共通のUIの更新処理関数.
//=========================================.
void CEvaluationStageBase::UpdateCommonUI()
{
	//更新処理関数.
	m_pCEndingUI->Update();
	//お化けの処理設定.
	if (m_pCEndingUI->GetFinishEvaluationFlag() == true) {
		m_UpdateFlag = GHOST_FLAG;
	}
	//シーン変更フラグ.
	m_bChangeStage = m_pCEndingUI->GetChangeSceneFlag();
}

//=========================================.
//		共通のUIの描画処理関数.
//=========================================.
void CEvaluationStageBase::RenderCommonUI()
{
	m_pCEndingUI->Render();
}

