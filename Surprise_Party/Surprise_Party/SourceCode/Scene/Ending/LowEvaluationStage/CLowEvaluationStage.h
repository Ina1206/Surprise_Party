#ifndef CLOW_EVALUATION_STAGE_H
#define CLOW_EVALUATION_STAGE_H

#include "..\CEndingStageBase\CEndingStageBase.h"

/***********************************************
*		��]���̃X�e�[�W�N���X.
*****************/
class CLowEvaluationStage
	: public CEndingStageBase
{
public:
	CLowEvaluationStage();
	~CLowEvaluationStage();

	//======================�֐�========================//.
	void Update();		//�X�V�����֐�.
	void Render();		//�`�揈���֐�.

private:
	//======================�֐�========================//.
	void Init();		//�����������֐�.
	void Release();		//��������֐�.


};

#endif	//#ifndef CLOW_EVALUATION_STAGE_H.