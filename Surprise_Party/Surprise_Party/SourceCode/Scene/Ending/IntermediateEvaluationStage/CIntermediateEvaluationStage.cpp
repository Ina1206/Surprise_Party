#include "CIntermediateEvaluationStage.h"

/***********************************************
*		中間評価ステージクラス.
********************/
CIntermediateEvaluationStage::CIntermediateEvaluationStage()
{
	//初期化処理関数.
	Init();
}

CIntermediateEvaluationStage::~CIntermediateEvaluationStage()
{
	//解放処理関数.
	Release();
}

//========================================.
//		更新処理関数.
//========================================.
void CIntermediateEvaluationStage::Update()
{
	//カメラの更新処理関数.
	m_pCCameraEnding->Update();

	//お化けの更新処理.
	for (unsigned int ghost = 0; ghost < m_pCGhost.size(); ghost++) {
		m_pCGhost[ghost]->Update();
	}


	//白画面のフェード.
	if (m_pCWhiteScreenFade->GetFadeFlag() & m_pCWhiteScreenFade->FADE_FINISH_FLAG) {
		//PushEnterの更新処理関数.
		UpdatePushEnter();
		return;
	}
	m_pCWhiteScreenFade->Update();

}

//========================================.
//		描画処理関数.
//========================================.
void CIntermediateEvaluationStage::Render()
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

	//PushEnter描画処理関数.
	RenderPushEnter();
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
		if (ghost == 2) {
			m_pCGhost[ghost]->SetEmotionNum(static_cast<int>(CGhostBase::enEmotionType::Rejoice));
			continue;
		}
		m_pCGhost[ghost]->SetEmotionNum(static_cast<int>(CGhostBase::enEmotionType::GoodFeeling));
	}

	m_pCCameraEnding->SetMoveFlag(m_pCCameraEnding->STOP_FLAG);

}

//========================================.
//		解放処理関数.
//========================================.
void CIntermediateEvaluationStage::Release()
{

}