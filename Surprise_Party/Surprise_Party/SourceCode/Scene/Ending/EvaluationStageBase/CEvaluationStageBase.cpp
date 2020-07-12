#include "CEvaluationStageBase.h"

/**********************************************
*		評価ステージ基底クラス.
************************/
CEvaluationStageBase::CEvaluationStageBase()
{

}

CEvaluationStageBase::~CEvaluationStageBase()
{

}

//===============================================.
//				更新処理関数.
//===============================================.
void CEvaluationStageBase::Update()
{
	//共通のUIの更新処理関数.
	UpdateCommonUI();

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

//===============================================.
//				描画処理関数.
//===============================================.
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

	//PushEnter描画処理関数.
	RenderPushEnter();

}