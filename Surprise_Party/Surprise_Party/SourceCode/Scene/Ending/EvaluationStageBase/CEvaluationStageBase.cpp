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
	//�J�����̍X�V�����֐�.
	m_pCCameraEnding->Update();

	if (m_UpdateFlag == 0) {
		//�t�F�[�h�X�V�����֐�.
		m_pCWhiteScreenFade->Update();

		//�t�F�[�h�I����ɋ������xUI�̏����J�n.
		if (m_pCWhiteScreenFade->GetFadeFlag() & m_pCWhiteScreenFade->FADE_FINISH_FLAG) {
			m_UpdateFlag = SURPRISE_DEGREE_FLAG;
		}
		return;
	}

	if (GetAsyncKeyState(VK_RETURN) & 0x0001) {
		m_bDisplayAllAtOnce = true;
	}

	//���ʂ�UI�̍X�V�����֐�.
	UpdateCommonUI();
	
	if (m_UpdateFlag & GHOST_FLAG) {
		//�������̍X�V����.
		for (unsigned int ghost = 0; ghost < m_pCGhost.size(); ghost++) {
			m_pCGhost[ghost]->Update();
		}
	}


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