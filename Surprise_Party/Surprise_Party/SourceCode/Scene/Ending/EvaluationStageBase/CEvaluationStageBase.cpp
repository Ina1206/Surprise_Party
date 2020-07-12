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

	if (GetAsyncKeyState(VK_RETURN) & 0x0001) {
		m_bDisplayAllAtOnce = true;
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