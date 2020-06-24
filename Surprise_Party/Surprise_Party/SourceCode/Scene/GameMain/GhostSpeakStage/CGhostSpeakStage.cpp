#include "CGhostSpeakStage.h"
#include "..\..\Camera\CameraGhostSpeakStage\CCameraGhostSpeakStage.h"

CGhostSpeakStage::CGhostSpeakStage()
	: CGhostSpeakStage	(0, enBeforeStageEndigneType::Nothing)
{
}

CGhostSpeakStage::CGhostSpeakStage(int stageNum, CGhostSpeakStage::enBeforeStageEndigneType enBeforeStageEndingType)	
	: m_pCFontResource		(nullptr)
	, m_pCFloor				(nullptr)
	, m_pCBigGhost			(nullptr)
	, m_pCSpeakBigGhost		(nullptr)
	, m_pCBackstageLight	(nullptr)
	, m_bOldSleepBigGhost	(true)
{
	m_StageNum = stageNum;
	m_enBeforeStageEndingType = enBeforeStageEndingType;
	//初期化処理関数.
	Init();
}

CGhostSpeakStage::~CGhostSpeakStage()
{
	//解放処理関数.
	Release();
}

//=========================================.
//		更新処理関数.
//=========================================.
void CGhostSpeakStage::UpDate(const bool& ControlFlag)
{
	//大きいお化け寝るフラグ.
	const bool SLEEP_BIGGHOST_FLAG = m_pCBigGhost->GetSleepFlag();


	if (GetAsyncKeyState('Q') & 0x8000) {
		if (m_TutorialFlag != TUTORIAL_FINISH) {
			m_TutorialFlag = TUTORIAL_START;
			return;
		}
	}

	if (SLEEP_BIGGHOST_FLAG == false) {
		SettingEmotion();
	}

	//大きいお化け更新処理関数.
	m_pCBigGhost->Update();

	if (SLEEP_BIGGHOST_FLAG == true) {
		if (m_bOldSleepBigGhost != SLEEP_BIGGHOST_FLAG) {
			//カメラ移動開始.
			m_pCCamera->SetMoveFlag(m_pCCamera->MOVE_FLAG);
		}
		m_bOldSleepBigGhost = SLEEP_BIGGHOST_FLAG;
	
		m_pCCamera->Update();

		if (m_pCCamera->GetMoveFlag() & m_pCCamera->CHANGE_STAGE_FLAG) {
			if (m_pCSpeakBigGhost->GetFinishFlag() & m_pCSpeakBigGhost->FINISH_NEXT_GAME) {
				//ゲームメインに進む.
				m_bChangeStageFlag = true;
				return;
			}
			//エンディングに進む.
			m_FinishFlag = FINISH_NEXT_ENDING;
		}

		return;
	}

	if (ControlFlag == false) {
		return;
	}

	//操作処理関数.
	Control();

	if (SLEEP_BIGGHOST_FLAG == true) {

		return;
	}
	if (m_TutorialFlag & TUTORIAL_START) {
		return;
	}

	//大きいお化け会話更新処理クラス.
	m_pCSpeakBigGhost->Update();

	//差分用.
	m_bOldSleepBigGhost = SLEEP_BIGGHOST_FLAG;

	const bool OldTutorialFlag = m_pCSpeakBigGhost->GetTutorialFlag();
	if (m_TutorialFlag != TUTORIAL_FINISH) {
		if (OldTutorialFlag == true) {
			m_TutorialFlag = TUTORIAL_START;
		}
		return;
	}
}

//=========================================.
//		描画処理関数.
//=========================================.
void CGhostSpeakStage::Render()
{
	//ライト情報.
	const LIGHT m_Light = m_pCBackstageLight->GetLight();

	//カメラ座標情報.
	const D3DXVECTOR3 m_vCameraPos = m_pCCamera->GetPos();

	//床の描画.
	m_pCFloor->SetCameraPos(m_vCameraPos);
	m_pCFloor->RenderInitSetting(m_mView, m_mProj, m_Light);
	m_pCFloor->SetPos(D3DXVECTOR3(0.0f, -6.0f, 0.0f));
	m_pCFloor->Render();

	//大きいお化け描画.
	m_pCBigGhost->SetPauseFlag(m_bPauseFlag);
	m_pCBigGhost->SetCameraPos(m_vCameraPos);
	m_pCBigGhost->RenderInitSetting(m_mView, m_mProj, m_Light);
	m_pCBigGhost->Render();

	if (m_pCBigGhost->GetSleepFlag() == true) {
		return;
	}

	if (m_TutorialFlag & TUTORIAL_START) {
		return;
	}

	//大きいお化け会話クラス.
	m_pCSpeakBigGhost->RenderInit(m_mView, m_mProj, m_vCameraPos);
	m_pCSpeakBigGhost->Render();

}

//=========================================.
//		初期化処理関数.
//=========================================.
void CGhostSpeakStage::Init()
{

	//床.
	m_pCFloor.reset(new CFloor());
	m_pCFloor->SetScale(0.5f);

	//大きいお化け.
	m_pCBigGhost.reset(new CBigGhost());

	//大きいお化け会話クラス.
	m_pCSpeakBigGhost.reset(new CSpeakBigGhost(m_StageNum,static_cast<int>(m_enBeforeStageEndingType)));

	//舞台裏のライトクラス.
	m_pCBackstageLight.reset(new CBackstageLight());

	//カメラクラス.
	m_pCCamera.reset(new CCameraGhostSpeakStage());

}

//=========================================.
//		解放処理関数.
//=========================================.
void CGhostSpeakStage::Release()
{
}

//=========================================.
//		操作処理関数.
//=========================================.
void CGhostSpeakStage::Control()
{

}

//===========================================.
//		感情設定処理関数.
//===========================================.
void CGhostSpeakStage::SettingEmotion()
{
	//終了フラグ.
	const unsigned int FINISH_FLAG = m_pCSpeakBigGhost->FINISH_NEXT_GAME | m_pCSpeakBigGhost->FINISH_NEXT_TITLE;
	if (m_pCSpeakBigGhost->GetFinishFlag() & FINISH_FLAG) {
		//睡眠.
		m_pCBigGhost->SetEmotionNum(static_cast<int>(CBigGhost::enEmotionType::Sleep));
		return;
	}

	//感情番号取得処理.
	m_pCBigGhost->SetEmotionNum(m_pCSpeakBigGhost->GetEmotionNum());
}