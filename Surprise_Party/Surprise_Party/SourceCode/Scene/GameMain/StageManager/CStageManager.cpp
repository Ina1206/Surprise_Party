#include "CStageManager.h"

CStageManager::CStageManager()
	: m_pCStageBase			(nullptr)
	, m_StageType			(0)
	, m_StageNum			(0)
	, m_enBeforeEndingType	(CMainStage::enBeforeStageEndigneType::Nothing)
	, m_pCStageFade			(nullptr)
{

}

CStageManager::~CStageManager()
{

}

//====================================.
//		�����������֐�.
//====================================.
void CStageManager::Init()
{
	//�X�e�[�W�����ݒ�.
	m_StageType = static_cast<int>(enStageType::GhostSpeakStage);
	m_pCStageBase.reset(new CGhostSpeakStage(m_StageNum));

	//�X�e�[�W�t�F�[�h�C���X�^���X��.
	m_pCStageFade.reset(new CStageFade());
}

//====================================.
//		�X�V�����֐�.
//====================================.
void CStageManager::UpDate()
{
	//�X�e�[�W�t�F�[�h�X�V�����֐�.
	m_pCStageFade->UpDate();

	if (m_pCStageFade->GetCurtainMoveFlag() & m_pCStageFade->CHANGE_STAGE_FLAG) {
		//�X�e�[�W�ύX�����֐�.
		ChangeStage();
	}

	bool m_bControlFlag = true;
	//�t�F�[�h���̓X�e�[�W�n���������Ȃ�.
	if (m_pCStageFade->GetCurtainMoveFlag() != 0) {
		m_bControlFlag = false;
	}
	//�X�e�[�W�̍X�V�����֐�.
	m_pCStageBase->UpDate(m_bControlFlag);


#ifdef _DEBUG
	//�f�o�b�O�p�X�e�[�W�ύX�����֐�.
	m_pCStageBase->DebugStageChange();
#endif	//#ifdef _DEBUG.

	if (m_pCStageBase->GetChangeStageFlag() == true) {
		//
		if (m_StageType == static_cast<int>(enStageType::GhostSpeakStage)) {
			m_pCStageFade->SetCurtainMoveFlag(m_pCStageFade->OPENING_FLAG | m_pCStageFade->CLOSE_CURTAIN_FLAG);
			return;
		}

		m_pCStageFade->SetCurtainMoveFlag(m_pCStageFade->CLOSE_FLAG | m_pCStageFade->CLOSE_CURTAIN_FLAG);
	}
}

//====================================.
//		�`�揈���֐�.
//====================================.
void CStageManager::Render(const D3DXMATRIX& mView, const D3DXMATRIX& mProj, const D3DXVECTOR3& vLightPos, const D3DXVECTOR3& vCameraPos)
{
	//�X�e�[�W�̕`�揉���ݒ菈���֐�.
	m_pCStageBase->RenderInitSetting(mView, mProj, vLightPos, vCameraPos);
	//�X�e�[�W�̕`�揈���֐�.
	m_pCStageBase->Render();

	//�X�e�[�W�t�F�[�h�`�揈���֐�.
	m_pCStageFade->Render();
}

//====================================.
//		��������֐�.
//====================================.
void CStageManager::Release()
{
	
}

//====================================.
//		�X�e�[�W�ύX�����֐�.
//====================================.
void CStageManager::ChangeStage()
{
	//�X�e�[�W�̎�ޕύX.
	switch (static_cast<enStageType>(m_StageType)) {
	case enStageType::GhostSpeakStage:
		//���̃X�e�[�W��.
		m_StageNum++;
		m_pCStageBase.reset(new CMainStage(m_StageNum, m_enBeforeEndingType));
		break;
	case enStageType::MainStage:
		m_enBeforeEndingType = m_pCStageBase->GetBeforeStageEndingType();
		m_pCStageBase.reset(new CGhostSpeakStage(m_StageNum));
		break;
	}

	m_StageType++;
	if (m_StageType >= static_cast<int>(enStageType::Max)) {
		m_StageType = static_cast<int>(enStageType::Start);
	}
}