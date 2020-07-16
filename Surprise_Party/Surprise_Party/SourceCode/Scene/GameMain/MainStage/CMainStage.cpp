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
	, m_pCPlaySoundManager		(CPlaySoundManager::GetPlaySoundManager())
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
	//�J�����̍X�V�����֐�.
	if (m_ObjectSelectFlag & GIMMICK_SELECTION_FLAG) {
		m_pCCamera->SetTargetPos(m_pCMoveObjectManager->GetGimmickPos());
	}
	else {
		m_pCCamera->SetTargetPos(m_pCWorkghostManager->GetSelectGhostPos());
	}
	m_pCCamera->Update();
	const D3DXVECTOR3 m_vCameraPos = m_pCCamera->GetPos();

	//�\���䃉�C�g�N���X�̍X�V�����֐�.
	m_pCFrontstageLight->SetCameraPos(m_vCameraPos);
	m_pCFrontstageLight->Update();

	//�ÓI�I�u�W�F�N�g�X�V�����֐�.
	m_pCStaticObjectManager->SetCameraPos(m_vCameraPos);
	m_pCStaticObjectManager->Updata();

	//�����������X�V�����֐�.
	UpdateWorkGhost();


	//���I�I�u�W�F�N�g�̍X�V�����֐�.
	m_pCMoveObjectManager->SetSurpriseObjToGhost(m_pCWorkghostManager->GetSurpriseObjectType());
	m_pCMoveObjectManager->SetCameraPos(m_vCameraPos);
	m_pCMoveObjectManager->SetSelectionNum(m_SelectNum[GIMMICK_NUM]);
	m_pCMoveObjectManager->SetGhostPos(m_pCWorkghostManager->GetAllGhostPos());
	m_pCMoveObjectManager->UpDate();


	//�M�~�b�N�I���t���O.
	if (m_pCWorkghostManager->GetChangeGimmickSelectFlag() == true) {
		m_ObjectSelectFlag = GIMMICK_SELECTION_FLAG;

		//�M�~�b�N�J�[�\���\���t���O�ݒ�.
		m_pCMoveObjectManager->SetGimmickCurosrDispFlag(true);
	}

	//�}�b�v��̂������J�[�\���X�V�����֐�.
	m_pCMapGhostCursor->SetCharaPos(m_pCWorkghostManager->GetSelectGhostPos());
	m_pCMapGhostCursor->UpDate();

	//�����Q�[�W�X�V�����֐�.
	m_pCSurpriseGage->Update();

	//�`���[�g���A�������֐�.
	if (Tutorial(ControlFlag) == false) {
		return;
	}

	if (ControlFlag == true) {
		//���쏈���֐�.
		Control();

		//��������O����.
		if (m_ExplainFlag & EXPLAINING_FLAG ){
			m_pCPeopleManager->SetTutorialFlag(true);

			if(!(m_pCDescriptionUIManager->GetStartLatestFlag() & SeePeople)) {
				//�������Ɏ��_��߂�.
				if (m_pCCamera->GetMoveFlag() & m_pCCamera->PEOPLE_LOOK_FLAG) {
					m_pCCamera->SetMoveFlag(m_pCCamera->GHOST_LOOK_FLAG);
				}
				return;
			}
			if (m_pCDescriptionUIManager->GetStartLatestFlag() & SeePeople) {
				//�l�Ɏ��_���ړ�.
				m_pCCamera->SetMoveFlag(m_pCCamera->PEOPLE_LOOK_FLAG);
				//�����擾�����֐�.
				m_pCCamera->AcquisitionDifference();

			}
		}

	}

	//�l�̍X�V�����֐�.
	m_pCPeopleManager->Update();

	//�X�܂ł̎��ԍX�V�����֐�.
	m_pCClosedTime->Update();
	m_pCClosedTime->GiveBornusTime(m_pCSurpriseGage->GetBornusGetFlag());

	//�]�������֐�.
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
	//���C�g���.
	const LIGHT m_Light = m_pCFrontstageLight->GetLight();
	//�J�������W.
	const D3DXVECTOR3 m_vCameraPos = m_pCCamera->GetPos();

	if (m_pCCamera->GetNotRenderMap() == false) {
		//�X�e�[�W�}�b�v�̕`��.
		m_pCStageMap->Render();

		//�}�b�v��̂������J�[�\���`�揈���֐�.
		m_pCMapGhostCursor->Render();

		//�������̕`��.
		m_pCWorkghostManager->SetPauseFlag(m_bPauseFlag);
		m_pCWorkghostManager->Render(m_mView, m_mProj, m_Light, m_vCameraPos);
	}

	//�����I�u�W�F�N�g�X�C�b�`�̕`��.
	m_pCMoveObjectManager->RenderSwitch(m_mView, m_mProj, m_Light);
	//�ÓI�I�u�W�F�N�g�̕`��.
	m_pCStaticObjectManager->Render(m_mView, m_mProj, m_vCameraPos, m_Light);
	//�����I�u�W�F�N�g�`�揈��.
	m_pCMoveObjectManager->Render(m_mView, m_mProj, m_Light);

	//�������̗̓A�C�R���`�揈���֐�.
	m_pCWorkghostManager->RenderIcon();

	//�l�̕`�揈���֐�.
	m_pCPeopleManager->SetNotRenderIcon(m_pCCamera->GetNotRenderMap());
	m_pCPeopleManager->SetPauseFlag(m_bPauseFlag);
	m_pCPeopleManager->Render(m_mView, m_mProj, m_vCameraPos, m_Light);

	//�����I�u�W�F�N�g�̃G�t�F�N�g�`��.
	bool m_bUIRender = true;
	if (m_pCCamera->GetNotRenderMap() == true) {
		m_bUIRender = false;
	}
	m_pCMoveObjectManager->SetRenderUI(m_bUIRender);
	m_pCMoveObjectManager->SetPauseFlag(m_bPauseFlag);
	m_pCMoveObjectManager->EffectRender();
	
	//�Q�[�����ł̂������̃J�[�\���`�揈���֐�.
	m_pCGameGhostCursor->RenderSetting(m_mView, m_mProj, m_vCameraPos);
	m_pCGameGhostCursor->Render();

	//�������̑I��`�揈���֐�.
	if (m_ObjectSelectFlag & GHOST_ACT_SELECT_FLAG) {
		m_pCWorkghostManager->RenderSelectUI();
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
		const unsigned int RELATED_TO_GHOST_ALL_FLAG = SELECT_GHOST_FLAG | GIMMICK_SELECTION_FLAG;
		if (m_vCameraPos.x == m_vSelectGhostPos.x &&
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
	const int FileNum = 0;

	//�I�u�W�F�N�g�t�@�C���ԍ�.
	const int ObjFileNum = static_cast<int>(CFileResource::enStageType::ObjectPos);

	//�ǂݍ��݃N���X�A�h���X�擾.
	CFileResource* m_pCFileResource = CFileResource::GetResourceInstance();
	
	m_pCStaticObjectManager.reset(new CStaticObjectManager(ObjFileNum, m_StageNum));

	//�X�e�[�W�̒����ő吔.
	float m_fStageDistanceMax = m_pCStaticObjectManager->GetStageDistanceMax();

	const int GhostFilenum = static_cast<int>(CFileResource::enStageType::GhostPos);
	//�������Ǘ��N���X���C���X�^���X��.
	m_pCWorkghostManager.reset(new CMainStageWorkGhostManager());
	m_pCWorkghostManager->Init(GhostFilenum, m_StageNum, m_pCStaticObjectManager->OBJECT_WIDTH);

	//���I�I�u�W�F�N�g�C���X�^���X��.
	m_pCMoveObjectManager.reset(new CMoveObjectManager(ObjFileNum, m_StageNum));
	m_pCMoveObjectManager->SetGhostElementCount(m_pCWorkghostManager->GetAllGhostNum());
	

	//�l�Ǘ��N���X�ݒ�.
	const int PeopleFileNum = static_cast<int>(CFileResource::enStageType::PeopleComeOder);
	m_pCPeopleManager.reset(new CPeopleManager());
	m_pCPeopleManager->Init( PeopleFileNum, m_StageNum, m_fStageDistanceMax);
	
	//�M�~�b�N�̏�ɂ����������邩�̔��菈��.
	const std::vector<D3DXVECTOR3> m_vGimmickPos = m_pCMoveObjectManager->GetAllGimmickPos();
	const std::vector<D3DXVECTOR3> m_vWorkGhostPos = m_pCWorkghostManager->GetAllGhostPos();
	const float			GIMMICK_UP_DECISION = 0.1f;								//�M�~�b�N�̏�ɏ���Ă��邩�̔��荷��.
	for (unsigned int gimmick = 0; gimmick < m_vGimmickPos.size(); gimmick++) {
		for (unsigned int ghost = 0; ghost < m_vWorkGhostPos.size(); ghost++) {
			if (fabsf(m_vWorkGhostPos[ghost].x - m_vGimmickPos[gimmick].x) < GIMMICK_UP_DECISION) {
				m_pCWorkghostManager->SetUseGimmickNum(ghost, gimmick);	
				m_pCMoveObjectManager->SetUsedGimmickFlag(gimmick, true);
			}
		}
	}

	//====UI�n�̃C���X�^���X��====.
	//�X�e�[�W.
	m_pCStageMap.reset(new CStageMap());
	//�}�b�v��̂������̃J�[�\��.
	m_pCMapGhostCursor.reset(new CMapGhostCursor());
	m_pCMapGhostCursor->SetStageMax(m_fStageDistanceMax);
	//�Q�[�����������̃J�[�\��.
	m_pCGameGhostCursor.reset(new CGameGhostCursor());
	//�O��̃X�e�[�W������.
	m_enBeforeStageEndingType = enBeforeStageEndigneType::Nothing;

	//�X�܂ł̎���.
	m_pCClosedTime.reset(new CClosedTime(m_StageNum));

	//�����Q�[�W.
	m_pCSurpriseGage.reset(new CSurpriseGage(m_StageNum));

	//���߂͂������̑I������.
	m_ObjectSelectFlag = GHOST_SELECTION_FLAG;
	
	//�I��ԍ�������.
	m_SelectNum.resize(SLECTION_MAX);
	for (unsigned int select = 0; select < m_SelectNum.size(); select++) {
		m_SelectNum[select] = 0;
	}

	//�J�����N���X�̃C���X�^���X��.
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
		if (GetAsyncKeyState(VK_RETURN) & 0x8000) {
			//���������������Ă���Ƃ��̂�.
			if (m_pCWorkghostManager->DecisionSelectSurprise() == true) {

				if (m_pCDescriptionUIManager != nullptr && m_ExplainFlag != 0) {
					if (!(m_pCDescriptionUIManager->GetTutorialFlag() & DECIDE_GHOST_FLAG)) {
						return;
					}

					if (m_pCDescriptionUIManager->GetAppearancedAllFont() == false) {
						return;
					}

					//�R�����g�i�߂�.
					m_pCDescriptionUIManager->SetAdvanceComment();
				}
				//�I���t���O.
				m_pCWorkghostManager->SetSelectFlag(true);

				//�M�~�b�N�ԍ��擾.
				m_SelectNum[GIMMICK_NUM] = m_pCWorkghostManager->GetUseGimmickNumToSelectGhost();

				//�������I����s��.
				m_ObjectSelectFlag = GHOST_ACT_SELECT_FLAG;

				if (m_ExplainFlag & EXPLAINING_FLAG) {
					//�������̐����I��.
					m_ExplainFlag |= EXPLAINED_GHOST_FLAG;
				}
			}
		}
	}

	//�ړ�����M�~�b�N����.
	if (m_ObjectSelectFlag & GIMMICK_SELECTION_FLAG) {
		if ((GetAsyncKeyState(VK_BACK) & 0x0001) || 
			m_pCWorkghostManager->GetRestSelectGhostFlag() == true) {
			//�������͏������Ăق����Ȃ�.
			if (m_ExplainFlag != 0) {
				return;
			}
			m_pCWorkghostManager->SetSelectStop();
			//�������̑I���ɖ߂�.
			m_ObjectSelectFlag = GHOST_SELECTION_FLAG;
			//�M�~�b�N�I���t���O.
			m_pCWorkghostManager->SetChangeGimmickSelect(false);
			//�M�~�b�N�J�[�\����\���t���O�ݒ�.
			m_pCMoveObjectManager->SetGimmickCurosrDispFlag(false);
			//�M�~�b�N�I������SE�̍Đ�.
			m_pCPlaySoundManager->SetPlaySE(enSEType::ReturnFromGimmickSelect);
		}

		if (GetAsyncKeyState(VK_RETURN) & 0x8000) {
			if (m_pCMoveObjectManager->GetUsedGimmickFlag(m_SelectNum[GIMMICK_NUM]) == true) {
				//�M�~�b�N���g�p����Ă����珈�����Ȃ�.
				m_pCPlaySoundManager->SetPlaySE(enSEType::NotSelect);
				return;
			}


			//�`���[�g���A�����ɃR�����g��i�߂鏈��.
			if (m_pCDescriptionUIManager != nullptr && m_ExplainFlag != 0) {
				//��O����.
				if (!(m_pCDescriptionUIManager->GetTutorialFlag() & DECIDE_GIMMICK_FLAG)) {
					return;
				}
				m_pCDescriptionUIManager->SetAdvanceComment();
			}

			//�g�p����M�~�b�N�ԍ��̕ύX.
			if (m_pCWorkghostManager->GetUseGimmickNumToSelectGhost() >= 0) {
				m_pCMoveObjectManager->SetUsedGimmickFlag(m_pCWorkghostManager->GetUseGimmickNumToSelectGhost(), false);
			}
			m_pCMoveObjectManager->SetUsedGimmickFlag(m_SelectNum[GIMMICK_NUM], true);
			m_pCWorkghostManager->SetUseGimmickNumToSelectGhost(m_SelectNum[GIMMICK_NUM]);

			//�ړ��ړI�̃I�u�W�F�N�g���W�擾.
			m_pCWorkghostManager->SetObjectiveGimmickPos(m_pCMoveObjectManager->GetGimmickPos());
			//�������̑I���ɖ߂�.
			m_ObjectSelectFlag = GHOST_SELECTION_FLAG;
			//�M�~�b�N�I���t���O.
			m_pCWorkghostManager->SetChangeGimmickSelect(false);
			//�M�~�b�N�J�[�\����\���t���O�ݒ�.
			m_pCMoveObjectManager->SetGimmickCurosrDispFlag(false);

			//�I��SE�Đ�����.
			m_pCPlaySoundManager->SetPlaySE(enSEType::GimmickDecide);

			if (m_ExplainFlag & EXPLAINING_FLAG) {
				//�M�~�b�N�����I��.
				m_ExplainFlag |= EXPLAINED_GIMMICK_FLAG;
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
	//�������I���ړ��t���O.
	bool MoveSelectFlag = m_pCWorkghostManager->SelectGhost();	

	if (MoveSelectFlag == true) {
		const int GHOST_TYPE_NUM = static_cast<int>(m_pCWorkghostManager->GetSurpriseObjectType());
		
		if (m_pCSpeakWorkGhost != nullptr) {
			//�������I���Ɋ֌W���邷�ׂẴt���O.
			const unsigned int RELATED_TO_GHOST_ALL_FLAG = GHOST_SELECTION_FLAG | GHOST_ACT_SELECT_FLAG;
			//�������I�����Ă��鎞�̂ݐݒ�\.
			if (m_ObjectSelectFlag & RELATED_TO_GHOST_ALL_FLAG) {
				m_pCSpeakWorkGhost->SetGhostTypeNum(GHOST_TYPE_NUM);
				m_vSelectGhostPos = m_pCWorkghostManager->GetSelectGhostPos();
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
	//�I���ړ��t���O.
	bool MoveSelectFlag = false;					
	//�M�~�b�N�^�C�v�ԍ�.
	const int GimmickType = static_cast<int>(m_pCWorkghostManager->GetSurpriseObjectType());
	//�M�~�b�N�ύX�ԍ�.
	int	ChangeSelectNum = m_pCMoveObjectManager->FindSelectGimmickNumByType(GimmickType, m_SelectNum[GIMMICK_NUM]);


	if (GetAsyncKeyState(VK_RIGHT) & 0x0001) {
		//�ő�l�̎�O�̐��l.
		const int BeforeGimmickMax = m_pCMoveObjectManager->GetGimmickMaxByType(GimmickType) - 1;
		//�����M�~�b�N�ɑI�����ړ����鏈��.
		if (ChangeSelectNum < BeforeGimmickMax) {
			ChangeSelectNum++;
			m_SelectNum[GIMMICK_NUM] = m_pCMoveObjectManager->GetGimmickNumByType(GimmickType, ChangeSelectNum);
			MoveSelectFlag = true;
			//�J�[�\���ړ�SE�̍Đ�.
			m_pCPlaySoundManager->SetPlaySE(enSEType::GhostGimmickMove);
		}
		else {
			//�J�[�\���ړ����SE�̍Đ�.
			m_pCPlaySoundManager->SetPlaySE(enSEType::GhostGimmickSelectLimit);
		}
	}

	if (GetAsyncKeyState(VK_LEFT) & 0x0001) {
		//�����M�~�b�N�ɑI�����ړ����鏈��.
		if (ChangeSelectNum > 0) {
			ChangeSelectNum--;
			m_SelectNum[GIMMICK_NUM] = m_pCMoveObjectManager->GetGimmickNumByType(GimmickType, ChangeSelectNum);
			MoveSelectFlag = true;
			//�J�[�\���ړ�SE�̍Đ�.
			m_pCPlaySoundManager->SetPlaySE(enSEType::GhostGimmickMove);
		}
		else {
			//�J�[�\���ړ����SE�̍Đ�.
			m_pCPlaySoundManager->SetPlaySE(enSEType::GhostGimmickSelectLimit);
		}
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

//===========================================.
//		�`���[�g���A�������֐�.
//===========================================.
bool CMainStage::Tutorial(const bool& ControlFlag)
{
	//�`���[�g���A���܂ł̏���(�����ł������ƃM�~�b�N�̎��͗�O�̏������s��Ȃ���΂Ȃ�Ȃ�).
	if (m_enStageType == enStageType::Tutorial && (m_ExplainFlag & EXPLAINING_FLAG)) {

		//�t�F�[�h���͗�O����.
		if (ControlFlag == false) {
			return false;

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

			m_pCWorkghostManager->UnloadTutorialFlag(m_pCWorkghostManager->EXPLAINING_FLAG);
			m_pCWorkghostManager->UnloadTutorialFlag(m_pCWorkghostManager->SELECT_WAIT_FLAG);
		}
	}

	if (m_pCDescriptionUIManager != nullptr) {
		//�R�����g�i�߂�Ƃ��͉��܂ŏ������Ȃ�.
		if (m_pCDescriptionUIManager->GetAdvanceCommentFlag() == true) {
			const unsigned int DESCRIPTION_LAST_FLAG = SeePeople | DescriptionEnd;
			if (!(m_pCDescriptionUIManager->GetStartLatestFlag() & DESCRIPTION_LAST_FLAG)) {
				return false;
			}
		}
	}

	return true;

}

//===========================================.
//		�����������X�V�����֐�.
//===========================================.
void CMainStage::UpdateWorkGhost()
{
	//�`���[�g���A�����ǂ���.
	if (m_enStageType == enStageType::Tutorial) {
		m_pCWorkghostManager->SetTutorialFlag(m_pCWorkghostManager->TUTORIAL_STAGE_FLAG);
	}

	//�����I��.
	if (m_ExplainFlag != 0) {
		m_pCWorkghostManager->SetTutorialFlag(m_pCWorkghostManager->EXPLAINING_FLAG);
	}

	if (m_pCDescriptionUIManager != nullptr) {
		//�`���[�g���A���t���O�グ���������֐�.
		UnloadSetTrueTutrialFlag();
	}

	//�����������Ǘ��N���X�̍X�V�����֐�.
	m_pCWorkghostManager->SetStageDisntaceMax(m_pCStaticObjectManager->GetStageDistanceMax());
	m_pCWorkghostManager->SetGimmickPos(m_pCMoveObjectManager->GetAllGimmickPos());
	m_pCWorkghostManager->SetPeoplePos(m_pCPeopleManager->GetHumanPos());
	m_pCWorkghostManager->Update();

	//���N���X�ɒl�Q��.
	for (unsigned int ghost = 0; ghost < m_pCWorkghostManager->GetAllGhostNum(); ghost++) {
		//�����Ă���l�ԍ��擾.
		m_pCPeopleManager->SetNowHumanSurprise(m_pCWorkghostManager->GetNearPeopleNum(ghost));
		//�ǉ��|�C���g��.
		m_pCSurpriseGage->AddSurprisePoint(m_pCPeopleManager->GetAddSurprisePoint());

		//�R�����g�i�߂�t���O.
		if (m_pCDescriptionUIManager != nullptr) {
			if (m_pCWorkghostManager->GetTutorialAddCommentFlag(ghost) == true) {
				m_pCDescriptionUIManager->SetAdvanceComment();
			}
		}

		//�I�u�W�F�N�g�グ�����t���O.
		const unsigned int UpDownFlag = m_pCWorkghostManager->GetUpDownFlag(ghost);
		const int	GimmickNum = m_pCWorkghostManager->GetUseGimmickNum(ghost);
		if (UpDownFlag != 0 && GimmickNum >= 0) {
			if (UpDownFlag & m_pCWorkghostManager->OBJ_DOWN_FLAG) {
				m_pCMoveObjectManager->SetGimmickMoveFlag(GimmickNum, m_pCMoveObjectManager->DOWN_FLAG);
				continue;
			}
			m_pCMoveObjectManager->SetGimmickMoveFlag(GimmickNum, m_pCMoveObjectManager->UP_FLAG);
		}

	}

	//�������I���t���O.
	if (m_ObjectSelectFlag & GHOST_ACT_SELECT_FLAG) {
		if (m_pCWorkghostManager->GetSelectGhostFlag() == false) {
			m_ObjectSelectFlag = GHOST_SELECTION_FLAG;
		}
	}

	//�������x�e�t���O.	
	bool GhostRestFlag = m_pCWorkghostManager->DecisionSelectRest();
	m_pCGameGhostCursor->SetRestFlag(GhostRestFlag);
	m_pCGameGhostCursor->SetCharacterPos(m_pCWorkghostManager->GetSelectGhostPos());

	//�Q�[�����ł̂������̃J�[�\���X�V�����֐�.
	m_pCGameGhostCursor->UpDate();

}

//========================================.
//	�`���[�g���A���t���O�グ��������.
//========================================.
void CMainStage::UnloadSetTrueTutrialFlag()
{
	if (m_ExplainFlag == 0) {
		return;
	}

	//�����������߂�t���O.
	if (m_pCDescriptionUIManager->GetAdvanceCommentFlag() == false) {
		//�t���O�𗧂Ă�.
		m_pCWorkghostManager->SetTutorialFlag(m_pCWorkghostManager->GHOST_DECIDE_FLAG);
	}
	else {
		//�t���O���~�낷.
		m_pCWorkghostManager->UnloadTutorialFlag(m_pCWorkghostManager->GHOST_DECIDE_FLAG);
	}

	//�I��ҋ@�t���O.
	if (m_pCDescriptionUIManager->GetAppearancedAllFont() == false &&
		m_ObjectSelectFlag & GHOST_ACT_SELECT_FLAG) {
		//�t���O�𗧂Ă�.
		m_pCWorkghostManager->SetTutorialFlag(m_pCWorkghostManager->SELECT_WAIT_FLAG);
	}
	else {
		//�t���O���~�낷.
		m_pCWorkghostManager->UnloadTutorialFlag(m_pCWorkghostManager->SELECT_WAIT_FLAG);
	}

}
