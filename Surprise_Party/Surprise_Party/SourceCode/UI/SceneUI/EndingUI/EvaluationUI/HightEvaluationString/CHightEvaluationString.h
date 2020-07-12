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

	//=====================�֐�======================//.
	void Update();		//�X�V�����֐�.

protected:
	//=====================�֐�======================//.
	void Init();		//�����������֐�.
	void Release();		//��������֐�.
	void Move();		//�ړ������֐�.
	void Jump();		//�W�����v�����֐�.
	void Bound();		//�o�E���h�����֐�.

	//=====================�ϐ�======================//.
	float	m_fAcc;			//�����x.
	int		m_JumpCnt;		//�W�����v�J�E���g.
	int		m_BoundCnt;		//�o�E���h�J�E���g.
};

#endif	//#ifndef CHIGHT_EVALUATION_STRING_H.