#ifndef CEVALUATION_STAGE_BASE_H
#define CEVALUATION_STAGE_BASE_H

#include "..\CEndingStageBase\CEndingStageBase.h"
#include "..\..\UI\SceneUI\EndingUI\CEndingUI.h"

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
	void Update();			//�X�V�����֐�.
	void Render();			//�`�揈���֐�.

protected:

private:
	//======================�֐�=========================//.
	void InitUI();			//UI�̏����������֐�.
	void UpdateCommonUI();	//���ʂ�UI�̍X�V�����֐�.
	void RenderCommonUI();	//���ʂ�UI�̕`�揈���֐�.

	//========================�ϐ�=============================//.
	std::unique_ptr<CEndingUI>				m_pCEndingUI;				//EndingUI�N���X.

};

#endif	//#ifndef CEVALUATION_STAGE_BASE_H.