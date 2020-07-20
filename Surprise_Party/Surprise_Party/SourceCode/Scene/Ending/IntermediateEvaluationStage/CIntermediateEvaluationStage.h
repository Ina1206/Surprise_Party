#ifndef CINTERMEDIATE_EVALUATION_STAGE_H
#define CINTERMEDIATE_EVALUATION_STAGE_H

#include "..\EvaluationStageBase\CEvaluationStageBase.h"

/***********************************************
*		���ԕ]���X�e�[�W�N���X.
********************/
class CIntermediateEvaluationStage
	: public CEvaluationStageBase
{
public:
	CIntermediateEvaluationStage();
	CIntermediateEvaluationStage(const int& EvaluationNum);
	~CIntermediateEvaluationStage();

	//=========================�萔==============================//.
	const int BIG_GHOST_NUM = 2;	//�r�b�O�S�[�X�g�ԍ�.

private:
	//=========================�֐�==============================//.
	void Init();		//�����������֐�.
	void Release();		//��������֐�.


};


#endif	//#ifndef CINTERMEDIATE_EVALUATION_STAGE_H.