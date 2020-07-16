#include "CMoveObjectManager.h"

CMoveObjectManager::CMoveObjectManager() 
	: CMoveObjectManager	(0, 0)
{

}

CMoveObjectManager::CMoveObjectManager(const int& FileNum, const int& StageNum)
	: m_mView					()
	, m_mProj					()
	, m_pCMoveObjectBase		()
	, m_vMoveObjectPos			()
	, m_vAttachObjPos			()
	, m_vAttachRot				()
	, m_pCFileResource			(nullptr)
	, m_pCGimmickIcon			()
	, m_pCMapGimmicKCursor		(nullptr)
	, m_SelectionNum			(0)
	, m_pCGameGimmickCursor		(nullptr)
	, m_enSurpriseObjectType	()
	, m_enGhostSurpriseObjType	()
	, m_vGhostPos				()
	, m_GhostMax				(0)
	, m_ObjeMoveFlag			(NOT_MOVE_FALG)
	, m_bGimmickCursorDisp		(false)
	, m_DispPaintingMax			(0)
	, m_AttachedObjMoveFlag		(0)
	, m_FlowerSwingCnt			(0)
	, m_bPlayEffectSound		()
	, m_bRenderUI				(true)
	, m_bPauseFlag				(false)
	, m_GimmickNumByType		(0)
	, m_pCPlaySoundManager		(CPlaySoundManager::GetPlaySoundManager())
	, m_bPlaySurpriseActSE		(0)
{
	//�����������֐�.
	Init(FileNum, StageNum);
}

CMoveObjectManager::~CMoveObjectManager()
{
	//��������֐�.
	Release();
}

//=======================================.
//		�X�V�����֐�.
//=======================================.
void CMoveObjectManager::UpDate()
{
	//�I�u�W�F�N�g.
	std::vector<bool> FoundFlag(m_vMoveObjectPos.size());
	for (int obj = 0; obj < static_cast<int>(enMoveObjectType::Max); obj++) {
		for (unsigned int allObj = 0; allObj < m_vMoveObjectPos.size(); allObj++) {
			if (FoundFlag[allObj] == false) {
				//�Đ������Ȃ�.
				m_bPlaySurpriseActSE[allObj] &= ~POSSIBLE_PLAY_SE_FLAG;
			}

			if (obj == m_enMoveObjectType[allObj]) {
				if (m_vCameraPos.x + DISP_CAMERA_WIDHT > m_vMoveObjectPos[allObj].x &&
					m_vCameraPos.x - DISP_CAMERA_WIDHT < m_vMoveObjectPos[allObj].x) {
					//�I�u�W�F�N�g�ʒu�ݒ菈��.
					m_pCMoveObjectBase[obj]->SetPos(m_vMoveObjectPos[allObj]);
					//�J�����\���t���O.
					m_pCMoveObjectBase[obj]->SetCameraDispFlag();
					//�G�t�F�N�g�Ɖ��Đ��t���O.
					m_pCMoveObjectBase[obj]->SetMoveObjectEffect(m_bPlayEffectSound[allObj]);
					//SE���Đ�������.
					m_bPlaySurpriseActSE[allObj] |= POSSIBLE_PLAY_SE_FLAG;
					FoundFlag[allObj] = true;
					if (obj == static_cast<int>(enMoveObjectType::ObjectMoveSwitch)) {
						for (int attach = 1; attach < 2; attach++) {
							//���W.
							m_pCMoveObjectBase[obj]->SetAttachedObjPos(attach, m_vAttachObjPos[allObj]);
							//�p�x.
							m_pCMoveObjectBase[obj]->SetAttachedObjRot(attach, m_vAttachRot[allObj]);
						}

					}
				}
			}

			//��ɂ����������Ȃ��ꍇ�����I�ɏ�ɂ�����.
			if (m_bUsedGimmickFlag[allObj] == false) {
				m_ObjeMoveFlag[allObj] = UP_FLAG;
			}

			//�ړ�����.
			const unsigned int UP_DOWN_FLAG = DOWN_FLAG | UP_FLAG;
			if (m_ObjeMoveFlag[allObj] & UP_DOWN_FLAG) {
				//�G��.
				if (m_enSurpriseObjectType[allObj] == CGameObject::enSurpriseObjectType::Disp) {
					//�G��𗎂Ƃ�����グ�鏈���֐�.
					PaintingUpDown(allObj);
					continue;
				}

				//�X�C�b�`.
				SwitchPush(allObj, m_enSurpriseObjectType[allObj]);
			}

		}
		

		//�X�V�����֐�.
		m_pCMoveObjectBase[obj]->Update();
	}

	//���Ɖԕr�̈ړ������֐�.
	for (unsigned int attachedObj = 0; attachedObj < m_AttachedObjMoveFlag.size(); attachedObj++) {
		if (m_AttachedObjMoveFlag[attachedObj] != 0) {
			Table_VaseFlowerMove(attachedObj);
		}
	}

	//�������ɃI�u�W�F�N�g�̏�ɂ��Ȃ��ꍇ�͗�O����.
	if (m_SelectionNum < 0) {
		m_SelectionNum = 0;
	}

	//�J�[�\���X�V����.
	//�}�b�vUI.
	m_pCGimmickIcon[m_SelectionNum]->SetSelectingFlag();
	m_pCMapGimmicKCursor->SetCharaPos(m_vMoveObjectPos[m_SelectionNum]);
	m_pCMapGimmicKCursor->UpDate();
	//�Q�[����UI.
	m_pCGameGimmickCursor->SetCharacterPos(m_vMoveObjectPos[m_SelectionNum]);
	//�g�p�o���Ȃ��J�[�\���t���O.
	bool m_bNotUseGimmickFlag = false;
	if (m_bUsedGimmickFlag[m_SelectionNum] == true ||
		m_enSurpriseObjectType[m_SelectionNum] != m_enGhostSurpriseObjType) {
		m_bNotUseGimmickFlag = true;
	}
	m_pCGameGimmickCursor->SetUnSelectableFlag(m_bNotUseGimmickFlag);
	m_pCGameGimmickCursor->UpDate();
	
	for (unsigned int icon = 0; icon < m_pCGimmickIcon.size(); icon++) {
		//�M�~�b�N�A�C�R���̍X�V�����֐�.
		m_pCGimmickIcon[icon]->UpDate();
	}
}

//======================================.
//		�`�揈���֐�.
//======================================.
void CMoveObjectManager::Render(const D3DXMATRIX& mView, const D3DXMATRIX& mProj, const LIGHT& stLight)
{
	for (int stage = 0; stage < static_cast<int>(enMoveObjectType::UseAttachObjectMax); stage++) {
		//�`�揉���ݒ菈���֐�.
		m_pCMoveObjectBase[stage]->SetCameraPos(m_vCameraPos);
		m_pCMoveObjectBase[stage]->RenderInitSetting(mView, mProj, stLight);
		//�t���I�u�W�F�N�g�̕`�揈���֐�.
		m_pCMoveObjectBase[stage]->AttachedObjRender();
	}

	if (m_bRenderUI == false) {
		//UI��`�悳���Ȃ��ŏ����I��.
		return;
	}

	//�M�~�b�N�J�[�\���`�揈���֐�.
	//�}�b�vUI.
	m_pCMapGimmicKCursor->Render();

	//�M�~�b�N�A�C�R���`�揈���֐�.
	for (unsigned int icon = 0; icon < m_pCGimmickIcon.size(); icon++) {
		m_pCGimmickIcon[icon]->Render();
	}
}

//======================================.
//		�X�C�b�`�̕`�揈���֐�.
//======================================.
void CMoveObjectManager::RenderSwitch(const D3DXMATRIX& mView, const D3DXMATRIX& mProj, const LIGHT& stLight)
{
	m_mView = mView;
	m_mProj = mProj;
	for (int obj = 0; obj < static_cast<int>(enMoveObjectType::Max); obj++) {
		//�`�揈��.
		m_pCMoveObjectBase[obj]->RenderInitSetting(mView, mProj, stLight);
		m_pCMoveObjectBase[obj]->Render();
	}
}

//======================================.
//		�G�t�F�N�g�`�揈���֐�.
//======================================.
void CMoveObjectManager::EffectRender() 
{
	for (int stage = 0; stage < static_cast<int>(enMoveObjectType::Max); stage++) {
		//�|�[�Y�t���O.
		m_pCMoveObjectBase[stage]->SetPauseFlag(m_bPauseFlag);
		//�G�t�F�N�g�`�揈���֐�.
		m_pCMoveObjectBase[stage]->EffectRender();
	}
	//�Q�[����UI.
	if (m_bGimmickCursorDisp == true) {
		m_pCGameGimmickCursor->RenderSetting(m_mView, m_mProj, m_vCameraPos);
		m_pCGameGimmickCursor->Render();
	}
}

//======================================.
//	��ޕʃM�~�b�N�ԍ��������鏈���֐�.
//======================================.
int CMoveObjectManager::FindSelectGimmickNumByType(const int& GimmickType,const int& GimmickNum)
{
	//�M�~�b�N�ԍ�����������.
	auto itr = std::find(m_GimmickNumByType[GimmickType].cbegin(), m_GimmickNumByType[GimmickType].cend(), GimmickNum);
	if (itr != m_GimmickNumByType[GimmickType].cend()) {
		return std::distance(m_GimmickNumByType[GimmickType].cbegin(), itr);
	}

	return 0;
}

//======================================.
//		�����������֐�.
//======================================.
void CMoveObjectManager::Init(const int& FileNum, const int& StageNum)
{
	//�t�@�C��.
	m_pCFileResource = CFileResource::GetResourceInstance();

	unsigned int objNum = 0;	//�I�u�W�F�N�g�ԍ�.
	unsigned int objMax = m_pCFileResource->GetStageMax(FileNum, StageNum) * static_cast<int>(enMoveObjectType::Max);
	unsigned int stageMax = m_pCFileResource->GetStageMax(FileNum, StageNum);
	unsigned int obj = 0;

	//���W�ݒ菈��.
	for (unsigned int stage = 0; stage < objMax; stage++) {
		//�e�I�u�W�F�N�g��؂�̃X�e�[�W�}�b�v��.
		int stagenum = stage - (stageMax - m_pCFileResource->GetStageMax(FileNum, StageNum));
		//�I�u�W�F�N�g�ԍ�.
		objNum = m_pCFileResource->GetStageNum(FileNum, StageNum, stagenum) - MOVEOBJECT_START_NUM;
		if (obj == objNum) {
			//�I�u�W�F�N�g���Ƃ̍��W�ݒ�.
			switch (static_cast<enMoveObjectType>(objNum)) {
			case enMoveObjectType::GhostDispPainting:
				m_vMoveObjectPos.push_back(STANDERD_PAINTING_POS);
				m_vMoveObjectPos[m_vMoveObjectPos.size() - 1].x = stagenum * OBJECT_WIDTH;
				m_enSurpriseObjectType.push_back(CGameObject::enSurpriseObjectType::Disp);
				m_vAttachObjPos.push_back(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				break;
			case enMoveObjectType::ObjectMoveSwitch:
				m_vMoveObjectPos.push_back(D3DXVECTOR3(stagenum * OBJECT_WIDTH, 0.0f, -0.5f));
				m_enSurpriseObjectType.push_back(CGameObject::enSurpriseObjectType::Switch);
				m_vAttachObjPos.push_back(D3DXVECTOR3(stagenum * OBJECT_WIDTH, 0.0f, -0.5f));
				break;
			case enMoveObjectType::PlaySoundSwitch:
				m_vMoveObjectPos.push_back(D3DXVECTOR3(stagenum * OBJECT_WIDTH, 0.0f, -0.5f));
				m_enSurpriseObjectType.push_back(CGameObject::enSurpriseObjectType::Switch);
				m_vAttachObjPos.push_back(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				break;
			}
			//�ړ��I�u�W�F�N�g�ԍ��ݒ�.
			m_enMoveObjectType.push_back(objNum);
			//�M�~�b�N�N���X�C���X�^���X��.
			m_pCGimmickIcon.push_back(nullptr);
			m_pCGimmickIcon[m_pCGimmickIcon.size() - 1].reset(new CGimmickIcon(objNum));
			//�X�e�[�W�̋����ő�l�擾.
			m_pCGimmickIcon[m_pCGimmickIcon.size() - 1]->SetStageMax(m_pCFileResource->GetStageMax(FileNum, StageNum) * OBJECT_WIDTH);
			//�M�~�b�N�A�C�R�����W�擾.
			m_pCGimmickIcon[m_pCGimmickIcon.size() - 1]->SetCharaPos(m_vMoveObjectPos[m_pCGimmickIcon.size() - 1]);
			//�M�~�b�N�A�C�R��1�񂾂��X�V������.
			m_pCGimmickIcon[m_pCGimmickIcon.size() - 1]->UpDate();

		}
		//���̓����I�u�W�F�N�g��.
		if (stage >= stageMax - 1) {
			if (obj == static_cast<int>(enMoveObjectType::GhostDispPainting)) {
				m_DispPaintingMax = m_vMoveObjectPos.size();
			}
			obj++;
			stageMax += m_pCFileResource->GetStageMax(FileNum, StageNum);
		}
	}
	//�㉺�t���O�v�f���ݒ�.
	m_ObjeMoveFlag.resize(m_pCGimmickIcon.size());
	//�g���Ă��邩�t���O.
	m_bUsedGimmickFlag.resize(m_pCGimmickIcon.size());
	//�t���I�u�W�F�N�g.
	//�ړ��t���O.
	m_AttachedObjMoveFlag.resize(m_pCGimmickIcon.size());
	//�p�x.
	m_vAttachRot.resize(m_pCGimmickIcon.size(), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//�ԕr���h���J�E���g.
	m_FlowerSwingCnt.resize(m_pCGimmickIcon.size());
	//�G�t�F�N�g�Ɖ����Đ�������t���O.
	m_bPlayEffectSound.resize(m_pCGimmickIcon.size());
	//�������s��SE�Đ��t���O.
	m_bPlaySurpriseActSE.resize(m_pCGimmickIcon.size());

	//�I�u�W�F�N�g�C���X�^���X��.
	m_pCMoveObjectBase.resize(static_cast<int>(enMoveObjectType::Max));
	m_pCMoveObjectBase[static_cast<int>(enMoveObjectType::GhostDispPainting)]	= new CGhostDispPainting();	//�������������G��.
	m_pCMoveObjectBase[static_cast<int>(enMoveObjectType::ObjectMoveSwitch)]	= new CObjectMoveSwitch();	//���������X�C�b�`.
	m_pCMoveObjectBase[static_cast<int>(enMoveObjectType::PlaySoundSwitch)]		= new CPlaySoundSwitch();	//������X�C�b�`.

	//�M�~�b�N�J�[�\���C���X�^���X��.
	m_pCMapGimmicKCursor.reset(new CMapGimmickCursor());
	m_pCMapGimmicKCursor->SetStageMax(m_pCFileResource->GetStageMax(FileNum, StageNum) * OBJECT_WIDTH);

	//�Q�[�����ł̃M�~�b�N�J�[�\���C���X�^���X��.
	m_pCGameGimmickCursor.reset(new CGameGimmickCursor());
	

	//�M�~�b�N�v�f�����בւ������֐�.
	GimmickSort();

	//�^�C�v�ʃI�u�W�F�N�g�ԍ�.
	m_GimmickNumByType.resize(static_cast<int>(CGameObject::enSurpriseObjectType::Max));
	for (unsigned int obj = 0; obj < m_pCGimmickIcon.size(); obj++) {
		const int GimmickTypeNum = static_cast<int>(m_enSurpriseObjectType[obj]);
		m_GimmickNumByType[GimmickTypeNum].push_back(obj);
	}
}

//======================================.
//		��������֐�.
//======================================.
void CMoveObjectManager::Release()
{
	for (int stage = static_cast<int>(enMoveObjectType::Max) - 1; stage >= 0; stage--) {
		SAFE_DELETE(m_pCMoveObjectBase[stage]);
	}
}

//======================================.
//	�M�~�b�N�v�f�����בւ������֐�.
//======================================.
void CMoveObjectManager::GimmickSort()
{
	for (unsigned int i = 0; i < m_pCGimmickIcon.size(); i++) {
		for (unsigned int j = m_pCGimmickIcon.size() - 1; j > i; j--) {
			if (m_vMoveObjectPos[j - 1].x > m_vMoveObjectPos[j].x) {

				//�I�u�W�F�N�g�^�C�v.
				int tmpObj;
				tmpObj = m_enMoveObjectType[j];
				m_enMoveObjectType[j] = m_enMoveObjectType[j - 1];
				m_enMoveObjectType[j - 1] = tmpObj;

				//�I�u�W�F�N�g���W.
				D3DXVECTOR3	tmpPos;
				tmpPos = m_vMoveObjectPos[j];
				m_vMoveObjectPos[j] = m_vMoveObjectPos[j - 1];
				m_vMoveObjectPos[j - 1] = tmpPos;

				//�A�C�R��.
				std::unique_ptr<CGimmickIcon>	tmpIcon;
				tmpIcon.swap(m_pCGimmickIcon[j]);
				m_pCGimmickIcon[j].swap(m_pCGimmickIcon[j - 1]);
				m_pCGimmickIcon[j - 1].swap(tmpIcon);

				//�I�u�W�F�N�g�^�C�v.
				CGameObject::enSurpriseObjectType enTmp;
				enTmp = m_enSurpriseObjectType[j];
				m_enSurpriseObjectType[j] = m_enSurpriseObjectType[j - 1];
				m_enSurpriseObjectType[j - 1] = enTmp;

				//�t���I�u�W�F�N�g���W.
				D3DXVECTOR3 tmpAttachPos;
				tmpAttachPos = m_vAttachObjPos[j];
				m_vAttachObjPos[j] = m_vAttachObjPos[j - 1];
				m_vAttachObjPos[j - 1] = tmpAttachPos;
			}
		}
	}
}

//============================================.
//		�G��𗎂Ƃ�����グ�鏈���֐�.
//============================================.
void CMoveObjectManager::PaintingUpDown(int objNum)
{
	m_bPlayEffectSound[objNum] = false;
	//�����鏈��.
	if (m_ObjeMoveFlag[objNum] & DOWN_FLAG) {
		m_vMoveObjectPos[objNum].y -= PAINTING_MOVE_SPEED;
		if (m_vMoveObjectPos[objNum].y <= PAINTING_DOWN_MAX) {
			m_vMoveObjectPos[objNum].y = PAINTING_DOWN_MAX;
			if (m_bPlaySurpriseActSE[objNum] == POSSIBLE_PLAY_SE_FLAG) {
				m_pCPlaySoundManager->SetPlaySE(enSEType::FallDownPicture);
				m_bPlaySurpriseActSE[objNum] |= PLAYED_SOUND;
			}
		}
		return;
	}

	//�グ�鏈��.
	if (m_ObjeMoveFlag[objNum] & UP_FLAG) {
		m_vMoveObjectPos[objNum].y += PAINTING_MOVE_SPEED;
		m_bPlaySurpriseActSE[objNum] &= ~PLAYED_SOUND;
	}

	if (m_vMoveObjectPos[objNum].y < STANDERD_PAINTING_POS.y) {
		return;
	}

	//���̈ʒu�ɖ߂�.
	m_vMoveObjectPos[objNum].y = STANDERD_PAINTING_POS.y;
	m_bPlayEffectSound[objNum] = true;

	//�t���O���~�낷.
	m_ObjeMoveFlag[objNum] &= ~m_ObjeMoveFlag[objNum];
}

//==============================================.
//		�X�C�b�`�������������֐�.
//==============================================.
void CMoveObjectManager::SwitchPush(int objNum, CGameObject::enSurpriseObjectType enSurpriseObj)
{
	m_bPlayEffectSound[objNum] = false;

	//�����鏈��.
	if (m_ObjeMoveFlag[objNum] & DOWN_FLAG) {
		m_vMoveObjectPos[objNum].y -= SWITCH_UP_DOWN_SPEED;
		if (m_vMoveObjectPos[objNum].y <= SWITCH_HIGHT_MIN) {
			m_vMoveObjectPos[objNum].y = SWITCH_HIGHT_MIN;
			//���̂̈ړ�.
			if (m_vAttachObjPos[objNum].x > 0.0f && m_AttachedObjMoveFlag[objNum] == 0) {
				//�t���I�u�W�F�N�g�ړ�����.
				m_AttachedObjMoveFlag[objNum] = ATTACHED_MOVE_PREPARA_FLAG;
				//�J�E���g�����ݒ�.
				m_FlowerSwingCnt[objNum] = 0;
			}
			else{
				//SE�炷.
				m_bPlayEffectSound[objNum] = true;
				if (m_bPlaySurpriseActSE[objNum] == POSSIBLE_PLAY_SE_FLAG) {
				}
			}

			if (m_bPlaySurpriseActSE[objNum] == POSSIBLE_PLAY_SE_FLAG) {
				//�Đ�
				if (m_bPlayEffectSound[objNum] == true) {
					m_pCPlaySoundManager->SetPlaySE(enSEType::PushSwitchPlaySound);
				}
				m_pCPlaySoundManager->SetPlaySE(enSEType::PushSwitch);
				m_bPlaySurpriseActSE[objNum] |= PLAYED_SOUND;
			}
		}
		return;
	}

	//�グ�鏈��.
	if (m_ObjeMoveFlag[objNum] & UP_FLAG) {
		m_vMoveObjectPos[objNum].y += SWITCH_UP_DOWN_SPEED;
		if (m_vMoveObjectPos[objNum].y >= SWITCH_HIGHT_MAX) {
			m_vMoveObjectPos[objNum].y = SWITCH_HIGHT_MAX;
			m_bPlaySurpriseActSE[objNum] &= ~PLAYED_SOUND;
		}
	}

	m_ObjeMoveFlag[objNum] &= ~m_ObjeMoveFlag[objNum];
}

//====================================================.
//		���Ɖԕr�̈ړ������֐�.
//====================================================.
void CMoveObjectManager::Table_VaseFlowerMove(int objNum)
{
	//�ړ�����.
	if (m_AttachedObjMoveFlag[objNum] & ATTACHED_MOVE_PREPARA_FLAG) {
		//�ԕr���グ�鏈��.
		m_vAttachObjPos[objNum].y += VASE_UP_DOWN_SPEED;
		if (m_vAttachObjPos[objNum].y >= VASE_HIGHT_MAX) {
			m_vAttachObjPos[objNum].y = VASE_HIGHT_MAX;
			m_AttachedObjMoveFlag[objNum] = ATTACHED_MOVE_FLAG | ATTACHED_MOVE_LEFT_FLAG;
		}


		return;
	}

	//�ړ�.
	if (m_AttachedObjMoveFlag[objNum] & ATTACHED_MOVE_FLAG) {
		//�ԕr�̗h��鏈��.

		//�߂�.
		if (m_FlowerSwingCnt[objNum] > VASE_SWING_MAX) {
			m_vAttachRot[objNum].z += VASE_SWING_SPEED;

			if (m_vAttachRot[objNum].z >= VASE_ROT_RETURN) {
				m_vAttachRot[objNum].z = VASE_ROT_RETURN;
				m_AttachedObjMoveFlag[objNum] = ATTACHED_MOVE_AFTER_FLAG;
			}
			return;
		}

		//���h��.
		if (m_AttachedObjMoveFlag[objNum] & ATTACHED_MOVE_LEFT_FLAG) {
			m_vAttachRot[objNum].z += VASE_SWING_SPEED;
			if (m_vAttachRot[objNum].z >= VASE_ROT_MAX) {
				m_vAttachRot[objNum].z = VASE_ROT_MAX;
				m_AttachedObjMoveFlag[objNum] &= ~ATTACHED_MOVE_LEFT_FLAG;
				//�h��鉹���Đ�.
				if (m_bPlaySurpriseActSE[objNum] & POSSIBLE_PLAY_SE_FLAG) {
					m_pCPlaySoundManager->SetPlaySE(enSEType::FlowerSwing);
				}
			}
			return;
		}

		//�E�h��.
		m_vAttachRot[objNum].z -= VASE_SWING_SPEED;
		if (m_vAttachRot[objNum].z <= VASE_ROT_MIN) {
			m_vAttachRot[objNum].z = VASE_ROT_MIN;
			m_FlowerSwingCnt[objNum]++;
			//�h��鉹���Đ�.
			if (m_bPlaySurpriseActSE[objNum] & POSSIBLE_PLAY_SE_FLAG) {
				m_pCPlaySoundManager->SetPlaySE(enSEType::FlowerSwing);
			}

			m_AttachedObjMoveFlag[objNum] |= ATTACHED_MOVE_LEFT_FLAG;
		}
		return;

	}

	//�ړ��I��.
	if (m_AttachedObjMoveFlag[objNum] & ATTACHED_MOVE_AFTER_FLAG) {
		m_vAttachObjPos[objNum].y -= VASE_UP_DOWN_SPEED;
		if (m_vAttachObjPos[objNum].y < VASE_HIGHT_MIN) {
			m_vAttachObjPos[objNum].y = VASE_HIGHT_MIN;
			//�S�t���O���~�낷.
			m_AttachedObjMoveFlag[objNum] = 0;
		}
	}
}