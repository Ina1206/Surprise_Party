#ifndef CINTERMEDIATE_EVALUATION_STAGE_H
#define CINTERMEDIATE_EVALUATION_STAGE_H

#include "..\CEndingStageBase\CEndingStageBase.h"

/***********************************************
*		���ԕ]���X�e�[�W�N���X.
********************/
class CIntermediateEvaluationStage
	: public CEndingStageBase
{
public:
	CIntermediateEvaluationStage();
	~CIntermediateEvaluationStage();

	//=========================�֐�==============================//.
	void Update();		//�X�V�����֐�.
	void Render();		//�`�揈���֐�.

private:
	//=========================�֐�==============================//.
	void Init();		//�����������֐�.
	void Release();		//��������֐�.


};


#endif	//#ifndef CINTERMEDIATE_EVALUATION_STAGE_H.