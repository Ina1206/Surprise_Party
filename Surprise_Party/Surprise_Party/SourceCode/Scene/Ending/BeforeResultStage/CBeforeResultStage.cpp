#include "CBeforeResultStage.h"

#include "..\..\..\GameObject\Object\StaticObject\SmartPhone\CSmartPhone.h"

/********************************************
*		���ʔ��\�O�̃X�e�[�W�N���X.
******************/
CBeforeResultStage::CBeforeResultStage()
	: m_pCReputationSNS		(nullptr)
	, m_pCSmartPhone		(nullptr)
	, m_pCPlaySoundManager	(CPlaySoundManager::GetPlaySoundManager())
	, m_bPlaySE				(false)
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
	//BGM�̉��ʂ�ݒ菈���֐�.
	SettingBGMVolume();

	//�J�����X�V�����֐�.
	m_pCCameraEnding->Update();

	//�������B�̍X�V�����֐�.
	for (unsigned int ghost = 0; ghost < m_pCGhost.size(); ghost++) {
		m_pCGhost[ghost]->Update();
	}

	//�X�}�[�g�t�H���̍X�V�����֐�.
	m_pCSmartPhone->Update();
	
	if (m_pCCameraEnding->GetMoveFlag() & m_pCCameraEnding->CHANGE_STAGE_FLAG) {
		//��ԂƂ���SE�Đ�����.
		if (m_bPlaySE == false) {
			m_pCPlaySoundManager->SetPlaySE(enSEType::JumpSNS);
			m_bPlaySE = true;
		}

		if (m_pCWhiteScreenFade->GetFadeFlag() & m_pCWhiteScreenFade->FADE_FINISH_FLAG) {
			//SNS�X�V�����֐�.
			m_pCReputationSNS->Update();
			
			if (m_pCReputationSNS->GetChangeStage() & m_pCReputationSNS->CHANGE_STAGE_FLAG) {
				m_bChangeStage = true;
			}
			return;
		}

		m_pCWhiteScreenFade->SetFadeFlag(m_pCWhiteScreenFade->FADE_IN_FLAG);
		m_pCWhiteScreenFade->Update();
	}

	//���͌��菈���֐�.
	DecideString();
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

	//�X�}�[�g�t�H���̕`�揈���֐�.
	RenderSmartPhone();

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
	m_pCSmartPhone.reset(new CSmartPhone());

	m_pCCameraEnding->SetMoveFlag(m_pCCameraEnding->MOVE_FLAG);
}

//=======================================.
//		��������֐�.
//=======================================.
void CBeforeResultStage::Release()
{

}

//=======================================.
//		���͌��菈���֐�.
//=======================================.
void CBeforeResultStage::DecideString()
{
	if (m_OldEvaluation != INIT_EVALUATION_NUM) {
		return;
	}

	if (m_Evaluation != m_OldEvaluation) {
		//���͌��菈���֐�.
		m_pCReputationSNS->DecideString(m_Evaluation);
	}

	m_OldEvaluation = m_Evaluation;
}

//========================================.
//		�X�}�[�g�t�H���`�揈���֐�.
//========================================.
void CBeforeResultStage::RenderSmartPhone()
{
	//���C�g���.
	const LIGHT m_Light = m_pCBackstageLight->GetLight();
	//�J�����ʒu.
	const D3DXVECTOR3 m_vCameraPos = m_pCCameraEnding->GetPos();

	m_pCSmartPhone->SetPos(m_vObjLookPos);
	m_pCSmartPhone->SetCameraPos(m_vCameraPos);
	m_pCSmartPhone->RenderInitSetting(m_mView, m_mProj, m_Light);
	m_pCSmartPhone->Render();
}