#include "CCameraGhostSpeakStage.h"

/**********************************************
*		お化けが話すステージのカメラクラス.
**************/
CCameraGhostSpeakStage::CCameraGhostSpeakStage()
{
	//初期化処理関数.
	Init();
}

CCameraGhostSpeakStage::~CCameraGhostSpeakStage()
{
	//解放処理関数.
	Release();
}

//===============================================.
//			更新処理関数.
//===============================================.
void CCameraGhostSpeakStage::Update()
{

	if (m_MoveFlag & STOP_FLAG) {
		return;
	}

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
			m_Camera.vLook = SPEAK_START_LOOK;
			m_MoveFlag = STOP_FLAG;
			m_MoveCameraDirection = FAR_AWAY_CAMERA_DIRECT;
		}

		if (m_Camera.vLook.x > SPEAK_START_LOOK.x) {
			m_Camera.vLook = SPEAK_START_LOOK;
		}
		return;
	}

	//カメラが遠のく上限処理.
	if (m_Camera.vPos.x < INIT_CAMERA_POS.x) {
		m_Camera.vPos = INIT_CAMERA_POS;
		//if (m_pCSpeakBigGhost->GetFinishFlag() & m_pCSpeakBigGhost->FINISH_NEXT_GAME) {
		//	//ゲームメインに進む.
		//	m_bChangeStageFlag = true;
		//	return;
		//}
		////エンディングに進む.
		//m_FinishFlag = FINISH_NEXT_ENDING;
		m_Camera.vLook = INIT_CAMERA_LOOK;
		m_MoveFlag = STOP_FLAG | MOVE_FINISH_FLAG;
		
	}

	if (m_Camera.vLook.x < INIT_CAMERA_LOOK.x) {
		m_Camera.vLook = INIT_CAMERA_LOOK;
	}

}

//===============================================.
//			初期化処理関数.
//===============================================.
void CCameraGhostSpeakStage::Init()
{
	m_Camera.vPos = D3DXVECTOR3(5.0f, 2.5f, -3.5f);
	m_Camera.vLook = D3DXVECTOR3(5.0f, 2.5f, 5.0f);

	m_MoveCameraDirection = GET_CLOSER_CAMERA_DIRECT;
}

//===============================================.
//			解放処理関数.
//===============================================.
void CCameraGhostSpeakStage::Release()
{

}