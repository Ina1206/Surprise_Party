#include "CEnding.h"
#include "HightEvaluationStage\CHightEvaluationStage.h"
#include "IntermediateEvaluationStage\CIntermediateEvaluationStage.h"
#include "LowEvaluationStage\CLowEvaluationStage.h"

CEnding::CEnding()
	: m_pCEndingStageBase	(nullptr)
	, m_ChangeStageCnt		(0)
{
	//�����������֐�.
	Init();
}

CEnding::~CEnding()
{
	//��������֐�.
	Release();
}

//=================================.
//		�X�V�����֐�.
//=================================.
void CEnding::UpDate()
{
	m_Evaluation = 0;

	//�]���u�������֐�.
	m_pCEndingStageBase->SetEvaluation(m_Evaluation);
	//�X�V�����֐�.
	m_pCEndingStageBase->Update();

	//�X�e�[�W�ύX����.
	if (m_pCEndingStageBase->GetChangeStage() == true) {
		ChangeStage();
	}
}

//==================================.
//		�`�揈���֐�.
//==================================.
void CEnding::Render()
{
	m_pCEndingStageBase->RenderInitSetting(m_mProj);
	m_pCEndingStageBase->Render();
}

//==================================.
//		�����������֐�.
//==================================.
void CEnding::Init()
{
	m_pCEndingStageBase.reset(new CBeforeResultStage());
	//m_pCEndingStageBase.reset(new CHightEvaluationStage());
}

//==================================.
//		��������֐�.
//==================================.
void CEnding::Release()
{

}

//==================================.
//		�X�e�[�W�ύX�����֐�.
//==================================.
void CEnding::ChangeStage()
{
	if (m_ChangeStageCnt > 0) {
		m_bChangeScene = true;
		return;
	}

	//�X�e�[�W���菈���֐�.
	m_pCEndingStageBase.reset(DecideStage());

	m_ChangeStageCnt++;
}

//==================================.
//		�X�e�[�W���菈���֐�.
//==================================.
CEndingStageBase*	CEnding::DecideStage()
{
	if (m_Evaluation == 0) {
		//���]���N���X.
		return new CHightEvaluationStage();
	}

	if (m_Evaluation == 1) {
		//���ԕ]���N���X.
		return new CIntermediateEvaluationStage();
	}

	return new CLowEvaluationStage();
}