#include "CMainStage.h"
#include <random>
#include "..\..\Camera\CameraGameMainStage\CCameraGameMainStage.h"

CMainStage::CMainStage()
	: CMainStage	(0, enStageType::Start ,enBeforeStageEndigneType::Nothing)
{

}

CMainStage::CMainStage(int stageNum, enStageType enStage, enBeforeStageEndigneType enType)
	: m_pCStaticObjectManager	(nullptr)
	, m_pCMoveObjectManager		(nullptr)
	, m_pCWorkGhost				()
	, m_pCPeopleManager			(nullptr)
	, m_pCStageMap				(nullptr)
	, m_pCMapGhostCursor		(nullptr)
	, m_SelectNum				()
	, m_ObjectSelectFlag		(0)
	, m_pCGameGhostCursor		(nullptr)
	, m_pCClosedTime			(nullptr)
	, m_pCSurpriseGage			()
	, m_pCFrontstageLight		(nullptr)
	, m_enStageType				(enStage)
	, m_ExplainFlag				(0)
	, m_bDispTextFlag			(true)
	, m_pCSpeakWorkGhost		(nullptr)
	, m_vSelectGhostPos			(0.0f, 0.0f, 0.0f)
	, m_pCDescriptionUIManager	(nullptr)
	//, m_bTutorialCameraMove		(false)
	//, m_stOldCamera				()
{
	m_StageNum = stageNum;
	m_enBeforeStageEndingType = enType;
	//�����������֐�.
	Init();
}

CMainStage::~CMainStage()
{
	//��������֐�.
	Release();
}

//===================================.
//		�X�V�����֐�.
//===================================.
void CMainStage::UpDate(const bool& ControlFlag)
{
	if (m_ObjectSelectFlag & GIMMICK_SELECTION_FLAG) {
		m_pCCamera->SetTargetPos(m_pCMoveObjectManager->GetGimmickPos());
	}
	else {
		m_pCCamera->SetTargetPos(m_pCWorkGhost[m_SelectNum[GHOST_NUM]]->GetPos());
	}
	m_pCCamera->Update();
	const D3DXVECTOR3 m_vCameraPos = m_pCCamera->GetPos();

	//�\���䃉�C�g�N���X�̍X�V�����֐�.
	m_pCFrontstageLight->SetCameraPos(m_vCameraPos);
	//m_pCFrontstageLight->SetCameraPos(m_Camera.vPos);
	m_pCFrontstageLight->Update();

	//�ÓI�I�u�W�F�N�g�X�V�����֐�.
	m_pCStaticObjectManager->SetCameraPos(m_vCameraPos);
	//m_pCStaticObjectManager->SetCameraPos(m_Camera.vPos);
	m_pCStaticObjectManager->Updata();

	//������.
	std::vector<D3DXVECTOR3> m_vGhostPos(m_pCWorkGhost.size());							//���������W.
	std::vector<D3DXVECTOR3> m_vGimmickPos = m_pCMoveObjectManager->GetAllGimmickPos();	//�M�~�b�N���W.
	for (unsigned int ghost = 0; ghost < m_pCWorkGhost.size(); ghost++) {

		//�X�e�[�W�S�̂̋����擾.
		m_pCWorkGhost[ghost]->SetStageDistanceMax(m_pCStaticObjectManager->GetStageDistanceMax());

		//�M�~�b�N�Ɛl�̍��W�擾.
		m_pCWorkGhost[ghost]->SetSurprisePosInfo(m_vGimmickPos, m_pCPeopleManager->GetHumanPos());

		if (m_enStageType == enStageType::Tutorial) {
			if (m_ExplainFlag != 0) {
				//�`���[�g���A���t���O.
				m_pCWorkGhost[ghost]->SetTutorialFlag(true);

				//�I������t���O�ݒ�.
				if (m_pCDescriptionUIManager->GetAdvanceCommentFlag() == false) {
					m_pCWorkGhost[ghost]->SetDecideSelectFlag(true);
				}
				else {
					m_pCWorkGhost[ghost]->SetDecideSelectFlag(false);
				}
			}
			else {
				m_pCWorkGhost[ghost]->SetTutorialFlag(false);
				m_pCWorkGhost[ghost]->SetDecideSelectFlag(true);
			}
		}


		//�������X�V�����֐�.
		m_pCWorkGhost[ghost]->Update();

		//�`���[�g���A�����R�����g��i�߂鏈��.
		if (m_pCDescriptionUIManager != nullptr) {
			if (m_pCWorkGhost[ghost]->GetTutorialAddCommentFlag() == true) {
				m_pCDescriptionUIManager->SetAdvanceComment();
			}
		}

		//�������̍��W�擾.
		m_vGhostPos[ghost] = m_pCWorkGhost[ghost]->GetPos();
		D3DXVECTOR3 vTargetPos;
		std::unique_ptr<CMainStageWorkGhostBase> pTmp;
		//�������̗v�f���ϊ�����.
		if (ghost < m_pCWorkGhost.size() - 1) {
			//������E.
			vTargetPos = m_pCWorkGhost[ghost + 1]->GetPos();
			if (m_vGhostPos[ghost].x > vTargetPos.x) {
				//�������̕ύX.
				pTmp.swap(m_pCWorkGhost[ghost]);
				m_pCWorkGhost[ghost].swap(m_pCWorkGhost[ghost + 1]);
				m_pCWorkGhost[ghost + 1].swap(pTmp);

				//�J�[�\�������鎞�͔ԍ����ړ�������.
				if (m_SelectNum[GHOST_NUM] == ghost) {
					m_SelectNum[GHOST_NUM] = ghost + 1;
				}
			}
		}
		if (ghost > 0) {
			//�E���獶.
			vTargetPos = m_pCWorkGhost[ghost - 1]->GetPos();
			if (m_vGhostPos[ghost].x < vTargetPos.x) {
				pTmp.swap(m_pCWorkGhost[ghost]);
				m_pCWorkGhost[ghost].swap(m_pCWorkGhost[ghost - 1]);
				m_pCWorkGhost[ghost - 1].swap(pTmp);

				if (m_SelectNum[GHOST_NUM] == ghost) {
					m_SelectNum[GHOST_NUM] = ghost - 1;
				}
			}
		}

		//�g�p���Ă���M�~�b�N�ݒ�.
		if (m_pCWorkGhost[ghost]->GetUseGimmickNum() >= 0) {
			m_pCMoveObjectManager->SetUsedGimmickFlag(m_pCWorkGhost[ghost]->GetUseGimmickNum(), true);
		}

		//�����Ă���l�ԍ��擾.
		m_pCPeopleManager->SetNowHumanSurprise(m_pCWorkGhost[ghost]->GetNearHumanNum());

		//�ǉ��|�C���g��.
		m_pCSurpriseGage->AddSurprisePoint(m_pCPeopleManager->GetAddSurprisePoint());

		//�M�~�b�N�̈ړ��t���O�ݒ�.
		int UseGimmickNum = m_pCWorkGhost[ghost]->GetUseGimmickNum();

		if (UseGimmickNum < 0) {
			continue;
		}

		//�I�u�W�F�N�g�����鏈��.
		if (m_pCWorkGhost[ghost]->GetUpDownFlag() & m_pCWorkGhost[ghost]->DOWN_FLAG) {
			m_pCMoveObjectManager->SetGimmickMoveFlag(UseGimmickNum, m_pCMoveObjectManager->DOWN_FLAG);
			continue;
		}

		//�I�u�W�F�N�g�グ�鏈��.
		if (m_pCWorkGhost[ghost]->GetUpDownFlag() & m_pCWorkGhost[ghost]->UP_FLAG) {
			m_pCMoveObjectManager->SetGimmickMoveFlag(UseGimmickNum, m_pCMoveObjectManager->UP_FLAG);
		}
	}

	//���I�I�u�W�F�N�g�̍X�V�����֐�.
	m_pCMoveObjectManager->SetCameraPos(m_vCameraPos);
	//m_pCMoveObjectManager->SetCameraPos(m_Camera.vPos);
	m_pCMoveObjectManager->SetSelectionNum(m_SelectNum[GIMMICK_NUM]);
	m_pCMoveObjectManager->SetGhostPos(m_vGhostPos);
	m_pCMoveObjectManager->UpDate();

	//�������I���t���O.
	if (m_ObjectSelectFlag & GHOST_ACT_SELECT_FLAG) {
		if (m_pCWorkGhost[m_SelectNum[GHOST_NUM]]->GetSelectFlag() == false) {
			m_ObjectSelectFlag = GHOST_SELECTION_FLAG;
		}
	}

	//�M�~�b�N�I���t���O.
	if (m_pCWorkGhost[m_SelectNum[GHOST_NUM]]->GetChangeGimmickSelect() == true) {
		m_ObjectSelectFlag = GIMMICK_SELECTION_FLAG;

		//�M�~�b�N�J�[�\���\���t���O�ݒ�.
		m_pCMoveObjectManager->SetGimmickCurosrDispFlag(true);
	}

	//�}�b�v��̂������J�[�\���X�V�����֐�.
	m_pCMapGhostCursor->SetCharaPos(m_pCWorkGhost[m_SelectNum[GHOST_NUM]]->GetPos());
	m_pCMapGhostCursor->UpDate();
	m_pCWorkGhost[m_SelectNum[GHOST_NUM]]->SetGhostSelectIcon(true);

	//�������x�e�擾����.
	bool GhostRestFlag = false;	//�������x�e�t���O.
	if (m_pCWorkGhost[m_SelectNum[GHOST_NUM]]->GetMoveFlag() & m_pCWorkGhost[m_SelectNum[GHOST_NUM]]->REST_FLAG) {
		GhostRestFlag = true;
	}
	m_pCGameGhostCursor->SetRestFlag(GhostRestFlag);
	m_pCGameGhostCursor->SetCharacterPos(m_pCWorkGhost[m_SelectNum[GHOST_NUM]]->GetPos());
	//�Q�[�����ł̂������̃J�[�\���X�V�����֐�.
	m_pCGameGhostCursor->UpDate();

	//�J�����ړ�.
	CameraMove();


	//�����Q�[�W�X�V�����֐�.
	m_pCSurpriseGage->Update();

	//�`���[�g���A���܂ł̏���(�����ł������ƃM�~�b�N�̎��͗�O�̏������s��Ȃ���΂Ȃ�Ȃ�).
	if (m_enStageType == enStageType::Tutorial && (m_ExplainFlag & EXPLAINING_FLAG)) {

		//�t�F�[�h���͗�O����.
		if (ControlFlag == false) {
			return;

		}

		//����UI�Ǘ��N���X.
		m_pCDescriptionUIManager->SetCenterPos(m_pCSurpriseGage->GetUIPos(), m_pCClosedTime->GetUIPos());
		m_pCDescriptionUIManager->Update();

		if (GetAsyncKeyState('Q') & 0x8000) {
			//�����I���Q�[���𓮂����t���O.
			m_ExplainFlag = 0;
		}
		
		if (m_pCDescriptionUIManager->GetDescriptionEndFlag() == true) {
			m_ExplainFlag = 0;
			//�e�L�X�g�`��I��.
			m_bDispTextFlag = false;
			//m_bTutorialCameraMove = 0;
		}
	}

	if (m_pCDescriptionUIManager != nullptr) {
		//�R�����g�i�߂�Ƃ��͉��܂ŏ������Ȃ�.
		if (m_pCDescriptionUIManager->GetAdvanceCommentFlag() == true) {
			const unsigned int DESCRIPTION_LAST_FLAG = SeePeople | DescriptionEnd;
			if (!(m_pCDescriptionUIManager->GetStartLatestFlag() & DESCRIPTION_LAST_FLAG)) {
				return;
			}
		}
	}

	//���쏈���֐�.
	if (ControlFlag == true) {
		Control();
		//��������O����.
		if (m_ExplainFlag & EXPLAINING_FLAG ){
			m_pCPeopleManager->SetTutorialFlag(true);

			if(!(m_pCDescriptionUIManager->GetStartLatestFlag() & SeePeople)) {
				//if (m_bTutorialCameraMove & CAMERA_MOVE_START_FLAG) {
				//	m_bTutorialCameraMove = CAMERA_MOVE_RETURN_FLAG;
				//}
				if (m_pCCamera->GetMoveFlag() & m_pCCamera->PEOPLE_LOOK_FLAG) {
					m_pCCamera->SetMoveFlag(m_pCCamera->GHOST_LOOK_FLAG);
				}
				return;
			}
			if (m_pCDescriptionUIManager->GetStartLatestFlag() & SeePeople) {
				//�J�����ړ��t���O.
				//m_bTutorialCameraMove = CAMERA_MOVE_START_FLAG;
				m_pCCamera->SetMoveFlag(m_pCCamera->PEOPLE_LOOK_FLAG);
				m_pCCamera->AcquisitionDifference();
				//m_stOldCamera.vPos = m_Camera.vPos;
				//m_stOldCamera.vLook = m_Camera.vLook;

			}
		}

	}

	

	//�l�̍X�V�����֐�.
	m_pCPeopleManager->Update();


	//�X�܂ł̎��ԍX�V�����֐�.
	m_pCClosedTime->Update();
	m_pCClosedTime->GiveBornusTime(m_pCSurpriseGage->GetBornusGetFlag());

	//if (m_pCSurpriseGage->GetSurprisePointMax() == true) {
	//	m_enBeforeStageEndingType = enBeforeStageEndigneType::Great;
	//}
	m_enBeforeStageEndingType = Evalute();

	//�I������.
	if (m_pCClosedTime->GetClosedFlag() == true) {
		if (m_enStageType == enStageType::Tutorial) {
			m_TutorialFlag = TUTORIAL_FINISH;
		}
		m_bChangeStageFlag = true;
	}
}

//===================================.
//		�`�揈���֐�.
//===================================.
void CMainStage::Render()
{
	{
	//	static bool	m_ControlFlag = true;
	//	if (m_ControlFlag == true) {
	//		if (GetAsyncKeyState('1') & 0x8000) {
	//			m_stLight.fIntensity -= 0.1f;
	//		}

	//		if (GetAsyncKeyState('2') & 0x8000) {
	//			m_stLight.fIntensity += 0.1f;
	//		}
	//	}
	//	else {
	//		if (GetAsyncKeyState('1') & 0x8000) {
	//			m_stLight.m_fLightWidth -= 0.1f;
	//		}

	//		if (GetAsyncKeyState('2') & 0x8000) {
	//			m_stLight.m_fLightWidth += 0.1f;
	//		}

	//	}

	//	if (GetAsyncKeyState(VK_F1) & 0x8000) {
	//		if (m_ControlFlag == true) {
	//			m_ControlFlag = false;
	//		}
	//		else {
	//			m_ControlFlag = true;
	//		}
	//	}
	}

	//���C�g���.
	const LIGHT m_Light = m_pCFrontstageLight->GetLight();
	//�J�������W.
	const D3DXVECTOR3 m_vCameraPos = m_pCCamera->GetPos();

	//�X�e�[�W�}�b�v�̕`��.
	m_pCStageMap->Render();

	//�}�b�v��̂������J�[�\���`�揈���֐�.
	m_pCMapGhostCursor->Render();


	//�������̕`��.
	for (unsigned int ghost = 0; ghost < m_pCWorkGhost.size(); ghost++) {
		//�������{�̂̕`�揈���֐�.
		m_pCWorkGhost[ghost]->SetCameraPos(m_vCameraPos);
		//m_pCWorkGhost[ghost]->SetCameraPos(m_Camera.vPos);
		m_pCWorkGhost[ghost]->RenderInitSetting(m_mView, m_mProj, m_Light);
		m_pCWorkGhost[ghost]->Render();
	}



	//�����I�u�W�F�N�g�X�C�b�`�̕`��.
	m_pCMoveObjectManager->RenderSwitch(m_mView, m_mProj, m_Light);
	//�ÓI�I�u�W�F�N�g�̕`��.
	m_pCStaticObjectManager->Render(m_mView, m_mProj, m_vCameraPos, m_Light);
	//m_pCStaticObjectManager->Render(m_mView, m_mProj, m_Camera.vPos, m_Light);
	//�����I�u�W�F�N�g�`�揈��.
	m_pCMoveObjectManager->Render(m_mView, m_mProj, m_Light);

	//�������̗̓A�C�R���`�揈���֐�.
	for (unsigned int ghost = 0; ghost < m_pCWorkGhost.size(); ghost++) {
		m_pCWorkGhost[ghost]->StrengthIconRender();
	}

	//�l�̕`�揈���֐�.
	m_pCPeopleManager->Render(m_mView, m_mProj, m_vCameraPos, m_Light);
	//m_pCPeopleManager->Render(m_mView, m_mProj, m_Camera.vPos, m_Light);

	//�����I�u�W�F�N�g�̃G�t�F�N�g�`��.
	m_pCMoveObjectManager->EffectRender();
	
	//�Q�[�����ł̂������̃J�[�\���`�揈���֐�.
	m_pCGameGhostCursor->RenderSetting(m_mView, m_mProj, m_vCameraPos);
	//m_pCGameGhostCursor->RenderSetting(m_mView, m_mProj, m_Camera.vPos);
	m_pCGameGhostCursor->Render();

	//�������̑I��`�揈���֐�.
	if (m_ObjectSelectFlag & GHOST_ACT_SELECT_FLAG) {
		m_pCWorkGhost[m_SelectNum[GHOST_NUM]]->SelectRender();
	}

	//�X�܂ł̎��ԕ`�揈���֐�.
	m_pCClosedTime->Render();

	//�����Q�[�W�`�揈���֐�.
	m_pCSurpriseGage->Render();

	//�e�L�X�g�\��.
	if (m_bDispTextFlag == false) {
		return;
	}


	//������������b�N���X.
	if (m_pCSpeakWorkGhost != nullptr) {
		//�������̑I���Ɋ֌W����S�Ẵt���O.
		const unsigned int RELATED_TO_GHOST_ALL_FLAG = SELECT_GHOST_FLAG | GHOST_ACT_SELECT_FLAG;
		if (m_vCameraPos.x == m_vSelectGhostPos.x ||
		//if (m_Camera.vPos.x == m_vSelectGhostPos.x ||
			m_ObjectSelectFlag & RELATED_TO_GHOST_ALL_FLAG) {
			m_pCSpeakWorkGhost->Render();
		}
	}

	//����UI�Ǘ��N���X.
	if (m_pCDescriptionUIManager != nullptr) {
		m_pCDescriptionUIManager->Render();
	}
}

//===================================.
//		�����������֐�.
//===================================.
void CMainStage::Init()
{
	//�S�̓I�Ƀt�@�C���ԍ�.
	int FileNum = 0;

	//�I�u�W�F�N�g�t�@�C���ԍ�.
	int ObjFileNum = static_cast<int>(CFileResource::enStageType::OneDay) + m_StageNum;

	//�ǂݍ��݃N���X�A�h���X�擾.
	CFileResource* m_pCFileResource = CFileResource::GetResourceInstance();

	//�ÓI�I�u�W�F�N�g�C���X�^���X��.
	std::random_device rnda;
	std::mt19937 mta(rnda());
	std::uniform_int_distribution<> IntervalRand4(0, 2);
	int m_columna = IntervalRand4(mta);
	
	m_pCStaticObjectManager.reset(new CStaticObjectManager(ObjFileNum, m_columna));

	//�X�e�[�W�̒����ő吔.
	float m_fStageDistanceMax = m_pCStaticObjectManager->GetStageDistanceMax();

	//�������ݒ�.
	std::random_device rnd;
	std::mt19937 mt(rnd());
	std::uniform_int_distribution<> IntervalRand(0, 2);
	int m_column = IntervalRand(mt);

	int GhostFilenum = static_cast<int>(CFileResource::enStageType::GhostPos_OneDay) * 3;
	for (int stage = 0; stage < m_pCFileResource->GetStageMax(GhostFilenum); stage++) {
		switch (m_pCFileResource->GetStageNum(GhostFilenum, m_column, stage) - 1) {
		case 0:
			m_pCWorkGhost.push_back(nullptr);
			m_pCWorkGhost[m_pCWorkGhost.size() - 1].reset(new CMainStageDispGhost());
			m_pCWorkGhost[m_pCWorkGhost.size() - 1]->SetPos(D3DXVECTOR3(stage * m_pCStaticObjectManager->OBJECT_WIDTH, 0.0f, 3.5f));
			m_pCWorkGhost[m_pCWorkGhost.size() - 1]->SetInitMovePos();
			break;
		case 1:
			m_pCWorkGhost.push_back(nullptr);
			m_pCWorkGhost[m_pCWorkGhost.size() - 1].reset(new CMainStageSwitchGhost());
			m_pCWorkGhost[m_pCWorkGhost.size() - 1]->SetPos(D3DXVECTOR3(stage * m_pCStaticObjectManager->OBJECT_WIDTH, 3.5f, 3.5f));
			m_pCWorkGhost[m_pCWorkGhost.size() - 1]->SetInitMovePos();
			break;
		}
	}

	//���I�I�u�W�F�N�g�C���X�^���X��.
	m_pCMoveObjectManager.reset(new CMoveObjectManager(ObjFileNum, m_column));
	m_pCMoveObjectManager->SetGhostElementCount(m_pCWorkGhost.size());
	
	//�l�Ǘ��N���X�ݒ�.
	m_pCPeopleManager.reset(new CPeopleManager());
	m_pCPeopleManager->Init(static_cast<int>(CFileResource::enStageType::PeopleOder) /*+ FileNum*/ * 3, 12, m_pCFileResource->GetStageMax(GhostFilenum) * m_pCMoveObjectManager->OBJECT_WIDTH);
	m_pCPeopleManager->SetStageDistanceMax(m_fStageDistanceMax);

	//====UI�n�̃C���X�^���X��====.
	//�X�e�[�W.
	m_pCStageMap.reset(new CStageMap());
	//�}�b�v��̂������̃J�[�\��.
	m_pCMapGhostCursor.reset(new CMapGhostCursor());
	m_pCMapGhostCursor->SetStageMax(m_fStageDistanceMax);
	//�Q�[�����������̃J�[�\��.
	m_pCGameGhostCursor.reset(new CGameGhostCursor());
	//�X�܂ł̎���.
	//�X�e�[�W���Ƃɐ������Ԃ�L�΂�.
	int TimeUpMax = START_TIME_UP_MAX + (ADD_TIME_UP * m_StageNum);
	//Good,Great���ƃ{�[�i�X�Ő������Ԃ�ǉ�.
	if (m_enBeforeStageEndingType == enBeforeStageEndigneType::Great) {
		TimeUpMax += BENEFITS_PREVIOS_RESULT;
	}
	//�`���[�g���A���͕�.
	if (m_enStageType == enStageType::Tutorial) {
		TimeUpMax = 1;
	}

	//�O��̃X�e�[�W������.
	m_enBeforeStageEndingType = enBeforeStageEndigneType::Nothing;

	m_pCClosedTime.reset(new CClosedTime(TimeUpMax * TIME_DELIMITER));
	//�����Q�[�W.
	//�X�e�[�W���Ƃɋ����Q�[�W�̍ő吔�𑝂₷.
	int SurpriseGageMax = START_SUPRISE_GAGE_MAX + (SURPRISE_GAGE_ADD * m_StageNum);
	m_pCSurpriseGage.reset(new CSurpriseGage(SurpriseGageMax));

	//���߂͂������̑I������.
	m_ObjectSelectFlag = GHOST_SELECTION_FLAG;
	
	//�I��ԍ�������.
	m_SelectNum.resize(SLECTION_MAX);
	for (unsigned int select = 0; select < m_SelectNum.size(); select++) {
		m_SelectNum[select] = 0;
	}

	//�J���������ݒu.
	//m_Camera.vPos = CAMERA_START_POS;
	//m_Camera.vLook = CAMERA_START_LOOK;
	m_pCCamera.reset(new CCameraGameMainStage());

	//�\����̃��C�g�N���X�̃C���X�^���X��.
	m_pCFrontstageLight.reset(new CFrontstageLight());
	m_pCFrontstageLight->SettingAllLightPos(m_fStageDistanceMax);
	
	//�`���[�g���A���ł̏���������.
	if (m_enStageType != enStageType::Tutorial) {
		return;
	}
	m_TutorialFlag = TUTORIAL_START;
	m_ExplainFlag = EXPLAINING_FLAG;
	m_pCSpeakWorkGhost.reset(new CSpeakWorkGhost());
	m_pCDescriptionUIManager.reset(new CDescriptionUIManager());

}

//====================================.
//		��������֐�.
//====================================.
void CMainStage::Release()
{

}

//====================================.
//		���쏈���֐�.
//====================================.
void CMainStage::Control()
{
	//============================================.
	//�������I�������֐�.
	if (m_ObjectSelectFlag & GHOST_SELECTION_FLAG) {
		if (m_pCDescriptionUIManager != nullptr && m_ExplainFlag != 0) {
			if (!(m_pCDescriptionUIManager->GetTutorialFlag() & (SELECT_GHOST_FLAG | DECIDE_GHOST_FLAG))) {
				return;
			}
		}
		GhostSelect();
	}


	//============================================.
	//�M�~�b�N�I�������֐�.
	if (m_ObjectSelectFlag & GIMMICK_SELECTION_FLAG) {
		
		//�`���[�g���A�����������̐������Ă��Ȃ���ΏI��.
		if (m_ExplainFlag != 0) {
			if (m_enStageType == enStageType::Tutorial &&
				!(m_ExplainFlag & EXPLAINED_GHOST_FLAG)) {
				return;
			}
		}

		GimmickSelect();
	}

	//============================================.
	//���菈��.

	//�s�����N��������������.
	if (m_ObjectSelectFlag & GHOST_SELECTION_FLAG) {
		if (GetAsyncKeyState(VK_RETURN) & 0x0001) {
			//���������������Ă���Ƃ��̂�.
			if (m_pCWorkGhost[m_SelectNum[GHOST_NUM]]->GetMoveFlag() & 
				m_pCWorkGhost[m_SelectNum[GHOST_NUM]]->SURPRISE_FLAG) {

				if (m_pCDescriptionUIManager != nullptr && m_ExplainFlag != 0) {
					if (!(m_pCDescriptionUIManager->GetTutorialFlag() & DECIDE_GHOST_FLAG)) {
						return;
					}
					//�R�����g�i�߂�.
					m_pCDescriptionUIManager->SetAdvanceComment();
				}

				//�������I����s��.
				m_ObjectSelectFlag = GHOST_ACT_SELECT_FLAG;
				//�I���t���O.
				m_pCWorkGhost[m_SelectNum[GHOST_NUM]]->SetSelectFlag(true);

				if (m_ExplainFlag & EXPLAINING_FLAG) {
					//�������̐����I��.
					m_ExplainFlag |= EXPLAINED_GHOST_FLAG;
				}
			}
		}
	}

	//�ړ�����M�~�b�N����.
	if (m_ObjectSelectFlag & GIMMICK_SELECTION_FLAG) {
		if (GetAsyncKeyState(VK_BACK) & 0x0001) {
			m_pCWorkGhost[m_SelectNum[GHOST_NUM]]->SetSelectStop();
			//�������̑I���ɖ߂�.
			m_ObjectSelectFlag = GHOST_SELECTION_FLAG;
			//�M�~�b�N�I���t���O.
			m_pCWorkGhost[m_SelectNum[GHOST_NUM]]->SetChangeGimmickSelect(false);
			//�M�~�b�N�J�[�\����\���t���O�ݒ�.
			m_pCMoveObjectManager->SetGimmickCurosrDispFlag(false);
		}

		if (GetAsyncKeyState(VK_RETURN) & 0x0001) {
			if (m_pCMoveObjectManager->GetUsedGimmickFlag(m_SelectNum[GIMMICK_NUM]) == false) {
				//�������̎�ނƃM�~�b�N�̎�ނ������Ă���Ƃ��̂�.
				if (m_pCWorkGhost[m_SelectNum[GHOST_NUM]]->GetSurpriseObjectType() ==
					m_pCMoveObjectManager->GetSurpriseObjectType()) {
					if (m_pCWorkGhost[m_SelectNum[GHOST_NUM]]->GetUseGimmickNum() >= 0) {
						m_pCMoveObjectManager->SetUsedGimmickFlag(m_pCWorkGhost[m_SelectNum[GHOST_NUM]]->GetUseGimmickNum(), false);
					}

					//�`���[�g���A�����ɃR�����g��i�߂鏈��.
					if (m_pCDescriptionUIManager != nullptr && m_ExplainFlag != 0) {
						//��O����.
						if (!(m_pCDescriptionUIManager->GetTutorialFlag() & DECIDE_GIMMICK_FLAG)) {
							return;
						}
						m_pCDescriptionUIManager->SetAdvanceComment();
					}

					//�ړ��ړI�̃I�u�W�F�N�g���W�擾.
					m_pCWorkGhost[m_SelectNum[GHOST_NUM]]->SetObjectiveGimmickPos(m_pCMoveObjectManager->GetGimmickPos());
					//�������̑I���ɖ߂�.
					m_ObjectSelectFlag = GHOST_SELECTION_FLAG;
					//�M�~�b�N�I���t���O.
					m_pCWorkGhost[m_SelectNum[GHOST_NUM]]->SetChangeGimmickSelect(false);
					//�M�~�b�N�J�[�\����\���t���O�ݒ�.
					m_pCMoveObjectManager->SetGimmickCurosrDispFlag(false);

					if (m_ExplainFlag & EXPLAINING_FLAG) {
						//�M�~�b�N�����I��.
						m_ExplainFlag |= EXPLAINED_GIMMICK_FLAG;
					}
				}
			}
		}
	}


//#ifdef _DEBUG
//	if (GetAsyncKeyState(VK_UP) & 0x0001) {
//		m_ObjectSelectFlag = GHOST_SELECTION_FLAG;
//	}
//
//	if (GetAsyncKeyState(VK_DOWN) & 0x0001) {
//		m_ObjectSelectFlag = GIMMICK_SELECTION_FLAG;
//	}
//#endif	//#ifdef _DEBUG.
}

//========================================.
//		�������I�������֐�.
//========================================.
void CMainStage::GhostSelect()
{
	bool MoveSelectFlag = false;	//�������I���ړ��t���O.

	if (GetAsyncKeyState(VK_RIGHT) & 0x0001) {
		m_SelectNum[GHOST_NUM]++;

		if (m_SelectNum[GHOST_NUM] >= static_cast<int>(m_pCWorkGhost.size())) {
			m_SelectNum[GHOST_NUM] = m_pCWorkGhost.size() - 1;
		}
		MoveSelectFlag = true;
	}

	if (GetAsyncKeyState(VK_LEFT) & 0x0001) {
		m_SelectNum[GHOST_NUM]--;

		if (m_SelectNum[GHOST_NUM] < 0) {
			m_SelectNum[GHOST_NUM] = 0;
		}
		MoveSelectFlag = true;
	}

	if (MoveSelectFlag == true) {
		const int GHOST_TYPE_NUM = static_cast<int>(m_pCWorkGhost[m_SelectNum[GHOST_NUM]]->GetSurpriseObjectType());
		
		if (m_pCSpeakWorkGhost != nullptr) {
			//�������I���Ɋ֌W���邷�ׂẴt���O.
			const unsigned int RELATED_TO_GHOST_ALL_FLAG = GHOST_SELECTION_FLAG | GHOST_ACT_SELECT_FLAG;
			//�������I�����Ă��鎞�̂ݐݒ�\.
			if (m_ObjectSelectFlag & RELATED_TO_GHOST_ALL_FLAG) {
				m_pCSpeakWorkGhost->SetGhostTypeNum(GHOST_TYPE_NUM);
				m_vSelectGhostPos = m_pCWorkGhost[m_SelectNum[GHOST_NUM]]->GetPos();
			}
		}

		if (m_pCDescriptionUIManager != nullptr) {
			//�I���ړ��J�E���g�ǉ������֐�.
			m_pCDescriptionUIManager->SetAddSelectMoveCount();
		}
	}
}

//========================================.
//		�M�~�b�N�I�������֐�.
//========================================.
void CMainStage::GimmickSelect()
{
	bool MoveSelectFlag = false;		//�I���ړ��t���O.

	if (GetAsyncKeyState(VK_RIGHT) & 0x0001) {
		m_SelectNum[GIMMICK_NUM]++;
		if (m_SelectNum[GIMMICK_NUM] >= m_pCMoveObjectManager->GetGimmickIconMax()) {
			m_SelectNum[GIMMICK_NUM] = m_pCMoveObjectManager->GetGimmickIconMax() - 1;
		}
		MoveSelectFlag = true;
	}

	if (GetAsyncKeyState(VK_LEFT) & 0x0001) {
		m_SelectNum[GIMMICK_NUM]--;
		if (m_SelectNum[GIMMICK_NUM] < 0) {
			m_SelectNum[GIMMICK_NUM] = 0;
		}
		MoveSelectFlag = true;
	}

	if (MoveSelectFlag == true) {
		//�I���ړ��J�E���g�ǉ������֐�.
		if (m_pCDescriptionUIManager != nullptr) {
			m_pCDescriptionUIManager->SetAddSelectMoveCount();
		}
	}
}

//=======================================.
//		�������v�f���ϊ������֐�.
//=======================================.
template<typename T>
void CMainStage::GhostElementSort(T pClass, int array)
{
	std::unique_ptr<T> pTmp;
	pTmp.swap(pClass[array]);
	pClass[array].swap(pClass[array + 1]);
	pClass[array + 1].swap(pTmp);
}

//=======================================.
//		�J�����ړ������֐�.
//=======================================.
void CMainStage::CameraMove()
{
	//�`���[�g���A�����̃J�����ړ�.
	//if(m_bTutorialCameraMove & CAMERA_MOVE_START_FLAG){
	//	if (m_Camera.vPos.x > 11.0f) {
	//		m_Camera.vPos.x -= 0.6f;
	//		m_Camera.vLook.x = m_Camera.vPos.x;
	//		return;
	//	}

	//	const D3DXVECTOR3 vSeePeopleOldPos = D3DXVECTOR3(m_Camera.vPos.x, m_stOldCamera.vPos.y, m_stOldCamera.vPos.z);
	//	const D3DXVECTOR3 vOldPos_Camera = vSeePeopleOldPos - CAMERA_PEOPLE_SEE_POS;
	//	const float	vLength = D3DXVec3Length(&(vOldPos_Camera));
	//	const D3DXVECTOR3 vRato = vOldPos_Camera / vLength;

	//	m_Camera.vPos -= 0.2f * vRato;

	//	if(m_Camera.vPos.y < CAMERA_PEOPLE_SEE_POS.y){
	//		m_Camera.vPos = CAMERA_PEOPLE_SEE_POS;
	//	}

	//	const D3DXVECTOR3 vSeePeopleOldLook = D3DXVECTOR3(m_Camera.vLook.x, m_stOldCamera.vLook.y, m_stOldCamera.vLook.z);
	//	const D3DXVECTOR3 vOldLook_SeeLook = m_stOldCamera.vLook - CAMERA_PEOPLE_SEE_LOOK;
	//	const float	vLookLength = D3DXVec3Length(&vOldLook_SeeLook);
	//	const D3DXVECTOR3 vLookRaito = vOldLook_SeeLook / vLookLength;

	//	m_Camera.vLook -= 0.2f * vLookRaito;

	//	if (m_Camera.vPos.y < CAMERA_PEOPLE_SEE_LOOK.y) {
	//		m_Camera.vLook = CAMERA_PEOPLE_SEE_LOOK;
	//	}

	//	return;
	//}

	//if (m_bTutorialCameraMove & CAMERA_MOVE_RETURN_FLAG) {
	//	//���ݑI�����Ă��邨�����̂Ƃ���փJ������߂�.
	//	const D3DXVECTOR3 vSelectGhostPos = m_pCWorkGhost[m_SelectNum[GHOST_NUM]]->GetPos();
	//	m_Camera.vPos = CAMERA_START_POS;
	//	m_Camera.vPos.x = vSelectGhostPos.x;
	//	m_Camera.vLook = CAMERA_START_LOOK;
	//	m_Camera.vLook.x = vSelectGhostPos.x;
	//	return;
	//}

	//D3DXVECTOR3 m_GhostPos = m_pCWorkGhost[m_SelectNum[GHOST_NUM]]->GetPos();
	////�������I����.
	//if (m_ObjectSelectFlag & GHOST_SELECTION_FLAG) {
	//	m_GhostPos = m_pCWorkGhost[m_SelectNum[GHOST_NUM]]->GetPos();
	//}
	////�M�~�b�N�I����.
	//if (m_ObjectSelectFlag & GIMMICK_SELECTION_FLAG) {
	//	m_GhostPos = m_pCMoveObjectManager->GetGimmickPos();
	//}
	////�J�������W�ƒ����_�̍��W�ݒ�.
	//m_Camera.vLook.x = m_Camera.vPos.x = m_GhostPos.x;
	
}

//=========================================.
//		�X�|�b�g���C�g�X�V�����֐�.
//=========================================.
void CMainStage::SpotLightUpdate()
{
}

//==========================================.
//		�]�������֐�.
//==========================================.
CMainStage::enBeforeStageEndigneType CMainStage::Evalute()
{
	const unsigned int EVALUTION_FLAG = m_pCSurpriseGage->GetEvalutionFlag();

	if (EVALUTION_FLAG & m_pCSurpriseGage->BAD_FLAG) {
		return enBeforeStageEndigneType::Bad;
	}

	if (EVALUTION_FLAG & m_pCSurpriseGage->GOOD_FLAG) {
		return enBeforeStageEndigneType::Good;
	}

	return enBeforeStageEndigneType::Great;
}