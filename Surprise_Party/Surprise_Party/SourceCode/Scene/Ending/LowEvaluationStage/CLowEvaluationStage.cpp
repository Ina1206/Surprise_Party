#include "CLowEvaluationStage.h"

/***********************************************
*		��]���̃X�e�[�W�N���X.
*****************/
CLowEvaluationStage::CLowEvaluationStage()
{
	//�����������֐�.
	Init();
}

CLowEvaluationStage::~CLowEvaluationStage()
{
	//��������֐�.
	Release();
}

//===============================================.
//		�X�V�����֐�.
//===============================================.
void CLowEvaluationStage::Update()
{
	//�J�����̍X�V�����֐�.
	m_pCCameraEnding->Update();


	//�������̍X�V����.
	for (unsigned int ghost = 0; ghost < m_pCGhost.size(); ghost++) {
		m_pCGhost[ghost]->Update();
	}

	//����ʂ̃t�F�[�h.
	if (m_pCWhiteScreenFade->GetFadeFlag() & m_pCWhiteScreenFade->FADE_FINISH_FLAG) {
		return;
	}
	m_pCWhiteScreenFade->Update();

}

//================================================.
//		�`�揈���֐�.
//================================================.
void CLowEvaluationStage::Render()
{
	//���̕`��.
	RenderFloor();

	//�������̕`��.
	RenderGhost();

	//����ʂ̃t�F�[�h�`��.
	if (!(m_pCWhiteScreenFade->GetFadeFlag() & m_pCWhiteScreenFade->FADE_FINISH_FLAG)) {
		m_pCWhiteScreenFade->Render();
	}
}

//================================================.
//		�����������֐�.
//================================================.
void CLowEvaluationStage::Init()
{
	//�t�F�[�h�A�E�g�Őݒ�.
	m_pCWhiteScreenFade->SetFadeFlag(m_pCWhiteScreenFade->FADE_OUT_FLAG);

	for (unsigned int ghost = 0; ghost < m_pCGhost.size(); ghost++) {
		m_pCGhost[ghost]->SetEmotionNum(static_cast<int>(CGhostBase::enEmotionType::HaveTrounble));
	}

	m_pCCameraEnding->SetMoveFlag(m_pCCameraEnding->STOP_FLAG);

}

//================================================.
//		��������֐�.
//================================================.
void CLowEvaluationStage::Release()
{

}