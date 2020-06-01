#include "CGhostSpeakStage.h"

CGhostSpeakStage::CGhostSpeakStage()
	: CGhostSpeakStage	(0, enBeforeStageEndigneType::Nothing)
{
}

CGhostSpeakStage::CGhostSpeakStage(int stageNum, CGhostSpeakStage::enBeforeStageEndigneType enBeforeStageEndingType)	
	: m_pCFontResource		(nullptr)
	, changestr				()
	, m_pCFloor				(nullptr)
	, m_pCBigGhost			(nullptr)
	, m_pCSpeakBigGhost		(nullptr)
	, m_pCBackstageLight	(nullptr)
	, m_MoveCameraDirection	(GET_CLOSER_CAMERA_DIRECT)
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
	if (GetAsyncKeyState('Q') & 0x8000) {
		//const bool OldTutorialFlag = m_pCSpeakBigGhost->GetTutorialFlag();
		if (m_TutorialFlag != TUTORIAL_FINISH) {
			//if (OldTutorialFlag == true) {
				m_TutorialFlag = TUTORIAL_START;
			//}
			return;
		}
	}

	if (m_pCBigGhost->GetSleepFlag() == false) {
		SettingEmotion();
	}

	//�傫���������X�V�����֐�.
	m_pCBigGhost->Update();

	if (m_pCBigGhost->GetSleepFlag() == true) {
		//�J�����ړ������֐�.
		CameraMove();
		return;
	}

	if (ControlFlag == false) {
		return;
	}

	//���쏈���֐�.
	Control();

	if (m_pCBigGhost->GetSleepFlag() == true) {
		return;
	}
	if (m_TutorialFlag & TUTORIAL_START) {
		return;
	}

	//�傫����������b�X�V�����N���X.
	m_pCSpeakBigGhost->Update();

	m_MoveCameraDirection = FAR_AWAY_CAMERA_DIRECT;

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

	//���̕`��.
	m_pCFloor->SetCameraPos(m_Camera.vPos);
	m_pCFloor->RenderInitSetting(m_mView, m_mProj, m_Light);
	m_pCFloor->SetPos(D3DXVECTOR3(0.0f, -6.0f, 0.0f));
	m_pCFloor->Render();

	//�傫���������`��.
	m_pCBigGhost->SetCameraPos(m_Camera.vPos);
	m_pCBigGhost->RenderInitSetting(m_mView, m_mProj, m_Light);
	m_pCBigGhost->Render();

	if (m_pCBigGhost->GetSleepFlag() == true) {
		return;
	}

	if (m_TutorialFlag & TUTORIAL_START) {
		return;
	}

	//�傫����������b�N���X.
	m_pCSpeakBigGhost->RenderInit(m_mView, m_mProj, m_Camera.vPos);
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

	m_Camera.vPos = D3DXVECTOR3(5.0f, 2.5f, -3.5f);
	m_Camera.vLook = D3DXVECTOR3(5.0f, 2.5f, 5.0f);
}

//=========================================.
//		��������֐�.
//=========================================.
void CGhostSpeakStage::Release()
{
	//m_pCFontResource->Destroy();
}

//=========================================.
//		���쏈���֐�.
//=========================================.
void CGhostSpeakStage::Control()
{

}

//===========================================.
//		�J�����ړ������֐�.
//===========================================.
void CGhostSpeakStage::CameraMove()
{

	//�J�����̈ړ�����.
	const float CAMERA_POS_LENGTH = D3DXVec3Length(&CAMERA_POS_DISTANCE);			//�x�N�g���̒���.
	const D3DXVECTOR3	CAMERA_POS_UNIT = CAMERA_POS_DISTANCE / CAMERA_POS_LENGTH;	//�P�ʃx�N�g��.
	m_Camera.vPos += CAMER_MOVE_SPEED * CAMERA_POS_UNIT * static_cast<float>(m_MoveCameraDirection);

	//�J�����̒����_�ړ�����.
	const float CAMERA_LOOK_LENGTH = D3DXVec3Length(&CAMERA_LOOK_DISTANCE);				//�x�N�g���̒���.
	const D3DXVECTOR3	CAMERA_LOOK_UNIT = CAMERA_LOOK_DISTANCE / CAMERA_LOOK_LENGTH;	//�P�ʃx�N�g��.
	const float	CAMERA_LENGTH_RATIO = CAMERA_LOOK_LENGTH / CAMERA_POS_LENGTH;			//�����̔䗦.
	m_Camera.vLook += CAMER_MOVE_SPEED * CAMERA_LOOK_UNIT * static_cast<float>(m_MoveCameraDirection) * CAMERA_LENGTH_RATIO;

	//�J�����̐ڋ߂���������.
	if (m_MoveCameraDirection == GET_CLOSER_CAMERA_DIRECT) {
		if (m_Camera.vPos.x > SPEAK_START_POS.x) {
			m_Camera.vPos = SPEAK_START_POS;
		}

		if (m_Camera.vLook.x > SPEAK_START_LOOK.x) {
			m_Camera.vLook = SPEAK_START_LOOK;
		}
		return;
	}

	//�J���������̂��������.
	if (m_Camera.vPos.x < INIT_CAMERA_POS.x) {
		m_Camera.vPos = INIT_CAMERA_POS;
		if (m_pCSpeakBigGhost->GetFinishFlag() & m_pCSpeakBigGhost->FINISH_NEXT_GAME) {
			//�Q�[�����C���ɐi��.
			m_bChangeStageFlag = true;
			return;
		}
		//�G���f�B���O�ɐi��.
		m_FinishFlag = FINISH_NEXT_ENDING;
	}

	if (m_Camera.vLook.x < INIT_CAMERA_LOOK.x) {
		m_Camera.vLook = INIT_CAMERA_LOOK;
	}
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