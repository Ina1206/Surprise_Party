#ifndef CLOW_EVALUATION_STAGE_H
#define CLOW_EVALUATION_STAGE_H

#include "..\EvaluationStageBase\CEvaluationStageBase.h"

/***********************************************
*		��]���̃X�e�[�W�N���X.
*****************/
class CLowEvaluationStage
	: public CEvaluationStageBase
{
public:
	CLowEvaluationStage();
	CLowEvaluationStage(const int& EvaluationNum);
	~CLowEvaluationStage();

private:
	//======================�֐�========================//.
	void Init();		//�����������֐�.
	void Release();		//��������֐�.


};

#endif	//#ifndef CLOW_EVALUATION_STAGE_H.