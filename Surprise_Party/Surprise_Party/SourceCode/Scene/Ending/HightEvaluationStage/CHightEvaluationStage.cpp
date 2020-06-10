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
	//����ʂ̃t�F�[�h.
	if (m_pCWhiteScreenFade->GetFadeFlag() & m_pCWhiteScreenFade->FADE_FINISH_FLAG) {
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
	}
}

//=============================================.
//			�����������֐�.
//=============================================.
void CHightEvaluationStage::Init()
{
	m_pCWhiteScreenFade->SetFadeFlag(m_pCWhiteScreenFade->FADE_OUT_FLAG);
}

//=============================================.
//			��������֐�.
//=============================================.
void CHightEvaluationStage::Release()
{

}