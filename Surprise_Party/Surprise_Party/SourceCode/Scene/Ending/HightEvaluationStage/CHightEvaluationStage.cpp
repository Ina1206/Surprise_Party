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