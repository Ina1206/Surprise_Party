#include "CBeforeResultStage.h"

#include "..\..\..\GameObject\Object\StaticObject\SmartPhone\CSmartPhone.h"

/********************************************
*		���ʔ��\�O�̃X�e�[�W�N���X.
******************/
CBeforeResultStage::CBeforeResultStage()
	: m_pCReputationSNS	(nullptr)
{
	//�����������֐�.
	Init();
}

CBeforeResultStage::~CBeforeResultStage()
{
	//��������֐�.
	Release();
}

//=======================================.
//		�X�V�����֐�.
//=======================================.
void CBeforeResultStage::Update()
{
	//�J�����X�V�����֐�.
	m_pCCameraEnding->Update();

	for (unsigned int ghost = 0; ghost < m_pCGhost.size(); ghost++) {
		m_pCGhost[ghost]->Update();
	}
	
	if (m_pCCameraEnding->GetMoveFlag() & m_pCCameraEnding->CHANGE_STAGE_FLAG) {
		
		if (m_pCWhiteScreenFade->GetFadeFlag() & m_pCWhiteScreenFade->FADE_FINISH_FLAG) {
			m_pCReputationSNS->Update();
			return;
		}

		m_pCWhiteScreenFade->SetFadeFlag(m_pCWhiteScreenFade->FADE_IN_FLAG);
		m_pCWhiteScreenFade->Update();
	}

}

//=======================================.
//		�`�揈���֐�.
//=======================================.
void CBeforeResultStage::Render()
{
	//���̕`�揈���֐�.
	RenderFloor();

	//�������`�揈���֐�.
	RenderGhost();

	//�t�F�[�h�`�揈���֐�.
	m_pCWhiteScreenFade->Render();

	//SNS�̕]���N���X.
	if (m_pCWhiteScreenFade->GetFadeFlag() & m_pCWhiteScreenFade->FADE_FINISH_FLAG) {
		m_pCReputationSNS->Render();
	}
}

//=======================================.
//		�����������֐�.
//=======================================.
void CBeforeResultStage::Init()
{
	m_pCReputationSNS.reset(new CReputationSNS());

	m_pCReputationSNS->DecideString(1);
}

//=======================================.
//		��������֐�.
//=======================================.
void CBeforeResultStage::Release()
{

}