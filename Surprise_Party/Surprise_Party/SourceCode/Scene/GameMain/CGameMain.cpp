#include "CGameMain.h"

CGameMain::CGameMain()
	: m_pCStageManager	(nullptr)
{
	//�����������֐�.
	Init();
}

CGameMain::~CGameMain()
{
	//��������֐�.
	Release();
}

//========================================.
//		�X�V�����֐�.
//========================================.
void CGameMain::UpDate()
{
	//�V�[���Ǘ��N���X�̍X�V�����֐�.
	m_pCStageManager->UpDate();

	if (m_pCStageManager->GetFinishFlag() & m_pCStageManager->FINISH_NEXT_TITLE) {
		m_bChangeScene = true;
	}
	if (m_pCStageManager->GetFinishFlag() & m_pCStageManager->FINISH_NEXT_ENDING) {
		m_Evaluation = m_pCStageManager->GetAverageEvaluation();
		m_bChangeScene = true;
	}
}

//========================================.
//		�`�揈���֐�.
//========================================.
void CGameMain::Render()
{
	//�|�[�Y�t���O.
	m_pCStageManager->SetPauseFlag(m_bPauseFlag);
	//�V�[���Ǘ��N���X�̕`�揈���֐�.
	m_pCStageManager->Render(m_mView, m_mProj);
}

//========================================.
//		�����������֐�.
//========================================.
void CGameMain::Init()
{
	//�V�[���Ǘ��N���X�̏�����.
	m_pCStageManager.reset(new CStageManager());
	m_pCStageManager->Init();


}

//========================================.
//		��������֐�.
//========================================.
void CGameMain::Release()
{
	//�X�e�[�W�Ǘ��N���X�̉�������֐�.
	m_pCStageManager->Release();

}