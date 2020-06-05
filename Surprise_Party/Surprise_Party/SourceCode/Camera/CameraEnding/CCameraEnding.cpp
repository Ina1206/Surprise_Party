#include "CCameraEnding.h"

/******************************************
*		�G���f�B���O�J�����N���X.
***************/
CCameraEnding::CCameraEnding()
	: m_fAngle			(0.0f)
	, m_fApprochDistance(0.0f)
	, m_ApprochFlag		(0)
{
	//�����������֐�.
	Init();
}

CCameraEnding::~CCameraEnding()
{
	//��������֐�.
	Release();
}

//=============================================.
//			�X�V�����֐�.
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
		//���Ԓn�_�܂ňړ������֐�.
		MoveToIntermediatePoint();
		return;
	}

	if (m_ApprochFlag & APPROCH_SMARTPHONE_FLAG) {
		//���~�����֐�.
		MoveDown();
	}
}

//=============================================.
//			�����������֐�.
//=============================================.
void CCameraEnding::Init()
{
	m_Camera.vPos = INIT_CAMERA_POS;
	m_Camera.vLook = INIT_CAMERA_LOOK;
	
	m_fAngle = ANGLE_MAX;

	m_ApprochFlag = APPROCH_GHOST_HEAD_FLAG;
}

//=============================================.
//			��������֐�.
//=============================================.
void CCameraEnding::Release()
{

}

//=============================================.
//			���Ԓn�_�܂ňړ������֐�.
//=============================================.
void CCameraEnding::MoveToIntermediatePoint()
{
	//�����_�ړ������֐�.
	MoveLook();

	//�㏸�ړ������֐�.
	MoveUp();
	//�ڋ߈ړ������֐�.
	MoveApproching();

}

//=============================================.
//		�㏸�ړ������֐�.
//=============================================.
void CCameraEnding::MoveUp()
{
	m_Camera.vPos.y += MOVE_SPEED;


	if (m_Camera.vPos.y > INTERMEDIATE_POINT_POS.y) {
		m_Camera.vPos.y = INTERMEDIATE_POINT_POS.y;
	}
}

//=============================================.
//		�ڋ߈ړ������֐�.
//=============================================.
void CCameraEnding::MoveApproching()
{
	//���Ԓn�_���珉���ʒu�̋���(�オ�鋗������Ɉړ����x����).
	const float INTERMEDIATE_INIT_HEIGHT_RANGE = INTERMEDIATE_POINT_POS.y - INIT_CAMERA_POS.y;

	//�����_���珉���̃J�����ʒu�̋���.
	const float RANGE_FROM_CENTER = sqrtf(pow(INIT_CAMERA_POS.x - m_Camera.vLook.x, 2) + pow(INIT_CAMERA_POS.y - m_Camera.vLook.y, 2));
	//�����������Z�o.
	const float CENTER_RANGE_POS_UNIT = RANGE_FROM_CENTER / INTERMEDIATE_INIT_HEIGHT_RANGE;
	m_fApprochDistance += MOVE_SPEED * CENTER_RANGE_POS_UNIT;

	float m_fCenterFromRange;
	m_fCenterFromRange = RANGE_FROM_CENTER - m_fApprochDistance;
	if (m_fCenterFromRange < 0.0f) {
		//���ӂ���鏈���͍s�����Ȃ�.
		m_Camera.vPos.x = INTERMEDIATE_POINT_POS.x;
		m_Camera.vPos.z = INTERMEDIATE_POINT_POS.z;

		//���~�ړ������ɕύX.
		m_ApprochFlag = APPROCH_SMARTPHONE_FLAG;
		m_MoveFlag = CHANGE_STAGE_FLAG;
		return;
	}

	//���ӂ���鏈���֐�.
	RotateSurrunding(INTERMEDIATE_INIT_HEIGHT_RANGE, m_fCenterFromRange);
}

//==============================================.
//		���ӂ���鏈���֐�.
//==============================================.
void CCameraEnding::RotateSurrunding(const float& fCriteriaRange, const float& fCenterRange)
{

	//�ړ��p�x�͈̔�.
	const float MOVE_ANGLE_RANGE = fabsf(ANGLE_MAX - ANGLE_MIN);
	const float MOVE_ANGLE_POS_UNIT = MOVE_ANGLE_RANGE / fCriteriaRange;
	m_fAngle -= MOVE_SPEED * MOVE_ANGLE_POS_UNIT;

	//���W�A��.
	const float RADIAN = static_cast<float>(D3DXToRadian(m_fAngle));
	m_Camera.vPos.x = m_Camera.vLook.x + (cosf(RADIAN) * fCenterRange);
	m_Camera.vPos.z = m_Camera.vLook.z + (sinf(RADIAN) * fCenterRange);

	if (m_fAngle < ANGLE_MIN) {
		m_fAngle = ANGLE_MIN;
	}

}

//==============================================.
//		�����_�ړ������֐�.
//==============================================.
void CCameraEnding::MoveLook()
{
	//�����l�ƒ��Ԓn�_�Ƃ̋���.
	const D3DXVECTOR3 Intermediate_Init_Look = INTERMEDIATE_POINT_LOOK - INIT_CAMERA_LOOK;
	const float LOOK_LENGTH = D3DXVec3Length(&Intermediate_Init_Look);
	const D3DXVECTOR3 LOOK_UNIT = Intermediate_Init_Look / LOOK_LENGTH;
	m_Camera.vLook += MOVE_SPEED * LOOK_UNIT;
	if (m_Camera.vLook.y < INTERMEDIATE_POINT_LOOK.y) {
		m_Camera.vLook = INTERMEDIATE_POINT_LOOK;
	}

}

//==============================================.
//		���~�ړ������֐�.
//==============================================.
void CCameraEnding::MoveDown()
{
	m_Camera.vPos.y -= 0.2f;

	if (m_Camera.vPos.y < 2.5f) {
		m_Camera.vPos.y = 2.5f;
	}
}