#include "CBeforeResultStage.h"

#include "..\..\..\GameObject\Object\StaticObject\SmartPhone\CSmartPhone.h"

/********************************************
*		結果発表前のステージクラス.
******************/
CBeforeResultStage::CBeforeResultStage()
	: m_pCReputationSNS	(nullptr)
{
	//初期化処理関数.
	Init();
}

CBeforeResultStage::~CBeforeResultStage()
{
	//解放処理関数.
	Release();
}

//=======================================.
//		更新処理関数.
//=======================================.
void CBeforeResultStage::Update()
{
	//カメラ更新処理関数.
	m_pCCameraEnding->Update();

	for (unsigned int ghost = 0; ghost < m_pCGhost.size(); ghost++) {
		m_pCGhost[ghost]->Update();
	}
	
	if (m_pCCameraEnding->GetMoveFlag() & m_pCCameraEnding->CHANGE_STAGE_FLAG) {
		
		if (m_pCWhiteScreenFade->GetFadeFlag() & m_pCWhiteScreenFade->FADE_FINISH_FLAG) {
			m_pCReputationSNS->Update();
			return;
		}

		m_pCWhiteScreenFade->SetFadeFlag(m_pCWhiteScreenFade->FADE_IN_FLAG);
		m_pCWhiteScreenFade->Update();
	}

}

//=======================================.
//		描画処理関数.
//=======================================.
void CBeforeResultStage::Render()
{
	//床の描画処理関数.
	RenderFloor();

	//お化け描画処理関数.
	RenderGhost();

	//フェード描画処理関数.
	m_pCWhiteScreenFade->Render();

	//SNSの評判クラス.
	if (m_pCWhiteScreenFade->GetFadeFlag() & m_pCWhiteScreenFade->FADE_FINISH_FLAG) {
		m_pCReputationSNS->Render();
	}
}

//=======================================.
//		初期化処理関数.
//=======================================.
void CBeforeResultStage::Init()
{
	m_pCReputationSNS.reset(new CReputationSNS());

	m_pCReputationSNS->DecideString(1);
}

//=======================================.
//		解放処理関数.
//=======================================.
void CBeforeResultStage::Release()
{

}