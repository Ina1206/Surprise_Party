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

	if (m_MoveFlag & STOP_FLAG) {
		return;
	}

	//�J�����̈ړ�����.
	const float CAMERA_POS_LENGTH = D3DXVec3Length(&CAMERA_POS_DISTANCE);			//�x�N�g���̒���.
	const D3DXVECTOR3	CAMERA_POS_UNIT = CAMERA_POS_DISTANCE / CAMERA_POS_LENGTH;	//�P�ʃx�N�g��.
	m_Camera.vPos += CAMER_MOVE_SPEED * CAMERA_POS_UNIT * static_cast<float>(m_MoveCameraDirection);

	//�J�����̒����_�ړ�����.
	const float CAMERA_LOOK_LENGTH = D3DXVec3Length(&CAMERA_LOOK_DISTANCE);				//�x�N�g���̒���.
	const D3DXVECTOR3	CAMERA_LOOK_UNIT = CAMERA_LOOK_DISTANCE / CAMERA_LOOK_LENGTH;	//�P�ʃx�N�g��.
	const float	CAMERA_LENGTH_RATIO = CAMERA_LOOK_LENGTH / CAMERA_POS_LENGTH;			//�����̔䗦.
	m_Camera.vLook += CAMER_MOVE_SPEED * CAMERA_LOOK_UNIT * static_cast<float>(m_MoveCameraDirection) * CAMERA_LENGTH_RATIO;

	//�J�����̐ڋ߂���������.
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

	//�J���������̂��������.
	if (m_Camera.vPos.x < INIT_CAMERA_POS.x) {
		m_Camera.vPos = INIT_CAMERA_POS;
		//if (m_pCSpeakBigGhost->GetFinishFlag() & m_pCSpeakBigGhost->FINISH_NEXT_GAME) {
		//	//�Q�[�����C���ɐi��.
		//	m_bChangeStageFlag = true;
		//	return;
		//}
		////�G���f�B���O�ɐi��.
		//m_FinishFlag = FINISH_NEXT_ENDING;
		m_Camera.vLook = INIT_CAMERA_LOOK;
		m_MoveFlag = STOP_FLAG | MOVE_FINISH_FLAG;
		
	}

	if (m_Camera.vLook.x < INIT_CAMERA_LOOK.x) {
		m_Camera.vLook = INIT_CAMERA_LOOK;
	}

}

//===============================================.
//			�����������֐�.
//===============================================.
void CCameraGhostSpeakStage::Init()
{
	m_Camera.vPos = D3DXVECTOR3(5.0f, 2.5f, -3.5f);
	m_Camera.vLook = D3DXVECTOR3(5.0f, 2.5f, 5.0f);

	m_MoveCameraDirection = GET_CLOSER_CAMERA_DIRECT;
}

//===============================================.
//			��������֐�.
//===============================================.
void CCameraGhostSpeakStage::Release()
{

}