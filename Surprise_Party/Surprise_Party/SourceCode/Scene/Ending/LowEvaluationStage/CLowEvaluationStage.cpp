#include "CLowEvaluationStage.h"

/***********************************************
*		��]���̃X�e�[�W�N���X.
*****************/
CLowEvaluationStage::CLowEvaluationStage()
{

}

CLowEvaluationStage::CLowEvaluationStage(const int& EvaluationNum)
	: CEvaluationStageBase	(EvaluationNum)
{
	m_Evaluation = EvaluationNum;
	//�����������֐�.
	Init();
}

CLowEvaluationStage::~CLowEvaluationStage()
{
	//��������֐�.
	Release();
}

//================================================.
//		�����������֐�.
//================================================.
void CLowEvaluationStage::Init()
{
	//�t�F�[�h�A�E�g�Őݒ�.
	m_pCWhiteScreenFade->SetFadeFlag(m_pCWhiteScreenFade->FADE_OUT_FLAG);

	//����ݒ�.
	for (unsigned int ghost = 0; ghost < m_pCGhost.size(); ghost++) {
		m_pCGhost[ghost]->SetEmotionNum(static_cast<int>(CGhostBase::enEmotionType::HaveTrounble));
	}

	//�J�����ړ���~.
	m_pCCameraEnding->SetMoveFlag(m_pCCameraEnding->STOP_FLAG);

}

//================================================.
//		��������֐�.
//================================================.
void CLowEvaluationStage::Release()
{

}