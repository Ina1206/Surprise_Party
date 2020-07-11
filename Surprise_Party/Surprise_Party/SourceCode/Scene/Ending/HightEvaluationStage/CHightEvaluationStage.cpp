#include "CHightEvaluationStage.h"

/**********************************************
*			���]���X�e�[�W�N���X.
*******************/
CHightEvaluationStage::CHightEvaluationStage()
{
	//�����������֐�.
	Init();
}

CHightEvaluationStage::~CHightEvaluationStage()
{
	//��������֐�.
	Release();
}

//=============================================.
//			�X�V�����֐�.
//=============================================.
void CHightEvaluationStage::Update()
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

//=============================================.
//			�`�揈���֐�.
//=============================================.
void CHightEvaluationStage::Render()
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

//=============================================.
//			�����������֐�.
//=============================================.
void CHightEvaluationStage::Init()
{
	//�t�F�[�h�A�E�g�Őݒ�.
	m_pCWhiteScreenFade->SetFadeFlag(m_pCWhiteScreenFade->FADE_OUT_FLAG);

	//����������ݒ�.
	for (unsigned int ghost = 0; ghost < m_pCGhost.size(); ghost++) {
		m_pCGhost[ghost]->SetEmotionNum(static_cast<int>(CGhostBase::enEmotionType::Rejoice));
	}

	m_pCCameraEnding->SetMoveFlag(m_pCCameraEnding->STOP_FLAG);
	
}

//=============================================.
//			��������֐�.
//=============================================.
void CHightEvaluationStage::Release()
{

}