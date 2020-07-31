#include "CCameraGhostSpeakStage.h"

/**********************************************
*		���������b���X�e�[�W�̃J�����N���X.
**************/
CCameraGhostSpeakStage::CCameraGhostSpeakStage()
{
	//�����������֐�.
	Init();
}

CCameraGhostSpeakStage::~CCameraGhostSpeakStage()
{
	//��������֐�.
	Release();
}

//===============================================.
//			�X�V�����֐�.
//===============================================.
void CCameraGhostSpeakStage::Update()
{
	//���X�L�b�v���Ă����珈���I��.
	if (m_bCanSkip == false) {
		return;
	}

	if (m_MoveFlag & STOP_FLAG) {
		return;
	}

	//�ړ������֐�.
	Move();

	if (m_MoveCameraDirection == GET_CLOSER_CAMERA_DIRECT) {
		//�ڋߏ�������֐�.
		GetCloserUpperLimit();
		return;
	}

	//���̂���������֐�.
	FarAwayUpperLimit();
}

//===============================================.
//			�����������֐�.
//===============================================.
void CCameraGhostSpeakStage::Init()
{
	m_Camera.vPos = INIT_CAMERA_POS;
	m_Camera.vLook = INIT_CAMERA_LOOK;

	m_MoveCameraDirection = GET_CLOSER_CAMERA_DIRECT;
}

//===============================================.
//			��������֐�.
//===============================================.
void CCameraGhostSpeakStage::Release()
{


}

//===============================================.
//			�ړ������֐�.
//===============================================.
void CCameraGhostSpeakStage::Move()
{
	//�J�����̈ړ�����.
	const float CAMERA_POS_LENGTH = D3DXVec3Length(&CAMERA_POS_DISTANCE);			//�x�N�g���̒���.
	const D3DXVECTOR3	CAMERA_POS_UNIT = CAMERA_POS_DISTANCE / CAMERA_POS_LENGTH;	//�P�ʃx�N�g��.
	m_Camera.vPos += CAMER_MOVE_SPEED * CAMERA_POS_UNIT * static_cast<float>(m_MoveCameraDirection);

	//�J�����̒����_�ړ�����.
	const float CAMERA_LOOK_LENGTH = D3DXVec3Length(&CAMERA_LOOK_DISTANCE);				//�x�N�g���̒���.
	const D3DXVECTOR3	CAMERA_LOOK_UNIT = CAMERA_LOOK_DISTANCE / CAMERA_LOOK_LENGTH;	//�P�ʃx�N�g��.
	const float	CAMERA_LENGTH_RATIO = CAMERA_LOOK_LENGTH / CAMERA_POS_LENGTH;			//�����̔䗦.
	m_Camera.vLook += CAMER_MOVE_SPEED * CAMERA_LOOK_UNIT * static_cast<float>(m_MoveCameraDirection) * CAMERA_LENGTH_RATIO;

}

//===============================================.
//			�ڋߏ�������֐�.
//===============================================.
void CCameraGhostSpeakStage::GetCloserUpperLimit()
{
	//�X�L�b�v����.
	if (m_MoveFlag & SKIP_FLAG) {
		m_Camera.vPos	= SPEAK_START_POS;
		m_Camera.vLook	= SPEAK_START_LOOK;
		m_bCanSkip		= false;
	}

	//������B���̏���.
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
//			���̂���������֐�.
//===============================================.
void CCameraGhostSpeakStage::FarAwayUpperLimit()
{
	//�X�L�b�v����.
	if (m_MoveFlag & SKIP_FLAG) {
		m_Camera.vPos	= INIT_CAMERA_POS;
		m_Camera.vLook	= INIT_CAMERA_LOOK;
	}

	//������B���̏���.
	if (m_Camera.vPos.x <= INIT_CAMERA_POS.x ||
		m_Camera.vLook.x <= INIT_CAMERA_LOOK.x) {
		m_Camera.vPos	= INIT_CAMERA_POS;
		m_Camera.vLook	= INIT_CAMERA_LOOK;
		m_MoveFlag		= STOP_FLAG | CHANGE_STAGE_FLAG;
	}

}