#include "CBeforeResultStage.h"

#include "..\..\..\GameObject\Object\StaticObject\SmartPhone\CSmartPhone.h"

/********************************************
*		結果発表前のステージクラス.
******************/
CBeforeResultStage::CBeforeResultStage()
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
}

//=======================================.
//		初期化処理関数.
//=======================================.
void CBeforeResultStage::Init()
{

}

//=======================================.
//		解放処理関数.
//=======================================.
void CBeforeResultStage::Release()
{

}