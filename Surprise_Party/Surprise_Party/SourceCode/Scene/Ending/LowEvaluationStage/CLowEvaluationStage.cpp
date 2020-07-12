#include "CLowEvaluationStage.h"

/***********************************************
*		低評価のステージクラス.
*****************/
CLowEvaluationStage::CLowEvaluationStage()
{
	//初期化処理関数.
	Init();
}

CLowEvaluationStage::~CLowEvaluationStage()
{
	//解放処理関数.
	Release();
}

//================================================.
//		初期化処理関数.
//================================================.
void CLowEvaluationStage::Init()
{
	//フェードアウトで設定.
	m_pCWhiteScreenFade->SetFadeFlag(m_pCWhiteScreenFade->FADE_OUT_FLAG);

	for (unsigned int ghost = 0; ghost < m_pCGhost.size(); ghost++) {
		m_pCGhost[ghost]->SetEmotionNum(static_cast<int>(CGhostBase::enEmotionType::HaveTrounble));
	}

	m_pCCameraEnding->SetMoveFlag(m_pCCameraEnding->STOP_FLAG);

}

//================================================.
//		解放処理関数.
//================================================.
void CLowEvaluationStage::Release()
{

}