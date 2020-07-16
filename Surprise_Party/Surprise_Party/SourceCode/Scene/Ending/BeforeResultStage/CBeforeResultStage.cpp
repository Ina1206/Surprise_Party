#include "CBeforeResultStage.h"

#include "..\..\..\GameObject\Object\StaticObject\SmartPhone\CSmartPhone.h"

/********************************************
*		結果発表前のステージクラス.
******************/
CBeforeResultStage::CBeforeResultStage()
	: m_pCReputationSNS		(nullptr)
	, m_pCSmartPhone		(nullptr)
	, m_pCPlaySoundManager	(CPlaySoundManager::GetPlaySoundManager())
	, m_bPlaySE				(false)
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
	//BGMの音量を設定処理関数.
	SettingBGMVolume();

	//カメラ更新処理関数.
	m_pCCameraEnding->Update();

	//お化け達の更新処理関数.
	for (unsigned int ghost = 0; ghost < m_pCGhost.size(); ghost++) {
		m_pCGhost[ghost]->Update();
	}

	//スマートフォンの更新処理関数.
	m_pCSmartPhone->Update();
	
	if (m_pCCameraEnding->GetMoveFlag() & m_pCCameraEnding->CHANGE_STAGE_FLAG) {
		//飛ぶときのSE再生処理.
		if (m_bPlaySE == false) {
			m_pCPlaySoundManager->SetPlaySE(enSEType::JumpSNS);
			m_bPlaySE = true;
		}

		if (m_pCWhiteScreenFade->GetFadeFlag() & m_pCWhiteScreenFade->FADE_FINISH_FLAG) {
			//SNS更新処理関数.
			m_pCReputationSNS->Update();
			
			if (m_pCReputationSNS->GetChangeStage() & m_pCReputationSNS->CHANGE_STAGE_FLAG) {
				m_bChangeStage = true;
			}
			return;
		}

		m_pCWhiteScreenFade->SetFadeFlag(m_pCWhiteScreenFade->FADE_IN_FLAG);
		m_pCWhiteScreenFade->Update();
	}

	//文章決定処理関数.
	DecideString();
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

	//スマートフォンの描画処理関数.
	RenderSmartPhone();

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
	m_pCSmartPhone.reset(new CSmartPhone());

	m_pCCameraEnding->SetMoveFlag(m_pCCameraEnding->MOVE_FLAG);
}

//=======================================.
//		解放処理関数.
//=======================================.
void CBeforeResultStage::Release()
{

}

//=======================================.
//		文章決定処理関数.
//=======================================.
void CBeforeResultStage::DecideString()
{
	if (m_OldEvaluation != INIT_EVALUATION_NUM) {
		return;
	}

	if (m_Evaluation != m_OldEvaluation) {
		//文章決定処理関数.
		m_pCReputationSNS->DecideString(m_Evaluation);
	}

	m_OldEvaluation = m_Evaluation;
}

//========================================.
//		スマートフォン描画処理関数.
//========================================.
void CBeforeResultStage::RenderSmartPhone()
{
	//ライト情報.
	const LIGHT m_Light = m_pCBackstageLight->GetLight();
	//カメラ位置.
	const D3DXVECTOR3 m_vCameraPos = m_pCCameraEnding->GetPos();

	m_pCSmartPhone->SetPos(m_vObjLookPos);
	m_pCSmartPhone->SetCameraPos(m_vCameraPos);
	m_pCSmartPhone->RenderInitSetting(m_mView, m_mProj, m_Light);
	m_pCSmartPhone->Render();
}