#ifndef CEVALUATION_STAGE_BASE_H
#define CEVALUATION_STAGE_BASE_H

#include "..\CEndingStageBase\CEndingStageBase.h"

/**********************************************
*		�]���X�e�[�W���N���X.
************************/
class CEvaluationStageBase
	: public CEndingStageBase
{
public:
	CEvaluationStageBase();
	CEvaluationStageBase(const int& EvaluationNum);
	~CEvaluationStageBase();
	
	//======================�֐�=========================//.
	void Update();	//�X�V�����֐�.
	void Render();	//�`�揈���֐�.

protected:

private:

};

#endif	//#ifndef CEVALUATION_STAGE_BASE_H.