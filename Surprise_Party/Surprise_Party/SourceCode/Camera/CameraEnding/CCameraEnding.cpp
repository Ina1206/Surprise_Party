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
	const unsigned int PosFlag = (1 << 0);
	const unsigned int LookFlag = (1 << 1);
	static int Cnt = 0;
	static D3DXVECTOR3 vLookPos = D3DXVECTOR3(5.0f, -0.8f, 5.0f);
	if (GetAsyncKeyState('1') & 0x0001) {
		Cnt++;
		if (Cnt > 1) {
			Cnt = 0;
		}
	}

	D3DXVECTOR3 Tmp;
	if (1 << Cnt & PosFlag) {
		Tmp = m_Camera.vPos;
	}
	else if (1 << Cnt & LookFlag) {
		Tmp = m_Camera.vLook;
	}
	else {
		Tmp = vLookPos;
	}

	if (GetAsyncKeyState(VK_UP) & 0x8000) {
		Tmp.y += 0.1f;
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
		Tmp.y -= 0.1f;
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
		Tmp.x += 0.1f;
	}
	if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
		Tmp.x -= 0.1f;
	}
	if (GetAsyncKeyState('Z') & 0x8000) {
		Tmp.z += 0.1f;
	}
	if (GetAsyncKeyState('X') & 0x8000) {
		Tmp.z -= 0.1f;
	}

	if (1 << Cnt & PosFlag) {
		m_Camera.vPos = Tmp;
	}
	else if (1 << Cnt & LookFlag) {
		m_Camera.vLook = Tmp;
	}
	else {
		vLookPos = Tmp;
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

	//注視点から初期のカメラ位置の距離.
	const float RANGE_FROM_CENTER = sqrtf(pow(INIT_CAMERA_POS.x - m_Camera.vLook.x, 2) + pow(INIT_CAMERA_POS.y - m_Camera.vLook.y, 2));
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
		m_MoveFlag = CHANGE_STAGE_FLAG;
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
	m_Camera.vPos.x = m_Camera.vLook.x + (cosf(RADIAN) * fCenterRange);
	m_Camera.vPos.z = m_Camera.vLook.z + (sinf(RADIAN) * fCenterRange);

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
	m_Camera.vPos.y -= 0.2f;

	if (m_Camera.vPos.y < 2.5f) {
		m_Camera.vPos.y = 2.5f;
	}
}