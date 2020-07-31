#ifndef CHIGHT_EVALUATION_STRING_H
#define CHIGHT_EVALUATION_STRING_H

#include "..\EvaluationUIBase\CEvaluationUIBase.h"

/**********************************************
*		���]�������N���X.
*********************/
class CHightEvaluationString
	: public CEvaluationUIBase
{
public:
	CHightEvaluationString();
	~CHightEvaluationString();

	//=====================�萔======================//.
	const D3DXVECTOR3	FINISH_BASE_POS	= D3DXVECTOR3(10.0f, 50.0f, 0.0f);	//�ŏI��ʒu.
	const D3DXVECTOR3	INIT_POS		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�����ʒu.
	const unsigned int	BOUND_DOWN_FLAG = (1 << 0);							//�o�E���h������t���O.
	const unsigned int	BOUND_UP_FALG	= (1 << 1);							//�o�E���h�オ��t���O.
	const float			MOVE_SPEED		= 0.5f;								//�ړ����x.
	const float			ADD_ACC_SPEED	= 2.0f;								//�����x���Z���x.
	const float			GRAVITY			= 20.0f;							//�d��.
	const float			JUMP_CNT_MAX	= 2;								//�W�����v�J�E���g�ő�l.
	const float			BOUND_SPEED		= 0.1f;								//�o�E���h���x.
	const float			DISP_SPEED		= 0.3f;								//�\�����x.

	//=====================�֐�======================//.
	void Update();					//�X�V�����֐�.

protected:
	//=====================�֐�======================//.
	void Init();					//�����������֐�.
	void Release();					//��������֐�.
	void Disp();					//�\�������֐�.
	void Move();					//�ړ������֐�.
	void Jump();					//�W�����v�����֐�.
	void Bound();					//�o�E���h�����֐�.
	void DisplayAllAtOnce();		//��C�ɕ\�����鏈���֐�.

	//=====================�ϐ�======================//.
	float			m_fAcc;			//�����x.
	int				m_JumpCnt;		//�W�����v�J�E���g.
	int				m_BoundCnt;		//�o�E���h�J�E���g.
	unsigned int	m_BoundFlag;	//�o�E���h�t���O.
};

#endif	//#ifndef CHIGHT_EVALUATION_STRING_H.