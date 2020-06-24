#include "CGhostSpeakStage.h"
#include "..\..\Camera\CameraGhostSpeakStage\CCameraGhostSpeakStage.h"

CGhostSpeakStage::CGhostSpeakStage()
	: CGhostSpeakStage	(0, enBeforeStageEndigneType::Nothing)
{
}

CGhostSpeakStage::CGhostSpeakStage(int stageNum, CGhostSpeakStage::enBeforeStageEndigneType enBeforeStageEndingType)	
	: m_pCFontResource		(nullptr)
	, m_pCFloor				(nullptr)
	, m_pCBigGhost			(nullptr)
	, m_pCSpeakBigGhost		(nullptr)
	, m_pCBackstageLight	(nullptr)
	, m_bOldSleepBigGhost	(true)
{
	m_StageNum = stageNum;
	m_enBeforeStageEndingType = enBeforeStageEndingType;
	//�����������֐�.
	Init();
}

CGhostSpeakStage::~CGhostSpeakStage()
{
	//��������֐�.
	Release();
}

//=========================================.
//		�X�V�����֐�.
//=========================================.
void CGhostSpeakStage::UpDate(const bool& ControlFlag)
{
	//�傫���������Q��t���O.
	const bool SLEEP_BIGGHOST_FLAG = m_pCBigGhost->GetSleepFlag();


	if (GetAsyncKeyState('Q') & 0x8000) {
		if (m_TutorialFlag != TUTORIAL_FINISH) {
			m_TutorialFlag = TUTORIAL_START;
			return;
		}
	}

	if (SLEEP_BIGGHOST_FLAG == false) {
		SettingEmotion();
	}

	//�傫���������X�V�����֐�.
	m_pCBigGhost->Update();

	if (SLEEP_BIGGHOST_FLAG == true) {
		if (m_bOldSleepBigGhost != SLEEP_BIGGHOST_FLAG) {
			//�J�����ړ��J�n.
			m_pCCamera->SetMoveFlag(m_pCCamera->MOVE_FLAG);
		}
		m_bOldSleepBigGhost = SLEEP_BIGGHOST_FLAG;
	
		m_pCCamera->Update();

		if (m_pCCamera->GetMoveFlag() & m_pCCamera->CHANGE_STAGE_FLAG) {
			if (m_pCSpeakBigGhost->GetFinishFlag() & m_pCSpeakBigGhost->FINISH_NEXT_GAME) {
				//�Q�[�����C���ɐi��.
				m_bChangeStageFlag = true;
				return;
			}
			//�G���f�B���O�ɐi��.
			m_FinishFlag = FINISH_NEXT_ENDING;
		}

		return;
	}

	if (ControlFlag == false) {
		return;
	}

	//���쏈���֐�.
	Control();

	if (SLEEP_BIGGHOST_FLAG == true) {

		return;
	}
	if (m_TutorialFlag & TUTORIAL_START) {
		return;
	}

	//�傫����������b�X�V�����N���X.
	m_pCSpeakBigGhost->Update();

	//�����p.
	m_bOldSleepBigGhost = SLEEP_BIGGHOST_FLAG;

	const bool OldTutorialFlag = m_pCSpeakBigGhost->GetTutorialFlag();
	if (m_TutorialFlag != TUTORIAL_FINISH) {
		if (OldTutorialFlag == true) {
			m_TutorialFlag = TUTORIAL_START;
		}
		return;
	}
}

//=========================================.
//		�`�揈���֐�.
//=========================================.
void CGhostSpeakStage::Render()
{
	//���C�g���.
	const LIGHT m_Light = m_pCBackstageLight->GetLight();

	//�J�������W���.
	const D3DXVECTOR3 m_vCameraPos = m_pCCamera->GetPos();

	//���̕`��.
	m_pCFloor->SetCameraPos(m_vCameraPos);
	m_pCFloor->RenderInitSetting(m_mView, m_mProj, m_Light);
	m_pCFloor->SetPos(D3DXVECTOR3(0.0f, -6.0f, 0.0f));
	m_pCFloor->Render();

	//�傫���������`��.
	m_pCBigGhost->SetPauseFlag(m_bPauseFlag);
	m_pCBigGhost->SetCameraPos(m_vCameraPos);
	m_pCBigGhost->RenderInitSetting(m_mView, m_mProj, m_Light);
	m_pCBigGhost->Render();

	if (m_pCBigGhost->GetSleepFlag() == true) {
		return;
	}

	if (m_TutorialFlag & TUTORIAL_START) {
		return;
	}

	//�傫����������b�N���X.
	m_pCSpeakBigGhost->RenderInit(m_mView, m_mProj, m_vCameraPos);
	m_pCSpeakBigGhost->Render();

}

//=========================================.
//		�����������֐�.
//=========================================.
void CGhostSpeakStage::Init()
{

	//��.
	m_pCFloor.reset(new CFloor());
	m_pCFloor->SetScale(0.5f);

	//�傫��������.
	m_pCBigGhost.reset(new CBigGhost());

	//�傫����������b�N���X.
	m_pCSpeakBigGhost.reset(new CSpeakBigGhost(m_StageNum,static_cast<int>(m_enBeforeStageEndingType)));

	//���䗠�̃��C�g�N���X.
	m_pCBackstageLight.reset(new CBackstageLight());

	//�J�����N���X.
	m_pCCamera.reset(new CCameraGhostSpeakStage());

}

//=========================================.
//		��������֐�.
//=========================================.
void CGhostSpeakStage::Release()
{
}

//=========================================.
//		���쏈���֐�.
//=========================================.
void CGhostSpeakStage::Control()
{

}

//===========================================.
//		����ݒ菈���֐�.
//===========================================.
void CGhostSpeakStage::SettingEmotion()
{
	//�I���t���O.
	const unsigned int FINISH_FLAG = m_pCSpeakBigGhost->FINISH_NEXT_GAME | m_pCSpeakBigGhost->FINISH_NEXT_TITLE;
	if (m_pCSpeakBigGhost->GetFinishFlag() & FINISH_FLAG) {
		//����.
		m_pCBigGhost->SetEmotionNum(static_cast<int>(CBigGhost::enEmotionType::Sleep));
		return;
	}

	//����ԍ��擾����.
	m_pCBigGhost->SetEmotionNum(m_pCSpeakBigGhost->GetEmotionNum());
}