#ifndef CCAMERA_TITLE_H
#define CCAMERA_TITLE_H

#include "..\CCameraBase.h"

/*******************************************
*		�^�C�g���J�����N���X.
*************/
class CCameraTitle
	: public CCameraBase
{
public:
	CCameraTitle();
	~CCameraTitle();

	//=======================�萔==========================//.
	const unsigned int	MOVE_FROM_FRONT_FLAG	= (1 << 0);							//���ʈړ��t���O.
	const unsigned int	MOVE_FROM_OBLIQUE_FLAG	= (1 << 1);							//�΂߃J�����ړ��t���O.
	
	const D3DXVECTOR3	POS_FROM_FRONT			= D3DXVECTOR3(11.9f, 3.3f, -14.3f);	//���ʂ��猩��J�������W.
	const D3DXVECTOR3	LOOK_FROM_FRONT			= D3DXVECTOR3(11.9f, 3.3f, 4.0f);	//���ʂ��猩��J�����̒����_���W.
	
	const D3DXVECTOR3	POS_FROM_OBLIQUE		= D3DXVECTOR3(1.3f, 5.4f, -5.5f);	//�΂߂��猩��J�������W.
	const D3DXVECTOR3	LOOK_FROM_OBLIQUE		= D3DXVECTOR3(6.4f, 4.6f, 4.0f);	//�΂߂��猩��J�����̒����_.

	const float			MOVE_SPEED_FROM_FRONT	= 0.05f;							//���ʂ��猩��J�����ړ����x.
	const float			MOVE_SPEED_FROM_OBLIQUE = 0.02f;							//�΂߂��猩��J�����ړ����x.

	const float			MOVE_DISTANCE_MAX		= 70.0f;							//�ړ������ő�l.

	const int			MOVE_TYPE_MAX			= 2;								//�ړ��^�C�v�ő�l.

	//=======================�֐�==========================//.
	void Update();		//�X�V�����֐�.
	
private:
	//=======================�֐�==========================//.
	void Init();		//�����������֐�.
	void Release();		//��������֐�.

	//=======================�ϐ�==========================//.
	unsigned int	m_MoveTypeFlag;		//�ړ���ރt���O.
	float			m_fMoveDistance;	//�ړ�����.
	float			m_fMoveSpeed;		//�ړ����x.
};

#endif	//#ifndef CCAMERA_TITLE_H.