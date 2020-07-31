#ifndef INTERMEDIATE_EVALUATION_STRING_H
#define INTERMEDIATE_EVALUATION_STRING_H

#include "..\EvaluationUIBase\CEvaluationUIBase.h"

/***************************************
*		���ԕ]���̕��̓N���X.
***************/
class CIntermediateEvaluationString
	: public CEvaluationUIBase
{
public:
	CIntermediateEvaluationString();
	~CIntermediateEvaluationString();

	//==========================�萔==========================//.
	const D3DXVECTOR3	BASE_POS				= D3DXVECTOR3(100.0f, 100.0f, 0.0f);//����W.

	const unsigned int	FINISH_SCALE_FLAG		= (1 << 0);							//�g��I���t���O.
	const unsigned int	FINISH_ROTATION_FLAG	= (1 << 1);							//��]�I���t���O.

	const D3DXVECTOR3	SCALE_SPEED				= D3DXVECTOR3(0.05f, 0.05f, 0.05f);	//�g�呬�x.
	const float			ROTATION_SPEED			= 0.2f;								//��]���x.
	const float			ROT_MAX					= 360.0f;							//�p�x�ő�l.

	//==========================�֐�==========================//.
	void Update();					//�X�V�����֐�.

private:
	//==========================�֐�==========================//.
	void Init();					//�����������֐�.
	void Release();					//��������֐�.
	void Scale();					//�g�又���֐�.
	void Rotation();				//��]�����֐�.
	void DisplayAllAtOnce();		//��C�ɕ\�������֐�.

	//==========================�ϐ�==========================//.
	unsigned int m_ActFinishFlag;	//�s���I���t���O.

};


#endif	//#ifndef INTERMEDIATE_EVALUATION_STRING_H