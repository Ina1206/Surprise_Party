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
	//一回スキップしていたら処理終了.
	if (m_bCanSkip == false) {
		return;
	}

	if (m_MoveFlag & STOP_FLAG) {
		return;
	}

	//移動処理関数.
	Move();

	if (m_MoveCameraDirection == GET_CLOSER_CAMERA_DIRECT) {
		//接近上限処理関数.
		GetCloserUpperLimit();
		return;
	}

	//遠のく上限処理関数.
	FarAwayUpperLimit();
}

//===============================================.
//			初期化処理関数.
//===============================================.
void CCameraGhostSpeakStage::Init()
{
	m_Camera.vPos = INIT_CAMERA_POS;
	m_Camera.vLook = INIT_CAMERA_LOOK;

	m_MoveCameraDirection = GET_CLOSER_CAMERA_DIRECT;
}

//===============================================.
//			解放処理関数.
//===============================================.
void CCameraGhostSpeakStage::Release()
{


}

//===============================================.
//			移動処理関数.
//===============================================.
void CCameraGhostSpeakStage::Move()
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

}

//===============================================.
//			接近上限処理関数.
//===============================================.
void CCameraGhostSpeakStage::GetCloserUpperLimit()
{
	//スキップ処理.
	if (m_MoveFlag & SKIP_FLAG) {
		m_Camera.vPos	= SPEAK_START_POS;
		m_Camera.vLook	= SPEAK_START_LOOK;
		m_bCanSkip		= false;
	}

	//上限到達時の処理.
	if (m_Camera.vPos.x >= SPEAK_START_POS.x ||
		m_Camera.vLook.x >= SPEAK_START_LOOK.x) {

		m_Camera.vPos			= SPEAK_START_POS;
		m_Camera.vLook			= SPEAK_START_LOOK;
		m_MoveFlag				= STOP_FLAG;
		m_MoveCameraDirection	= FAR_AWAY_CAMERA_DIRECT;
		m_bCanSkip				= false;
	}

}

//===============================================.
//			遠のく上限処理関数.
//===============================================.
void CCameraGhostSpeakStage::FarAwayUpperLimit()
{
	//スキップ処理.
	if (m_MoveFlag & SKIP_FLAG) {
		m_Camera.vPos	= INIT_CAMERA_POS;
		m_Camera.vLook	= INIT_CAMERA_LOOK;
	}

	//上限到達時の処理.
	if (m_Camera.vPos.x <= INIT_CAMERA_POS.x ||
		m_Camera.vLook.x <= INIT_CAMERA_LOOK.x) {
		m_Camera.vPos	= INIT_CAMERA_POS;
		m_Camera.vLook	= INIT_CAMERA_LOOK;
		m_MoveFlag		= STOP_FLAG | CHANGE_STAGE_FLAG;
	}

}