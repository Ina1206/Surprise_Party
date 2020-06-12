#include "CIntermediateEvaluationStage.h"

/***********************************************
*		���ԕ]���X�e�[�W�N���X.
********************/
CIntermediateEvaluationStage::CIntermediateEvaluationStage()
{
	//�����������֐�.
	Init();
}

CIntermediateEvaluationStage::~CIntermediateEvaluationStage()
{
	//��������֐�.
	Release();
}

//========================================.
//		�X�V�����֐�.
//========================================.
void CIntermediateEvaluationStage::Update()
{
	//�J�����̍X�V�����֐�.
	m_pCCameraEnding->Update();

	//�������̍X�V����.
	for (unsigned int ghost = 0; ghost < m_pCGhost.size(); ghost++) {
		m_pCGhost[ghost]->Update();
	}


	//����ʂ̃t�F�[�h.
	if (m_pCWhiteScreenFade->GetFadeFlag() & m_pCWhiteScreenFade->FADE_FINISH_FLAG) {
		//PushEnter�̍X�V�����֐�.
		UpdatePushEnter();
		return;
	}
	m_pCWhiteScreenFade->Update();

}

//========================================.
//		�`�揈���֐�.
//========================================.
void CIntermediateEvaluationStage::Render()
{
	//���̕`�揈���֐�.
	RenderFloor();

	//�������`�揈���֐�.
	RenderGhost();

	//����ʂ̃t�F�[�h�`��.
	if (!(m_pCWhiteScreenFade->GetFadeFlag() & m_pCWhiteScreenFade->FADE_FINISH_FLAG)) {
		m_pCWhiteScreenFade->Render();
		return;
	}

	//PushEnter�`�揈���֐�.
	RenderPushEnter();
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
		if (ghost == 2) {
			m_pCGhost[ghost]->SetEmotionNum(static_cast<int>(CGhostBase::enEmotionType::Rejoice));
			continue;
		}
		m_pCGhost[ghost]->SetEmotionNum(static_cast<int>(CGhostBase::enEmotionType::GoodFeeling));
	}

	m_pCCameraEnding->SetMoveFlag(m_pCCameraEnding->STOP_FLAG);

}

//========================================.
//		��������֐�.
//========================================.
void CIntermediateEvaluationStage::Release()
{

}