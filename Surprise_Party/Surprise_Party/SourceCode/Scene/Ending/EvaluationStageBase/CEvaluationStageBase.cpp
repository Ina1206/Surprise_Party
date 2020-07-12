#include "CEvaluationStageBase.h"

/**********************************************
*		評価ステージ基底クラス.
************************/
CEvaluationStageBase::CEvaluationStageBase()
{

}

CEvaluationStageBase::CEvaluationStageBase(const int& EvaluationNum)
	: CEndingStageBase				(EvaluationNum)
	, m_pCSurpriseDegreeManager		(nullptr)
	, m_pCEvaluationUIManager		(nullptr)
	, m_pCPushEnterUI				(nullptr)
	, m_fPushEnterUIAlpha			(0.0f)
	, m_AlphaAddDecDirect			(1)
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

	//PushEnter描画処理関数.
	RenderPushEnter();

}

//=========================================.
//		UIの初期化処理関数.
//=========================================.
void CEvaluationStageBase::InitUI()
{
	m_pCSurpriseDegreeManager = std::make_unique<CSurpriseDegreeManager>(m_Evaluation);
	m_pCEvaluationUIManager = std::make_unique<CEvaluationUIManager>(m_Evaluation);
}

//=========================================.
//		共通のUIの更新処理関数.
//=========================================.
void CEvaluationStageBase::UpdateCommonUI()
{
	if (m_UpdateFlag & SURPRISE_DEGREE_FLAG) {

		m_pCSurpriseDegreeManager->SetDisplayAllAtOnce(m_bDisplayAllAtOnce);

		//驚かし度のUI更新処理関数.
		m_pCSurpriseDegreeManager->Update();

		if (m_pCSurpriseDegreeManager->GetAllDispFlag() == true) {
			//お化けと評価文字更新処理フラグ.
			m_UpdateFlag = EVALUATION_STRING_FLAG | GHOST_FLAG;
		}
		return;
	}

	if (m_UpdateFlag & EVALUATION_STRING_FLAG) {

		m_pCEvaluationUIManager->SetDispAllAtOnce(m_bDisplayAllAtOnce);

		//評価UI更新処理関数.
		m_pCEvaluationUIManager->Update();

		if(m_pCEvaluationUIManager->GetFinishedAllDispFlag() == true){
			//PushEnter表示フラグ.
			m_UpdateFlag = GHOST_FLAG | PUSH_ENTER_FLAG;
		}

	}
}

//=========================================.
//		共通のUIの描画処理関数.
//=========================================.
void CEvaluationStageBase::RenderCommonUI()
{
	m_pCSurpriseDegreeManager->Render();
	m_pCEvaluationUIManager->Render();
}


//=========================================.
//		PushEnterの更新処理関数.
//=========================================.
void CEvaluationStageBase::UpdatePushEnter()
{
	if (GetAsyncKeyState(VK_RETURN) & 0x8000) {
		m_bChangeStage = true;
	}

	m_fPushEnterUIAlpha += 0.05f * m_AlphaAddDecDirect;

	if (m_fPushEnterUIAlpha > ALPHA_MAX) {
		m_fPushEnterUIAlpha = ALPHA_MAX;
		m_AlphaAddDecDirect *= -1;
		return;
	}

	if (m_fPushEnterUIAlpha < ALPHA_MIN) {
		m_fPushEnterUIAlpha = ALPHA_MIN;
		m_AlphaAddDecDirect *= -1;
	}

}

//=========================================.
//		PushEnterの描画処理関数.
//=========================================.
void CEvaluationStageBase::RenderPushEnter()
{
	CResourceManager* m_pCResourceManager = CResourceManager::GetResourceManagerInstance();
	m_pCPushEnterUI = m_pCResourceManager->GetSpriteUI(enSpriteUI::PushEnterString);
	m_pCPushEnterUI->SetAlpha(m_fPushEnterUIAlpha);
	m_pCPushEnterUI->SetScale(PUSH_ENTER_SCALE_MAX);
	m_pCPushEnterUI->SetPosition(PUSH_ENTER_POS);

	CDepth_Stencil* m_pCDeptshStencil = CDepth_Stencil::GetDepthStencilInstance();
	m_pCDeptshStencil->SetDepth(false);
	m_pCPushEnterUI->Render();
	m_pCDeptshStencil->SetDepth(true);

}
