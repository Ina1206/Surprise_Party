#include "CStageManager.h"

CStageManager::CStageManager()
	: m_pCStageBase			()
	, m_StageType			(0)
	, m_StageNum			(0)
	, m_enBeforeEndingType	(CMainStage::enBeforeStageEndigneType::Nothing)
	, m_pCStageFade			(nullptr)
	, m_FinishFlag			(0)
	, m_bOldTutorialFlag	(false)
	, m_AllEndingType		(0)
	, m_bPauseFlag			(false)
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
	m_pCStageBase.resize(1);
	//�X�e�[�W�����ݒ�.
	//m_StageType = static_cast<int>(CStageBase::enStageType::MainStage);
	//m_pCStageBase[NORMAL_STAGE_NUM].reset(new CMainStage(m_StageNum, CStageBase::enStageType::MainStage, CStageBase::enBeforeStageEndigneType::Bad));
	m_StageType = static_cast<int>(CStageBase::enStageType::GhostSpeakStage);
	m_pCStageBase[NORMAL_STAGE_NUM].reset(new CGhostSpeakStage(m_StageNum, m_enBeforeEndingType));

	//�X�e�[�W�t�F�[�h�C���X�^���X��.
	m_pCStageFade.reset(new CStageFade());
}

//====================================.
//		�X�V�����֐�.
//====================================.
void CStageManager::UpDate()
{

	//�X�e�[�W�t�F�[�h�X�V�����֐�.
	m_pCStageFade->Update();

	if (m_pCStageFade->GetCurtainMoveFlag() & m_pCStageFade->CHANGE_STAGE_FLAG) {
		//�X�e�[�W�ύX�����֐�.
		ChangeStage();
	}
	const int STAGE_TYPE_NUM = m_pCStageBase.size() - 1;

	bool m_bControlFlag = true;
	//�t�F�[�h���̓X�e�[�W�n���������Ȃ�.
	if (m_pCStageFade->GetCurtainMoveFlag() != 0) {
		m_bControlFlag = false;
	}
	//�X�e�[�W�̍X�V�����֐�.
	m_pCStageBase[STAGE_TYPE_NUM]->UpDate(m_bControlFlag);


#ifdef _DEBUG
	//�f�o�b�O�p�X�e�[�W�ύX�����֐�.
	m_pCStageBase[STAGE_TYPE_NUM]->DebugStageChange();
#endif	//#ifdef _DEBUG.

	if (m_pCStageBase[STAGE_TYPE_NUM]->GetChangeStageFlag() == true ||
		m_pCStageBase[STAGE_TYPE_NUM]->GetTutorialFlag() != m_bOldTutorialFlag) {
		if (m_StageType == static_cast<int>(CStageBase::enStageType::GhostSpeakStage)){
			if (m_bOldTutorialFlag == 0 || m_bOldTutorialFlag & m_pCStageBase[STAGE_TYPE_NUM]->TUTORIAL_FINISH) {
				//�J�X���̃J�[�e���̓���.
				m_pCStageFade->SetCurtainMoveFlag(m_pCStageFade->OPENING_FLAG | m_pCStageFade->CLOSE_CURTAIN_FLAG);
				return;
			}
		}
		//�X���̃J�[�e���̓���.
		m_pCStageFade->SetCurtainMoveFlag(m_pCStageFade->CLOSE_FLAG | m_pCStageFade->CLOSE_CURTAIN_FLAG);
	}

	//�I������.
	if (m_pCStageBase[STAGE_TYPE_NUM]->GetFinishFlag() & m_pCStageBase[STAGE_TYPE_NUM]->FINISH_NEXT_ENDING) {
		m_FinishFlag = FINISH_NEXT_ENDING;
	}
	if (m_pCStageBase[STAGE_TYPE_NUM]->GetFinishFlag() & m_pCStageBase[STAGE_TYPE_NUM]->FINISH_NEXT_TITLE) {
		m_FinishFlag = FINISH_NEXT_TITLE;
	}
}

//====================================.
//		�`�揈���֐�.
//====================================.
void CStageManager::Render(const D3DXMATRIX& mView, const D3DXMATRIX& mProj)
{
	const int STAGE_TYPE_NUM = m_pCStageBase.size() - 1;

	//�|�[�Y�t���O.
	m_pCStageBase[STAGE_TYPE_NUM]->SetPauseFlag(m_bPauseFlag);

	//�X�e�[�W�̕`�揉���ݒ菈���֐�.
	m_pCStageBase[STAGE_TYPE_NUM]->RenderInitSetting(mView, mProj);
	//�X�e�[�W�̕`�揈���֐�.
	m_pCStageBase[STAGE_TYPE_NUM]->Render();

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
	const int STAGE_TYPE_NUM = m_pCStageBase.size() - 1;

	if (m_pCStageBase[STAGE_TYPE_NUM]->GetTutorialFlag() & m_pCStageBase[STAGE_TYPE_NUM]->TUTORIAL_START) {
		m_pCStageBase.emplace_back(new CMainStage(0, CStageBase::enStageType::Tutorial, m_enBeforeEndingType));
		m_StageType = static_cast<int>(CStageBase::enStageType::Tutorial);
		m_bOldTutorialFlag = m_pCStageBase[STAGE_TYPE_NUM]->TUTORIAL_START;
		return;
	}

	if (m_pCStageBase[STAGE_TYPE_NUM]->GetTutorialFlag() & m_pCStageBase[STAGE_TYPE_NUM]->TUTORIAL_FINISH) {
		if (m_pCStageBase.size() >= 2) {
			m_pCStageBase.pop_back();
			m_bOldTutorialFlag = m_pCStageBase[0]->TUTORIAL_FINISH;
			m_StageType = static_cast<int>(CStageBase::enStageType::GhostSpeakStage);
			m_pCStageBase[0]->SetTutorialFlag(m_pCStageBase[0]->TUTORIAL_FINISH);
			return;
		}
	}
	if (m_StageType == static_cast<int>(CStageBase::enStageType::Tutorial)) {
		return;
	}

	//3�X�e�[�W�ȏ�̏ꍇ�͏I������.
	if (m_StageNum >= 3) {
		m_FinishFlag = FINISH_NEXT_ENDING;
		return;
	}

	//�X�e�[�W�̎�ޕύX.
	switch (static_cast<CStageBase::enStageType>(m_StageType)) {
	case CStageBase::enStageType::GhostSpeakStage:
		//���̃X�e�[�W��.
		m_AllEndingType = 0;
		m_pCStageBase[STAGE_TYPE_NUM].reset(new CMainStage(m_AllEndingType, CStageBase::enStageType::GhostSpeakStage , m_enBeforeEndingType));
		m_bOldTutorialFlag = 0;
		break;
	case CStageBase::enStageType::MainStage:
		m_enBeforeEndingType = m_pCStageBase[STAGE_TYPE_NUM]->GetBeforeStageEndingType();
		//�Q�[���G���f�B���O���Z.
		m_AllEndingType += static_cast<int>(m_enBeforeEndingType);
		m_StageNum++;
		m_pCStageBase[STAGE_TYPE_NUM].reset(new CGhostSpeakStage(m_StageNum, m_enBeforeEndingType));
		break;
	}

	m_StageType++;
	if (m_StageType >= static_cast<int>(CStageBase::enStageType::NormalStageMax)) {
		m_StageType = static_cast<int>(CStageBase::enStageType::Start);
	}
}