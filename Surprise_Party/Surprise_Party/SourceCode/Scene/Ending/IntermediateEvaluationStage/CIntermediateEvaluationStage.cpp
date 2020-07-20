#include "CIntermediateEvaluationStage.h"

/***********************************************
*		���ԕ]���X�e�[�W�N���X.
********************/
CIntermediateEvaluationStage::CIntermediateEvaluationStage()
	: CIntermediateEvaluationStage(0)
{

}

CIntermediateEvaluationStage::CIntermediateEvaluationStage(const int& EvaluationNum)
	: CEvaluationStageBase	(EvaluationNum)
{
	m_Evaluation = EvaluationNum;
	//�����������֐�.
	Init();
}

CIntermediateEvaluationStage::~CIntermediateEvaluationStage()
{
	//��������֐�.
	Release();
}

//========================================.
//		�����������֐�.
//========================================.
void CIntermediateEvaluationStage::Init()
{
	//�t�F�[�h�A�E�g�Őݒ�.
	m_pCWhiteScreenFade->SetFadeFlag(m_pCWhiteScreenFade->FADE_OUT_FLAG);

	//����������ݒ�.
	for (unsigned int ghost = 0; ghost < m_pCGhost.size(); ghost++) {
		if (ghost == BIG_GHOST_NUM) {
			//���.
			m_pCGhost[ghost]->SetEmotionNum(static_cast<int>(CGhostBase::enEmotionType::Rejoice));
			continue;
		}
		//��@��.
		m_pCGhost[ghost]->SetEmotionNum(static_cast<int>(CGhostBase::enEmotionType::GoodFeeling));
	}
	//�J�����I��.
	m_pCCameraEnding->SetMoveFlag(m_pCCameraEnding->STOP_FLAG);

}

//========================================.
//		��������֐�.
//========================================.
void CIntermediateEvaluationStage::Release()
{

}