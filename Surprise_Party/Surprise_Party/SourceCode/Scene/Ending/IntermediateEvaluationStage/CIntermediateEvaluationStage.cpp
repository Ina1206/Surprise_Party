#include "CIntermediateEvaluationStage.h"

/***********************************************
*		中間評価ステージクラス.
********************/
CIntermediateEvaluationStage::CIntermediateEvaluationStage()
	: CIntermediateEvaluationStage(0)
{

}

CIntermediateEvaluationStage::CIntermediateEvaluationStage(const int& EvaluationNum)
	: CEvaluationStageBase	(EvaluationNum)
{
	m_Evaluation = EvaluationNum;
	//初期化処理関数.
	Init();
}

CIntermediateEvaluationStage::~CIntermediateEvaluationStage()
{
	//解放処理関数.
	Release();
}

//========================================.
//		初期化処理関数.
//========================================.
void CIntermediateEvaluationStage::Init()
{
	//フェードアウトで設定.
	m_pCWhiteScreenFade->SetFadeFlag(m_pCWhiteScreenFade->FADE_OUT_FLAG);

	//お化け感情設定.
	for (unsigned int ghost = 0; ghost < m_pCGhost.size(); ghost++) {
		if (ghost == BIG_GHOST_NUM) {
			//喜び.
			m_pCGhost[ghost]->SetEmotionNum(static_cast<int>(CGhostBase::enEmotionType::Rejoice));
			continue;
		}
		//上機嫌.
		m_pCGhost[ghost]->SetEmotionNum(static_cast<int>(CGhostBase::enEmotionType::GoodFeeling));
	}
	//カメラ終了.
	m_pCCameraEnding->SetMoveFlag(m_pCCameraEnding->STOP_FLAG);

}

//========================================.
//		解放処理関数.
//========================================.
void CIntermediateEvaluationStage::Release()
{

}