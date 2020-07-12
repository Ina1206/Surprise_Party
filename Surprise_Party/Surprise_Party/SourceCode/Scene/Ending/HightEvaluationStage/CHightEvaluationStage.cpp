#include "CHightEvaluationStage.h"

/**********************************************
*			高評価ステージクラス.
*******************/
CHightEvaluationStage::CHightEvaluationStage()
	: CHightEvaluationStage(0)
{

}

CHightEvaluationStage::CHightEvaluationStage(const int& EvaluationNum)
	: CEvaluationStageBase	(EvaluationNum)
{
	m_Evaluation = EvaluationNum;
	//初期化処理関数.
	Init();
}

CHightEvaluationStage::~CHightEvaluationStage()
{
	//解放処理関数.
	Release();
}

//=============================================.
//			初期化処理関数.
//=============================================.
void CHightEvaluationStage::Init()
{
	//フェードアウトで設定.
	m_pCWhiteScreenFade->SetFadeFlag(m_pCWhiteScreenFade->FADE_OUT_FLAG);

	//お化け感情設定.
	for (unsigned int ghost = 0; ghost < m_pCGhost.size(); ghost++) {
		m_pCGhost[ghost]->SetEmotionNum(static_cast<int>(CGhostBase::enEmotionType::Rejoice));
	}

	m_pCCameraEnding->SetMoveFlag(m_pCCameraEnding->STOP_FLAG);
	
}

//=============================================.
//			解放処理関数.
//=============================================.
void CHightEvaluationStage::Release()
{

}