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
	~CIntermediateEvaluationStage();

private:
	//=========================�֐�==============================//.
	void Init();		//�����������֐�.
	void Release();		//��������֐�.


};


#endif	//#ifndef CINTERMEDIATE_EVALUATION_STAGE_H.