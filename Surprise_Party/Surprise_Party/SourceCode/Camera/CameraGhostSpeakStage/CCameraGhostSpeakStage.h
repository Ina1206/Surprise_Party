#ifndef CCAMERA_GHOST_SPEAK_STAGE_H
#define CCAMERA_GHOST_SPEAK_STAGE_H

#include "..\CCameraBase.h"

/**********************************************
*		���������b���X�e�[�W�̃J�����N���X.
**************/
class CCameraGhostSpeakStage
	: public CCameraBase
{
public:
	CCameraGhostSpeakStage();
	~CCameraGhostSpeakStage();

	//========================�萔=============================//.
	const D3DXVECTOR3	INIT_CAMERA_POS				= D3DXVECTOR3(5.0f, 2.5f, -3.5f);		//�J���������ʒu.
	const D3DXVECTOR3	INIT_CAMERA_LOOK			= D3DXVECTOR3(5.0f, 2.5f, 5.0f);		//�J�������������_.
	const D3DXVECTOR3	SPEAK_START_POS				= D3DXVECTOR3(6.0f, 2.7f, 1.3f);		//��b�J�n���̃J�������W.
	const D3DXVECTOR3	SPEAK_START_LOOK			= D3DXVECTOR3(6.0f, 2.2f, 5.0f);		//��b�J�n���̃J���������_.
	const D3DXVECTOR3	CAMERA_POS_DISTANCE			= SPEAK_START_POS - INIT_CAMERA_POS;	//�J�����̍��W����.
	const D3DXVECTOR3	CAMERA_LOOK_DISTANCE		= SPEAK_START_LOOK - INIT_CAMERA_LOOK;	//�J�����̒����_����.
	const float			CAMER_MOVE_SPEED			= 0.02f;								//�J�����ړ����x.
	const int			GET_CLOSER_CAMERA_DIRECT	= 1;									//�J�������ڋ߂������.
	const int			FAR_AWAY_CAMERA_DIRECT		= -1;									//�J���������̂�����.

	//========================�֐�==========================//.
	void Update();				//�X�V�����֐�.
private:
	//========================�֐�==========================//.
	void Init();				//�����������֐�.
	void Release();				//��������֐�.
	void Move();				//�ړ������֐�.
	void GetCloserUpperLimit();	//�ڋߏ�������֐�.
	void FarAwayUpperLimit();	//���̂���������֐�.

	//========================�ϐ�==========================//.
	int	m_MoveCameraDirection;	//�J�����ړ�����.

};

#endif	//#ifndef CCAMERA_GHOST_SPEAK_STAGE_H.