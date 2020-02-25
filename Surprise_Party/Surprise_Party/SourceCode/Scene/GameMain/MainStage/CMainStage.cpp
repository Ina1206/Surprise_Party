#include "CMainStage.h"

CMainStage::CMainStage()
	: CMainStage	(0, enBeforeStageEndigneType::Nothing)
{

}

CMainStage::CMainStage(int stageNum, enBeforeStageEndigneType enType)
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


	//�l�̍X�V�����֐�.
	m_pCPeopleManager->UpDate();

	//������.
	std::vector<D3DXVECTOR3> m_vGhostPos(m_pCWorkGhost.size());							//���������W.
	std::vector<D3DXVECTOR3> m_vGimmickPos = m_pCMoveObjectManager->GetAllGimmickPos();	//�M�~�b�N���W.
	for (unsigned int ghost = 0; ghost < m_pCWorkGhost.size(); ghost++) {
		//�X�e�[�W�S�̂̋����擾.
		m_pCWorkGhost[ghost]->SetStageDistanceMax(m_pCStaticObjectManager->GetStageDistanceMax());

		//�M�~�b�N�Ɛl�̍��W�擾.
		m_pCWorkGhost[ghost]->SetSurprisePosInfo(m_vGimmickPos, m_pCPeopleManager->GetHumanPos());

		//�������X�V�����֐�.
		m_pCWorkGhost[ghost]->UpDate();

		//�������̍��W�擾.
		m_vGhostPos[ghost] = m_pCWorkGhost[ghost]->GetPos();
		D3DXVECTOR3 vTargetPos;
		std::unique_ptr<CWorkGhostBase> pTmp;
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

	//���쏈���֐�.
	if (ControlFlag == true) {
		Control();
	}

	//���I�I�u�W�F�N�g�̍X�V�����֐�.
	m_pCMoveObjectManager->SetCameraPos(m_Camera.vPos);
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
	m_pCSurpriseGage->UpDate();

	//�X�܂ł̎��ԍX�V�����֐�.
	m_pCClosedTime->UpDate();
	m_pCClosedTime->GiveBornusTime(m_pCSurpriseGage->GetBornusGetFlag());

	if (m_pCSurpriseGage->GetSurprisePointMax() == true) {
		m_enBeforeStageEndingType = enBeforeStageEndigneType::Great;
	}

	//�I������.
	if (m_pCClosedTime->GetClosedFlag() == true) {
		m_bChangeStageFlag = true;
	}
}

//===================================.
//		�`�揈���֐�.
//===================================.
void CMainStage::Render()
{
	static bool	m_ControlFlag = true;
	if (m_ControlFlag == true) {
		if (GetAsyncKeyState('1') & 0x8000) {
			m_stLight.fIntensity -= 0.1f;
		}

		if (GetAsyncKeyState('2') & 0x8000) {
			m_stLight.fIntensity += 0.1f;
		}
	}
	else {
		if (GetAsyncKeyState('1') & 0x8000) {
			m_stLight.m_fLightWidth -= 0.1f;
		}

		if (GetAsyncKeyState('2') & 0x8000) {
			m_stLight.m_fLightWidth += 0.1f;
		}

	}

	if (GetAsyncKeyState(VK_F1) & 0x8000) {
		if (m_ControlFlag == true) {
			m_ControlFlag = false;
		}
		else {
			m_ControlFlag = true;
		}
	}

	//�X�e�[�W�}�b�v�̕`��.
	m_pCStageMap->Render();

	//�}�b�v��̂������J�[�\���`�揈���֐�.
	m_pCMapGhostCursor->Render();


	//�������̕`��.
	for (unsigned int ghost = 0; ghost < m_pCWorkGhost.size(); ghost++) {
		//�������{�̂̕`�揈���֐�.
		m_pCWorkGhost[ghost]->SetCameraPos(m_Camera.vPos);
		m_pCWorkGhost[ghost]->RenderInitSetting(m_mView, m_mProj, m_stLight);
		m_pCWorkGhost[ghost]->Render();
	}


	//�����I�u�W�F�N�g�̕`��.
	m_pCMoveObjectManager->Render(m_mView, m_mProj, m_stLight);

	//�ÓI�I�u�W�F�N�g�̕`��.
	m_pCStaticObjectManager->SetCameraPos(m_Camera.vPos);
	m_pCStaticObjectManager->UpData();
	m_pCStaticObjectManager->Render(m_mView, m_mProj, m_Camera.vPos, m_stLight);

	//�������̗̓A�C�R���`�揈���֐�.
	for (unsigned int ghost = 0; ghost < m_pCWorkGhost.size(); ghost++) {
		m_pCWorkGhost[ghost]->StrengthIconRender();
	}

	//�l�̕`�揈���֐�.
	m_pCPeopleManager->Render(m_mView, m_mProj, m_Camera.vPos, m_stLight);

	//�����I�u�W�F�N�g�̃G�t�F�N�g�`��.
	m_pCMoveObjectManager->EffectRender();
	
	//�Q�[�����ł̂������̃J�[�\���`�揈���֐�.
	m_pCGameGhostCursor->RenderSetting(m_mView, m_mProj, m_Camera.vPos);
	m_pCGameGhostCursor->Render();

	//�������̑I��`�揈���֐�.
	if (m_ObjectSelectFlag & GHOST_ACT_SELECT_FLAG) {
		m_pCWorkGhost[m_SelectNum[GHOST_NUM]]->SelectRender();
	}

	//�X�܂ł̎��ԕ`�揈���֐�.
	m_pCClosedTime->Render();

	//�����Q�[�W�`�揈���֐�.
	m_pCSurpriseGage->Render();
}

//===================================.
//		�����������֐�.
//===================================.
void CMainStage::Init()
{
	//�S�̓I�Ƀt�@�C���ԍ�.
	int FileNum = 0;

	//�I�u�W�F�N�g�t�@�C���ԍ�.
	int ObjFileNum = m_StageNum + FileNum;

	//�ǂݍ��݃N���X�A�h���X�擾.
	CFileResource* m_pCFileResource = CFileResource::GetResourceInstance();

	//�ÓI�I�u�W�F�N�g�C���X�^���X��.
	m_pCStaticObjectManager.reset(new CStaticObjectManager());

	//�������ݒ�.
	int GhostFilenum = (static_cast<int>(CFileResource::enStageType::GhostPos_OneDay) * 3) + FileNum;
	for (int stage = 0; stage < m_pCFileResource->GetStageMax(GhostFilenum); stage++) {
		switch (m_pCFileResource->GetStageNum(GhostFilenum, 0, stage) - 1) {
		case 0:
			m_pCWorkGhost.push_back(nullptr);
			m_pCWorkGhost[m_pCWorkGhost.size() - 1].reset(new CDispGhost());
			m_pCWorkGhost[m_pCWorkGhost.size() - 1]->SetPos(D3DXVECTOR3(stage * m_pCStaticObjectManager->OBJECT_WIDTH, 0.0f, 3.5f));
			m_pCWorkGhost[m_pCWorkGhost.size() - 1]->SetInitMovePos();
			break;
		case 1:
			m_pCWorkGhost.push_back(nullptr);
			m_pCWorkGhost[m_pCWorkGhost.size() - 1].reset(new CSwitchGhost());
			m_pCWorkGhost[m_pCWorkGhost.size() - 1]->SetPos(D3DXVECTOR3(stage * m_pCStaticObjectManager->OBJECT_WIDTH, 3.5f, 3.5f));
			m_pCWorkGhost[m_pCWorkGhost.size() - 1]->SetInitMovePos();
			break;
		}
	}

	//���I�I�u�W�F�N�g�C���X�^���X��.
	m_pCMoveObjectManager.reset(new CMoveObjectManager(ObjFileNum));
	m_pCMoveObjectManager->SetGhostElementCount(m_pCWorkGhost.size());
	
	//�l�Ǘ��N���X�ݒ�.
	m_pCPeopleManager.reset(new CPeopleManager());
	m_pCPeopleManager->Init(static_cast<int>(CFileResource::enStageType::PeopleOder) + FileNum, 12, m_pCFileResource->GetStageMax(GhostFilenum) * m_pCMoveObjectManager->OBJECT_WIDTH);
	m_pCPeopleManager->SetStageDistanceMax(m_pCStaticObjectManager->GetStageDistanceMax());

	//====UI�n�̃C���X�^���X��====.
	//�X�e�[�W.
	m_pCStageMap.reset(new CStageMap());
	//�}�b�v��̂������̃J�[�\��.
	m_pCMapGhostCursor.reset(new CMapGhostCursor());
	m_pCMapGhostCursor->SetStageMax(m_pCStaticObjectManager->GetStageDistanceMax());
	//�Q�[�����������̃J�[�\��.
	m_pCGameGhostCursor.reset(new CGameGhostCursor());
	//�X�܂ł̎���.
	//�X�e�[�W���Ƃɐ������Ԃ�L�΂�.
	int TimeUpMax = START_TIME_UP_MAX + (ADD_TIME_UP * m_StageNum);
	//Good,Great���ƃ{�[�i�X�Ő������Ԃ�ǉ�.
	if (m_enBeforeStageEndingType == enBeforeStageEndigneType::Great) {
		TimeUpMax += BENEFITS_PREVIOS_RESULT;
	}
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
	m_Camera.vPos = CAMERA_START_POS;
	m_Camera.vLook = CAMERA_START_LOOK;

	//���C�g��񏉊��ݒ�.
	m_stLight.vPos = D3DXVECTOR3(17.1f, -3.7f, -0.3f);
	m_stLight.fIntensity = 15.0f;
	m_stLight.m_fLightWidth = 10.0f;
	m_stLight.m_fLightWidth = 0.9f;
	D3DXMatrixIdentity(&m_stLight.mRot);
	
	D3DXMATRIX mYaw, mPich, mRoll;
	D3DXMatrixRotationY(&mYaw, 0.0f);
	D3DXMatrixRotationX(&mPich, 2.8f);
	D3DXMatrixRotationZ(&mRoll, 0.0f);
	m_stLight.mRot = mYaw * mPich * mRoll;

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
		GhostSelect();
	}

	//============================================.
	//�M�~�b�N�I�������֐�.
	if (m_ObjectSelectFlag & GIMMICK_SELECTION_FLAG) {
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
				//�������I����s��.
				m_ObjectSelectFlag = GHOST_ACT_SELECT_FLAG;
				//�I���t���O.
				m_pCWorkGhost[m_SelectNum[GHOST_NUM]]->SetSelectFlag(true);
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

					//�ړ��ړI�̃I�u�W�F�N�g���W�擾.
					m_pCWorkGhost[m_SelectNum[GHOST_NUM]]->SetObjectiveGimmickPos(m_pCMoveObjectManager->GetGimmickPos());
					//�������̑I���ɖ߂�.
					m_ObjectSelectFlag = GHOST_SELECTION_FLAG;
					//�M�~�b�N�I���t���O.
					m_pCWorkGhost[m_SelectNum[GHOST_NUM]]->SetChangeGimmickSelect(false);
					//�M�~�b�N�J�[�\����\���t���O�ݒ�.
					m_pCMoveObjectManager->SetGimmickCurosrDispFlag(false);
				}
			}
		}
	}


#ifdef _DEBUG
	if (GetAsyncKeyState(VK_UP) & 0x0001) {
		m_ObjectSelectFlag = GHOST_SELECTION_FLAG;
	}

	if (GetAsyncKeyState(VK_DOWN) & 0x0001) {
		m_ObjectSelectFlag = GIMMICK_SELECTION_FLAG;
	}
#endif	//#ifdef _DEBUG.
}

//========================================.
//		�������I�������֐�.
//========================================.
void CMainStage::GhostSelect()
{
	if (GetAsyncKeyState(VK_RIGHT) & 0x0001) {
		m_SelectNum[GHOST_NUM]++;

		if (m_SelectNum[GHOST_NUM] >= static_cast<int>(m_pCWorkGhost.size())) {
			m_SelectNum[GHOST_NUM] = m_pCWorkGhost.size() - 1;
		}
		return;
	}

	if (GetAsyncKeyState(VK_LEFT) & 0x0001) {
		m_SelectNum[GHOST_NUM]--;

		if (m_SelectNum[GHOST_NUM] < 0) {
			m_SelectNum[GHOST_NUM] = 0;
		}
		return;
	}
}

//========================================.
//		�M�~�b�N�I�������֐�.
//========================================.
void CMainStage::GimmickSelect()
{

	if (GetAsyncKeyState(VK_RIGHT) & 0x0001) {
		m_SelectNum[GIMMICK_NUM]++;
		if (m_SelectNum[GIMMICK_NUM] >= m_pCMoveObjectManager->GetGimmickIconMax()) {
			m_SelectNum[GIMMICK_NUM] = m_pCMoveObjectManager->GetGimmickIconMax() - 1;
		}
		return;
	}

	if (GetAsyncKeyState(VK_LEFT) & 0x0001) {
		m_SelectNum[GIMMICK_NUM]--;
		if (m_SelectNum[GIMMICK_NUM] < 0) {
			m_SelectNum[GIMMICK_NUM] = 0;
		}
		return;
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
	D3DXVECTOR3 m_GhostPos = m_pCWorkGhost[m_SelectNum[GHOST_NUM]]->GetPos();
	//�������I����.
	if (m_ObjectSelectFlag & GHOST_SELECTION_FLAG) {
		m_GhostPos = m_pCWorkGhost[m_SelectNum[GHOST_NUM]]->GetPos();
	}
	//�M�~�b�N�I����.
	if (m_ObjectSelectFlag & GIMMICK_SELECTION_FLAG) {
		m_GhostPos = m_pCMoveObjectManager->GetGimmickPos();
	}
	//�J�������W�ƒ����_�̍��W�ݒ�.
	m_Camera.vLook.x = m_Camera.vPos.x = m_GhostPos.x;
	
}

//template void CMainStage::GhostElementSort<std::unique_ptr<CWorkGhostBase>>(CWorkGhostBase, int);