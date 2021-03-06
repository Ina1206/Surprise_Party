#include "CCameraEnding.h"

/******************************************
*		エンディングカメラクラス.
***************/
CCameraEnding::CCameraEnding()
	: m_fAngle			(0.0f)
	, m_fApprochDistance(0.0f)
	, m_ApprochFlag		(0)
{
	//初期化処理関数.
	Init();
}

CCameraEnding::~CCameraEnding()
{
	//解放処理関数.
	Release();
}

//=============================================.
//			更新処理関数.
//=============================================.
void CCameraEnding::Update()
{
	//カメラが移動しないときの座標.
	if (m_MoveFlag & STOP_FLAG) {
		m_Camera.vPos = LOOK_AT_GHOSTS_POS;
		m_Camera.vLook = LOOK_AT_GHOSTS_LOOK;
		return;
	}

	if (m_ApprochFlag & APPROCH_GHOST_HEAD_FLAG) {
		//中間地点まで移動処理関数.
		MoveToIntermediatePoint();
		return;
	}

	if (m_ApprochFlag & APPROCH_SMARTPHONE_FLAG) {
		//下降処理関数.
		MoveDown();
	}
}

//=============================================.
//			初期化処理関数.
//=============================================.
void CCameraEnding::Init()
{
	m_Camera.vPos = INIT_CAMERA_POS;
	m_Camera.vLook = INIT_CAMERA_LOOK;
	
	m_fAngle = ANGLE_MAX;

	m_ApprochFlag = APPROCH_GHOST_HEAD_FLAG;
}

//=============================================.
//			解放処理関数.
//=============================================.
void CCameraEnding::Release()
{

}

//=============================================.
//			中間地点まで移動処理関数.
//=============================================.
void CCameraEnding::MoveToIntermediatePoint()
{
	//注視点移動処理関数.
	MoveLook();

	//上昇移動処理関数.
	MoveUp();
	//接近移動処理関数.
	MoveApproching();

}

//=============================================.
//		上昇移動処理関数.
//=============================================.
void CCameraEnding::MoveUp()
{
	m_Camera.vPos.y += MOVE_SPEED;


	if (m_Camera.vPos.y > INTERMEDIATE_POINT_POS.y) {
		m_Camera.vPos.y = INTERMEDIATE_POINT_POS.y;
	}
}

//=============================================.
//		接近移動処理関数.
//=============================================.
void CCameraEnding::MoveApproching()
{
	//中間地点から初期位置の距離(上がる距離を基準に移動速度調整).
	const float INTERMEDIATE_INIT_HEIGHT_RANGE = INTERMEDIATE_POINT_POS.y - INIT_CAMERA_POS.y;

	//中間地点から初期のカメラ位置の距離.
	const float RANGE_FROM_CENTER = sqrtf(pow(INIT_CAMERA_POS.x - INTERMEDIATE_POINT_POS.x, 2) + pow(INIT_CAMERA_POS.z - INTERMEDIATE_POINT_POS.z, 2));
	//引く距離を算出.
	const float CENTER_RANGE_POS_UNIT = RANGE_FROM_CENTER / INTERMEDIATE_INIT_HEIGHT_RANGE;
	m_fApprochDistance += MOVE_SPEED * CENTER_RANGE_POS_UNIT;

	float m_fCenterFromRange;
	m_fCenterFromRange = RANGE_FROM_CENTER - m_fApprochDistance;
	if (m_fCenterFromRange < 0.0f) {
		//周辺を回る処理は行かせない.
		m_Camera.vPos.x = INTERMEDIATE_POINT_POS.x;
		m_Camera.vPos.z = INTERMEDIATE_POINT_POS.z;

		//下降移動処理に変更.
		m_ApprochFlag = APPROCH_SMARTPHONE_FLAG;
		m_MoveFlag |= CHANGE_STAGE_FLAG;
		return;
	}

	//周辺を回る処理関数.
	RotateSurrunding(INTERMEDIATE_INIT_HEIGHT_RANGE, m_fCenterFromRange);
}

//==============================================.
//		周辺を回る処理関数.
//==============================================.
void CCameraEnding::RotateSurrunding(const float& fCriteriaRange, const float& fCenterRange)
{

	//移動角度の範囲.
	const float MOVE_ANGLE_RANGE = fabsf(ANGLE_MAX - ANGLE_MIN);
	const float MOVE_ANGLE_POS_UNIT = MOVE_ANGLE_RANGE / fCriteriaRange;
	m_fAngle -= MOVE_SPEED * MOVE_ANGLE_POS_UNIT;

	//ラジアン.
	const float RADIAN = static_cast<float>(D3DXToRadian(m_fAngle));
	//中間地点を中心として回転する.
	m_Camera.vPos.x = INTERMEDIATE_POINT_POS.x + (cosf(RADIAN) * fCenterRange);
	m_Camera.vPos.z = INTERMEDIATE_POINT_POS.z + (sinf(RADIAN) * fCenterRange);

	if (m_fAngle < ANGLE_MIN) {
		m_fAngle = ANGLE_MIN;
	}

}

//==============================================.
//		注視点移動処理関数.
//==============================================.
void CCameraEnding::MoveLook()
{
	//初期値と中間地点との距離.
	const D3DXVECTOR3 Intermediate_Init_Look = INTERMEDIATE_POINT_LOOK - INIT_CAMERA_LOOK;
	const float LOOK_LENGTH = D3DXVec3Length(&Intermediate_Init_Look);
	const D3DXVECTOR3 LOOK_UNIT = Intermediate_Init_Look / LOOK_LENGTH;
	m_Camera.vLook += MOVE_SPEED * LOOK_UNIT;
	if (m_Camera.vLook.y < INTERMEDIATE_POINT_LOOK.y) {
		m_Camera.vLook = INTERMEDIATE_POINT_LOOK;
	}

}

//==============================================.
//		下降移動処理関数.
//==============================================.
void CCameraEnding::MoveDown()
{
	//中間地点から最終地点までの二点間の距離.
	const D3DXVECTOR3 FINISH_INTERMEDIATE_POS = FINISH_CMAERA_POS - INTERMEDIATE_POINT_POS;
	const float POS_LENGTH = D3DXVec3Length(&FINISH_INTERMEDIATE_POS);
	const D3DXVECTOR3 POS_UNIT = FINISH_INTERMEDIATE_POS / POS_LENGTH;
	
	m_Camera.vPos += MOVE_DOWN_SPEED * POS_UNIT;

	if (m_Camera.vPos.y < FINISH_CMAERA_POS.y) {
		m_Camera.vPos = FINISH_CMAERA_POS;
	}
}