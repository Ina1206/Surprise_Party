#ifndef CLOW_EVALUATION_STRING_H
#define CLOW_EVALUATION_STRING_H

#include "..\EvaluationUIBase\CEvaluationUIBase.h"

/********************************************
*		��]������UI�����N���X.
*****************/
class CLowEvaluationString
	: public CEvaluationUIBase
{
public:
	CLowEvaluationString();
	~CLowEvaluationString();

	//=========================�萔===============================//.
	const unsigned int	DISP_FLAG				= (1 << 0);							//�\���t���O.
	const unsigned int	MOVE_FLAG				= (1 << 1);							//�ړ��t���O.
	const unsigned int	TRANSPARENT_FLAG		= (1 << 2);							//���߃t���O.

	const float			VERTICAL_MOVE_SPEED		= 0.5f;								//�c�ړ����x.
	const float			ANGLE_SPEED				= 5.0f;								//�p�x�̑��x.
	const float			MOVE_HORIZON_WIDTH		= 3.0f;								//�ړ�����.
	const float			ANGLE_MAX				= 360.0f;							//�p�x�ő�l.

	const float			PLAY_SOUND_RANGE_MIN	= 90.0f;							//���������͈͂̍ŏ��l.
	const float			PLAY_SOUND_RANGE_IN		= 180.0f;							//���������͈͂̒��Ԓn�_.
	const float			PLAY_SOUND_RANGE_MAX	= 270.0f;							//���������͈͂̍ő�l.
	const D3DXVECTOR3	FINSH_BASE_POS			= D3DXVECTOR3(50.0f, 27.5f, 0.0f);	//�ŏI����W.
	const int			FLOAT_SOUND_VOLUME_MAX	= 500;								//���V���̉��ʍő�l.

	//=========================�֐�===============================//.
	void Update();		//�X�V����.

private:
	//=========================�֐�===============================//.
	void Init();							//�����������֐�.
	void Release();							//��������֐�.
	void MoveBeforePos();					//�ړ��O�̍��W�ݒ菈���֐�.
	void Transparent();						//���ߏ����֐�.
	void Move();							//�ړ������֐�.
	void DisplayAllAtOnce();				//��C�ɕ\�����鏈���֐�.

	//=========================�ϐ�===============================//.
	unsigned int	m_ActFlag;				//�s���t���O.
	float			m_fAngle;				//�p�x.
	bool			m_bPlayFloatingSound;	//���V���Đ��t���O.
};

#endif	//#ifndef CLOW_EVALUATION_STRING_H.