#ifndef CHIGHT_EVALUATION_STAGE_H
#define CHIGHT_EVALUATION_STAGE_H

#include "..\EvaluationStageBase\CEvaluationStageBase.h"

/**************************************************
*			���]���X�e�[�W�N���X.
********************/
class CHightEvaluationStage
	: public CEvaluationStageBase
{
public:
	CHightEvaluationStage();
	~CHightEvaluationStage();

private:
	//========================�֐�============================//.
	void Init();		//�����������֐�.
	void Release();		//��������֐�.

};

#endif	//#ifndef CHIGHT_EVALUATION_STAGE_H.