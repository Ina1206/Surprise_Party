#include "CEvaluationStageBase.h"

/**********************************************
*		�]���X�e�[�W���N���X.
************************/
CEvaluationStageBase::CEvaluationStageBase()
{

}

CEvaluationStageBase::~CEvaluationStageBase()
{

}

//===============================================.
//				�X�V�����֐�.
//===============================================.
void CEvaluationStageBase::Update()
{
	//���ʂ�UI�̍X�V�����֐�.
	UpdateCommonUI();

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

//===============================================.
//				�`�揈���֐�.
//===============================================.
void CEvaluationStageBase::Render()
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

	//���ʂ�UI�̕`�揈���֐�.
	RenderCommonUI();

	//PushEnter�`�揈���֐�.
	RenderPushEnter();

}