#include "CGhostSpeakStage.h"

CGhostSpeakStage::CGhostSpeakStage()
	: CGhostSpeakStage	(0, enBeforeStageEndigneType::Nothing)
{
}

CGhostSpeakStage::CGhostSpeakStage(int stageNum, CGhostSpeakStage::enBeforeStageEndigneType enBeforeStageEndingType)	
	: m_pCFontResource		(nullptr)
	, changestr				()
	, m_pCFloor				(nullptr)
	, m_pCBigGhost			(nullptr)
	, m_pCSpeakBigGhost		(nullptr)
	, m_pCBackstageLight	(nullptr)
	, m_MoveCameraDirection	(GET_CLOSER_CAMERA_DIRECT)
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
	if (GetAsyncKeyState('Q') & 0x8000) {
		//const bool OldTutorialFlag = m_pCSpeakBigGhost->GetTutorialFlag();
		if (m_TutorialFlag != TUTORIAL_FINISH) {
			//if (OldTutorialFlag == true) {
				m_TutorialFlag = TUTORIAL_START;
			//}
			return;
		}
	}

	if (m_pCBigGhost->GetSleepFlag() == false) {
		SettingEmotion();
	}

	//大きいお化け更新処理関数.
	m_pCBigGhost->Update();

	if (m_pCBigGhost->GetSleepFlag() == true) {
		//カメラ移動処理関数.
		CameraMove();
		return;
	}

	if (ControlFlag == false) {
		return;
	}

	//操作処理関数.
	Control();

	if (m_pCBigGhost->GetSleepFlag() == true) {
		return;
	}
	if (m_TutorialFlag & TUTORIAL_START) {
		return;
	}

	//大きいお化け会話更新処理クラス.
	m_pCSpeakBigGhost->Update();

	m_MoveCameraDirection = FAR_AWAY_CAMERA_DIRECT;

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

	//床の描画.
	m_pCFloor->SetCameraPos(m_Camera.vPos);
	m_pCFloor->RenderInitSetting(m_mView, m_mProj, m_Light);
	m_pCFloor->SetPos(D3DXVECTOR3(0.0f, -6.0f, 0.0f));
	m_pCFloor->Render();

	//大きいお化け描画.
	m_pCBigGhost->SetCameraPos(m_Camera.vPos);
	m_pCBigGhost->RenderInitSetting(m_mView, m_mProj, m_Light);
	m_pCBigGhost->Render();

	if (m_pCBigGhost->GetSleepFlag() == true) {
		return;
	}

	if (m_TutorialFlag & TUTORIAL_START) {
		return;
	}

	//大きいお化け会話クラス.
	m_pCSpeakBigGhost->RenderInit(m_mView, m_mProj, m_Camera.vPos);
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

	m_Camera.vPos = D3DXVECTOR3(5.0f, 2.5f, -3.5f);
	m_Camera.vLook = D3DXVECTOR3(5.0f, 2.5f, 5.0f);
}

//=========================================.
//		解放処理関数.
//=========================================.
void CGhostSpeakStage::Release()
{
	//m_pCFontResource->Destroy();
}

//=========================================.
//		操作処理関数.
//=========================================.
void CGhostSpeakStage::Control()
{

}

//===========================================.
//		カメラ移動処理関数.
//===========================================.
void CGhostSpeakStage::CameraMove()
{

	//カメラの移動処理.
	const float CAMERA_POS_LENGTH = D3DXVec3Length(&CAMERA_POS_DISTANCE);			//ベクトルの長さ.
	const D3DXVECTOR3	CAMERA_POS_UNIT = CAMERA_POS_DISTANCE / CAMERA_POS_LENGTH;	//単位ベクトル.
	m_Camera.vPos += CAMER_MOVE_SPEED * CAMERA_POS_UNIT * static_cast<float>(m_MoveCameraDirection);

	//カメラの注視点移動処理.
	const float CAMERA_LOOK_LENGTH = D3DXVec3Length(&CAMERA_LOOK_DISTANCE);				//ベクトルの長さ.
	const D3DXVECTOR3	CAMERA_LOOK_UNIT = CAMERA_LOOK_DISTANCE / CAMERA_LOOK_LENGTH;	//単位ベクトル.
	const float	CAMERA_LENGTH_RATIO = CAMERA_LOOK_LENGTH / CAMERA_POS_LENGTH;			//長さの比率.
	m_Camera.vLook += CAMER_MOVE_SPEED * CAMERA_LOOK_UNIT * static_cast<float>(m_MoveCameraDirection) * CAMERA_LENGTH_RATIO;

	//カメラの接近する上限処理.
	if (m_MoveCameraDirection == GET_CLOSER_CAMERA_DIRECT) {
		if (m_Camera.vPos.x > SPEAK_START_POS.x) {
			m_Camera.vPos = SPEAK_START_POS;
		}

		if (m_Camera.vLook.x > SPEAK_START_LOOK.x) {
			m_Camera.vLook = SPEAK_START_LOOK;
		}
		return;
	}

	//カメラが遠のく上限処理.
	if (m_Camera.vPos.x < INIT_CAMERA_POS.x) {
		m_Camera.vPos = INIT_CAMERA_POS;
		if (m_pCSpeakBigGhost->GetFinishFlag() & m_pCSpeakBigGhost->FINISH_NEXT_GAME) {
			//ゲームメインに進む.
			m_bChangeStageFlag = true;
			return;
		}
		//エンディングに進む.
		m_FinishFlag = FINISH_NEXT_ENDING;
	}

	if (m_Camera.vLook.x < INIT_CAMERA_LOOK.x) {
		m_Camera.vLook = INIT_CAMERA_LOOK;
	}
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