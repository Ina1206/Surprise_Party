#ifndef CHIGHT_EVALUATION_STAGE_H
#define CHIGHT_EVALUATION_STAGE_H

#include "..\CEndingStageBase\CEndingStageBase.h"

/**************************************************
*			���]���X�e�[�W�N���X.
********************/
class CHightEvaluationStage
	: public CEndingStageBase
{
public:
	CHightEvaluationStage();
	~CHightEvaluationStage();

	//========================�֐�============================//.
	void Update();		//�X�V�����֐�.
	void Render();		//�`�揈���֐�.

private:
	//========================�֐�============================//.
	void Init();		//�����������֐�.
	void Release();		//��������֐�.

};

#endif	//#ifndef CHIGHT_EVALUATION_STAGE_H.