#include "CEnding.h"
#include "HightEvaluationStage\CHightEvaluationStage.h"
#include "IntermediateEvaluationStage\CIntermediateEvaluationStage.h"
#include "LowEvaluationStage\CLowEvaluationStage.h"
#include "..\..\Sound\PlaySoundManager\CPlaySoundManager.h"

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
	//���𗬂��Ǘ��N���X.
	CPlaySoundManager* m_pCPlaySoundManager = CPlaySoundManager::GetPlaySoundManager();

	if (m_Evaluation == 0) {
		//��]���N���X.
		m_pCPlaySoundManager->ChangePlayingBGM(enBGMType::LowEvaluationStage);
		return new CLowEvaluationStage(m_Evaluation);
	}

	if (m_Evaluation == 1) {
		//���ԕ]���N���X.
		m_pCPlaySoundManager->ChangePlayingBGM(enBGMType::IntermediateEvaluationStage);
		return new CIntermediateEvaluationStage(m_Evaluation);
	}

	//���]���N���X.
	m_pCPlaySoundManager->ChangePlayingBGM(enBGMType::HightEvaluationStage);
	return new CHightEvaluationStage(m_Evaluation);
}