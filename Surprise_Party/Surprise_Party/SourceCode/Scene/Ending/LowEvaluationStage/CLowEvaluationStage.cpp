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

//===============================================.
//		更新処理関数.
//===============================================.
void CLowEvaluationStage::Update()
{
	//カメラの更新処理関数.
	m_pCCameraEnding->Update();


	//お化けの更新処理.
	for (unsigned int ghost = 0; ghost < m_pCGhost.size(); ghost++) {
		m_pCGhost[ghost]->Update();
	}

	//白画面のフェード.
	if (m_pCWhiteScreenFade->GetFadeFlag() & m_pCWhiteScreenFade->FADE_FINISH_FLAG) {
		return;
	}
	m_pCWhiteScreenFade->Update();

}

//================================================.
//		描画処理関数.
//================================================.
void CLowEvaluationStage::Render()
{
	//床の描画.
	RenderFloor();

	//お化けの描画.
	RenderGhost();

	//白画面のフェード描画.
	if (!(m_pCWhiteScreenFade->GetFadeFlag() & m_pCWhiteScreenFade->FADE_FINISH_FLAG)) {
		m_pCWhiteScreenFade->Render();
	}
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