#include "CMainStageWorkGhostBase.h"

/**********************************************
*	���C���X�e�[�W�̓������������N���X.
****************/
CMainStageWorkGhostBase::CMainStageWorkGhostBase()
	: m_pCAct_Selection			(nullptr)
	, m_MoveFlag				(SURPRISE_FLAG)
	, m_bSelectFlag				(false)
	, m_ActType					(0)
	, m_fStageMaxDistance		(0.0f)
	, m_pCGhostIcon				(nullptr)
	, m_bGhostSelectIcon		(false)
	, m_vObjectiveGimmickPos	(0.0f, 0.0f, 0.0f)
	, m_bChangeGimmickSelect	(false)
	, m_enSurpriseObjectType	(enSurpriseObjectType::Disp)
	, m_fStrength				(0.0f)
	, m_fStrengthMax			(0.0f)
	, m_fMoveSpeed				(0.0f)
	, m_fMoveSpeedMax			(0.0f)
	, m_fRecoverySpeed			(0.0f)
	, m_SurpriseFlag			(0)
	, m_fScaleMax				(0.0f)
	, m_pCGhostStrengthIcon		(nullptr)
	, m_UpDownObjectFlag		(0)
	, m_vMovePos				(0.0f, 0.0f, 0.0f)
	, m_vSurpriseBeforePos		(0.0f, 0.0f, 0.0f)
	, m_vStrengthIconPos		(0.0f, 0.0f, 0.0f)
	, m_fMoveFinishHight		(0.0f)
	, m_bNowHumanSurprise		(false)
	, m_NearHumanNum			()
	, m_vEffectCenterPos		(0.0f, 0.0f, 0.0f)
	, m_pCFatigue				(nullptr)
	, m_GhostType				(0)
	, m_MoveDirection			(0)
	, m_vGimmickPos				()
	, m_vHumanPos				()
	, m_pCHitSphere				(2)
	, m_RestFlag				(REST_PREPARAT_FLAG)
	, m_OldStrengthType			(0)
	, m_SurpriseRestTime		(0)
	, m_UseGimmickNum			(-1)
	, m_bLimitationRest			(false)
	, m_bTutorialCommentAddFlag	(false)
{
	//�ǂݍ��񂾋��̃A�h���X�擾.
	for (unsigned int sphere = 0; sphere < m_pCHitSphere.size(); sphere++) {
		m_pCHitSphere[sphere] = m_pCResourceManager->GetStaticMesh(enStaticMeshType::HitSphere);
	}
	//�������̗̑̓A�C�R���̃C���X�^���X��.
	m_pCGhostStrengthIcon.reset(new CGhostStrengthIcon());

	//��J�G�t�F�N�g�C���X�^���X��.
	m_pCFatigue.reset(new CSurpriseEffect());

}

CMainStageWorkGhostBase::~CMainStageWorkGhostBase()
{
	for (int sphere = static_cast<int>(m_pCHitSphere.size()) - 1; sphere >= 0; sphere--) {
		m_pCHitSphere[sphere] = nullptr;
	}

}

//=========================================.
//		�s���I��`�揈���֐�.
//=========================================.
void CMainStageWorkGhostBase::SelectRender()
{
	if (m_MoveFlag & SELECT_FLAG) {
		//�`�揈���֐�.
		m_pCAct_Selection->RenderSetting(m_mView, m_mProj, m_vCameraPos);
		m_pCAct_Selection->Render();
	}
}

//=========================================.
//		�̗̓A�C�R���`�揈���֐�.
//=========================================.
void CMainStageWorkGhostBase::StrengthIconRender()
{
	//�x�e���ȊO�\������.
	if (!(m_MoveFlag & REST_FLAG)) {
		m_pCGhostStrengthIcon->RenderSetting(m_mView, m_mProj, m_vCameraPos);
		m_pCGhostStrengthIcon->Render();
	}
}

//=========================================.
//		�I���X�V�����֐�.
//=========================================.
void CMainStageWorkGhostBase::SelectUpdate()
{
	m_bTutorialCommentAddFlag = false;

	//�̗͖����Ƃ��Ɏ����x�e����.
	if (m_fStrength <= 0.0f) {
		if (m_MoveFlag & SURPRISE_FLAG) {
			m_MoveFlag |= REST_FLAG;
			//�������s����~.	
			m_SurpriseFlag &= ~SURPRISE_ACT_FLAG;

			m_bLimitationRest = true;

			//�I��������I�������.
			if (m_pCAct_Selection->GetSelectFlag() == false) {
				//�������t���O����x�e�t���O��.
				m_MoveFlag &= ~SURPRISE_FLAG;
				
				//�������̋߂��ɂ���l�ԍ����폜�����֐�.		
				ClearNearHumanOfGhost();
				return;
			}
		}
	}

	if (m_MoveFlag & REST_FLAG && m_bLimitationRest == true) {
		RestAct();
	}

	//�I�𒆂̍s���t���O.
	if (m_bSelectFlag == true) {
		m_MoveFlag = SELECT_FLAG | SURPRISE_FLAG;
	}

	//�������̍s���I������.
	if (m_MoveFlag & SELECT_FLAG) {
		//�������̍��W�擾.
		m_pCAct_Selection->SetCharacterPos(m_vSurpriseBeforePos);
		//�s���I���X�V�����֐�.
		m_pCAct_Selection->UpDate();
		//�A�C�R���̕\��ύX.
		m_pCGhostIcon->SetSelectedFlag(true);

		//�I���������.
		if (m_bLimitationRest == true) {
			m_pCAct_Selection->SetCloseMoveFlag();
		}

		//�I������߂鏈��.
		if (m_pCAct_Selection->GetSelectFlag() == false) {
			//�I���I��.
			m_bSelectFlag = false;

			//�A�C�R���̕\��߂�.
			m_pCGhostIcon->SetSelectedFlag(false);

			//�S�Ẵt���O.
			unsigned int ACT_ALL_FLAG = m_pCAct_Selection->MOVE_FLAG | m_pCAct_Selection->REST_FLAG;
			if (m_pCAct_Selection->GetGhostActFlag() & ACT_ALL_FLAG) {
				//�I���I��(�I���t���O���~�낷).
				m_MoveFlag &= ~SELECT_FLAG;
				//�I����̍s��.
				m_MoveFlag |= SELECT_ACT_FLAG;


				//�`���[�g���A�����R�����g����₷�t���O.
				m_bTutorialCommentAddFlag = true;

				m_ActType = m_pCAct_Selection->GetGhostActFlag();
				if (m_ActType & m_pCAct_Selection->MOVE_FLAG) {
					m_bChangeGimmickSelect = true;
				}
				else {
					//�������t���O����x�e�t���O��.
					m_MoveFlag &= ~SURPRISE_FLAG;
					m_MoveFlag |= REST_FLAG;
					//�������s����~.	
					m_SurpriseFlag &= ~SURPRISE_ACT_FLAG;
				}

				return;
			}

			//������.
			m_MoveFlag = SURPRISE_FLAG;
		}
	}

	//�I����̍s�������֐�.
	if (m_MoveFlag & SELECT_ACT_FLAG) {
		SelectAfterActivity();
	}
}

//==========================================.
//		�������s�������߂鏈���֐�.
//==========================================.
void CMainStageWorkGhostBase::SurpriseActDecide()
{
	//�������x�e����.
	if (m_SurpriseFlag & SURPRISE_REST_FLAG) {
		const int FileNum			= static_cast<int>(CFileResource::enStatusCharaType::Ghost);							//�t�@�C���ԍ�.
		const int StrengthType		= m_pCGhostIcon->GetFaceType() + 4;														//�\��ԍ�.
		const int SurpriseRestMax	= static_cast<int>(m_pCFileResource->GetStatusNum(FileNum, m_GhostType, StrengthType));	//�����x�e���ԍő�l.

		if (m_SurpriseRestTime <= SurpriseRestMax) {
			m_SurpriseRestTime++;

			//�������̋߂��ɂ���l�ԍ����폜�����֐�.		
			ClearNearHumanOfGhost();

			return;
		}
		m_SurpriseRestTime = 0;
		m_SurpriseFlag &= ~SURPRISE_REST_FLAG;
	}

	//���������M�~�b�N�̏�ɂ��邩�ǂ����̏���.
	if (m_UseGimmickNum >= 0) {
		m_SurpriseFlag |= GIMMICK_TOP_FLAG;
	}

	if (!(m_SurpriseFlag & SURPRISE_ACT_FLAG)) {

		//���������M�~�b�N�̏�ɂ��Ȃ���ΏI��.
		if (!(m_SurpriseFlag & GIMMICK_TOP_FLAG)) {
			//�������̋߂��ɂ���l�ԍ����폜�����֐�.		
			ClearNearHumanOfGhost();
			return;
		}

		//�l���������̋߂��ɂ��邩�ǂ���.
		for (unsigned int human = 0; human < m_vHumanPos.size(); human++) {
			if (fabsf((m_vPos.x - 5.0f) - m_vHumanPos[human].x) < NEAR_SENTER_ADJUST) {
				m_SurpriseFlag |= HUMAN_NEAR_FLAG;
			}
		}

		//�l���߂��ɂ��Ȃ���ΏI��.
		if (!(m_SurpriseFlag & HUMAN_NEAR_FLAG)) {
			//�������̋߂��ɂ���l�ԍ����폜�����֐�.		
			ClearNearHumanOfGhost();
			return;
		}

		//������.
		m_SurpriseFlag = SURPRISE_ACT_FLAG;

		//�l�������ꏊ.
		m_vSurprisePos = m_vHumanPos[0];
		m_vSurprisePos.x = m_vPos.x - SURPRISE_POS_ADJUST;

	}

	//�������̋߂��ɂ���l�ԍ�.
	if (m_SurpriseFlag & SURPRISE_ACT_FLAG) {
		int NearHumanCnt = 0;	//�������̋߂��ɂ���l�J�E���g.
		if (m_bNowHumanSurprise == true) {
			for (unsigned int human = 0; human < m_vHumanPos.size(); human++) {
				if (fabsf((m_vPos.x - NEAR_SENTER_ADJUST) - m_vHumanPos[human].x) < NEAR_SENTER_ADJUST) {

					//�l�ԍ��ݒ�.
					if (static_cast<int>(m_NearHumanNum.size()) > NearHumanCnt) {
						if (m_NearHumanNum[NearHumanCnt] != human) {
							m_NearHumanNum[NearHumanCnt] = human;
						}
						NearHumanCnt++;
						continue;
					}

					m_NearHumanNum.push_back(human);
					NearHumanCnt++;
				}
			}
		}

		//�s�v�ȗv�f���ύX.
		if (static_cast<int>(m_NearHumanNum.size()) > NearHumanCnt) {
			m_NearHumanNum.erase(m_NearHumanNum.begin() + NearHumanCnt, m_NearHumanNum.end());
		}

	}

	return;
}

//==========================================.
//		�����������蔻�菈���֐�.
//==========================================.
HRESULT CMainStageWorkGhostBase::SurpriseHit()
{
	const int PEOPLE_NUM = 0;	//�l�̔ԍ�.
	const int GHOST_NUM = 1;	//�������̔ԍ�.

	//2�_�̒���.
	std::vector<float>	fLength(m_NearHumanNum.size());
	for (unsigned int human = 0; human < m_NearHumanNum.size(); human++) {

		//2�_�̒��S�Ԃ̋��������߂�.
		D3DXVECTOR3 vLength = m_vSurprisePos - m_vHumanPos[m_NearHumanNum[human]];
		//�����ɕϊ�.
		fLength[human] = D3DXVec3Length(&vLength);

		//�Փ˔���.
		if (fLength[human] <= m_pCHitSphere[PEOPLE_NUM]->m_Sphere.fRadius * HUMAN_HIT_SCALE + m_pCHitSphere[GHOST_NUM]->m_Sphere.fRadius * SURPRISE_HIT_SCALE) {
			//�������l�̏���.
			m_bHumanSurpriseFlag = true;
			m_SurpriseHumanNum = m_NearHumanNum[human];

			break;
		}

		m_bHumanSurpriseFlag = false;
		m_SurpriseHumanNum = NOT_SURPRISE_NUM;

	}

	return S_OK;
}

//==========================================.
//		�I����̍s�������֐�.
//==========================================.
void CMainStageWorkGhostBase::SelectAfterActivity()
{

	if (m_ActType & m_pCAct_Selection->MOVE_FLAG) {
		if (m_bChangeGimmickSelect == false) {

			//����������I��.
			m_SurpriseFlag &= ~SURPRISE_ACT_FLAG;
			m_MoveFlag &= ~SURPRISE_FLAG;

			//�I���~�߂鏈��.
			if (m_MoveFlag & SELECT_STOP_FLAG) {
				m_MoveFlag = SURPRISE_FLAG;
				m_ActType = 0;
				return;
			}

			if (m_MoveFlag & MOVE_FLAG) {
				//�������̋߂��ɂ���l�ԍ����폜�����֐�.		
				ClearNearHumanOfGhost();

				//�M�~�b�N�ړ������֐�.
				MoveGimmick();
			}
		}
		return;
	}

	if (m_MoveFlag & MOVE_FLAG) {
		//�������̋߂��ɂ���l�ԍ����폜�����֐�.		
		ClearNearHumanOfGhost();

		//�x�e�����֐�.
		RestAct();
	}

}

//===========================================.
//		�������A�C�R���X�V�����֐�.
//===========================================.
void CMainStageWorkGhostBase::GhostIconUpdate()
{
	//�x�e���̊�̕ύX�p.
	if (m_MoveFlag & REST_FLAG) {
		m_pCGhostIcon->SetRestFlag(true);
	}
	else {
		m_pCGhostIcon->SetRestFlag(false);
	}
	//�\������L�������W�ݒ�.
	m_pCGhostIcon->SetCharaPos(m_vPos);
	//�X�e�[�W�S�̃}�b�v�ݒ�.
	m_pCGhostIcon->SetStageMax(m_fStageMaxDistance);
	//�̗͐ݒ�.
	m_pCGhostIcon->SetStrength(m_fStrength);
	//�X�V�����֐�.
	m_pCGhostIcon->UpDate();

	//�I�΂�Ă���Ƃ�.
	if (m_bGhostSelectIcon == true) {
		m_pCGhostIcon->SetSelectingFlag();
	}
	m_bGhostSelectIcon = false;
}

//===========================================.
//		�̗̓A�C�R���X�V�����֐�.
//===========================================.
void CMainStageWorkGhostBase::StrengthIconUpdate()
{
	//���W.
	m_pCGhostStrengthIcon->SetCharacterPos(m_vStrengthIconPos);
	//�̗̓A�C�R��.
	m_pCGhostStrengthIcon->SetStrengthIcon(m_pCGhostIcon->GetFaceType());
	m_pCGhostStrengthIcon->UpDate();
}

//===========================================.
//		�x�e�����֐�.
//===========================================.
void CMainStageWorkGhostBase::RestAct()
{
	//�񕜏�������.
	if (m_RestFlag & REST_PREPARAT_FLAG) {
		//�񕜏����֐�.
		RestMove(&m_vMovePos.y, REST_MOVE_SPEED, REST_MOVE_MAX);
		RestMove(&m_vRot.x, REST_ROTATION_SPEED.x, REST_ROTATION_MAX.x);
		RestMove(&m_vRot.y, REST_ROTATION_SPEED.y, REST_ROTATION_MAX.y);

		//�x�e��.
		m_fScale -= REST_SCALE_SPEED;
		if (m_fScale <= REST_SCALE_MIN) {
			m_fScale = REST_SCALE_MIN;
			m_RestFlag = IN_REST_FLAG;
		}
	}

	//�񕜒�����.
	if (m_RestFlag & IN_REST_FLAG) {
		//��J�񕜑��x�̒���.
		float RecoverySpeed = 1.0f;
		if (m_bLimitationRest == true) {
			RecoverySpeed = 4.0f;
		}
		m_fStrength += m_fRecoverySpeed / RecoverySpeed;

		//����.
		if (m_fStrength >= m_fStrengthMax) {
			m_fStrength = m_fStrengthMax;;
			m_RestFlag = RESURRECTION_FLAG;
		}
	}

	//��������.
	if (m_RestFlag & RESURRECTION_FLAG) {
		//�x�e�ړ������֐�.
		Resurrection(&m_vMovePos.y, REST_MOVE_SPEED, 0.0f);
		Resurrection(&m_vRot.x, REST_ROTATION_SPEED.x, 0.0f);
		Resurrection(&m_vRot.y, REST_ROTATION_SPEED.y, 0.0f);
		m_fScale += REST_SCALE_SPEED;

		//���ɖ߂�.
		if (m_fScale > m_fScaleMax) {
			m_fScale = m_fScaleMax;
			m_MoveFlag = SURPRISE_FLAG;
			m_RestFlag = REST_PREPARAT_FLAG;
			m_ActType = 0;

			m_bLimitationRest = false;
		}

	}
}

//===========================================.
//		�M�~�b�N�ړ������֐�.
//===========================================.
void CMainStageWorkGhostBase::MoveGimmick()
{
	if (fabsf(m_vPos.x - m_vObjectiveGimmickPos.x) <= ADJUSTMENT_WIDTH) {
		m_vPos.x = m_vObjectiveGimmickPos.x;

		//����������.
		m_vPos.y -= UP_DOWN_SPEED;
		if (m_vPos.y <= m_fMoveFinishHight) {
			m_vPos.y = m_fMoveFinishHight;
		}

		//�p�x�߂�.
		float Rotation_Direction = m_vRot.y / fabsf(m_vRot.y);
		m_vRot.y -= ROT_SPEED * Rotation_Direction;
		if (fabsf(m_vRot.y) <= ROT_MIN_ADJUST) {
			m_vRot.y = ROT_MIN;
			//�������s���Ɉړ�.
			m_MoveFlag = SURPRISE_FLAG;
			m_ActType = 0;
		}
		return;
	}

	//�ړ�����.
	int MoveDirection = static_cast<int>((m_vObjectiveGimmickPos.x - m_vPos.x ) / fabsf(m_vObjectiveGimmickPos.x - m_vPos.x));

	//�p�x�ړ�.
	m_vRot.y -= ROT_SPEED * MoveDirection;
	if (fabsf(m_vRot.y) >= ROT_MAX) {
		m_vRot.y = -ROT_MAX * MoveDirection;
	}

	//���ړ�.
	m_vPos.x += m_fMoveSpeed * MoveDirection;

	//���V�����֐�.
	MoveUpDown();

	//�̗͌�������.
	m_fStrength -= MOVE_REDUCE_SPEED;
}

//=============================================.
//		�f�o�b�O�p���̕`�揈���֐�.
//=============================================.
void CMainStageWorkGhostBase::DebugHitSphereRender()
{
#ifdef _DEBUG
	if (m_NearHumanNum.size() > 0) {
		std::vector<D3DXVECTOR3> SpherePos;
		SpherePos.push_back(m_vHumanPos[m_NearHumanNum[0]]);
		SpherePos.push_back(D3DXVECTOR3(m_vPos.x - SURPRISE_POS_ADJUST, m_vHumanPos[m_NearHumanNum[0]].y, m_vHumanPos[m_NearHumanNum[0]].z));
		std::vector<float> SphereScale;
		SphereScale.push_back(HUMAN_HIT_SCALE);
		SphereScale.push_back(SURPRISE_HIT_SCALE);
		for (unsigned int sphere = 0; sphere < m_pCHitSphere.size(); sphere++) {
			m_pCHitSphere[sphere]->SetScale(SphereScale[sphere]);
			m_pCHitSphere[sphere]->SetPosition(SpherePos[sphere]);
			m_pCHitSphere[sphere]->Render(m_mView, m_mProj, m_vCameraPos, m_stLight);
		}
	}
#endif	//#ifdef _DEBUG.
}

//===========================================.
//		�x�e�ړ������֐�.
//===========================================.
void CMainStageWorkGhostBase::RestMove(float* pfVar, float fSpeed, float fMax)
{
	*pfVar += fSpeed;
	if (*pfVar >= fMax) {
		*pfVar = fMax;
	}
}

//===========================================.
//		�񕜏����֐�.
//===========================================.
void CMainStageWorkGhostBase::Resurrection(float* pfVar, float fSpeed, float fMin)
{
	*pfVar -= fSpeed;
	if (*pfVar <= fMin) {
		*pfVar = fMin;
	}
}

//============================================.
//		�ړ����x�ύX�����֐�.
//============================================.
void CMainStageWorkGhostBase::MoveSpeedChange()
{
	int StrengthType = m_pCGhostIcon->GetFaceType();

	//�̗̓^�C�v����������.
	if (StrengthType < m_OldStrengthType) {
		m_fMoveSpeed -= m_fMoveSpeedMax / m_pCGhostIcon->STRENGTH_FACE_MAX;
	}

	//�̗͉�.
	if (StrengthType > m_OldStrengthType) {
		m_fMoveSpeed = m_fMoveSpeedMax;
	}

	m_OldStrengthType = StrengthType;
}

//============================================.
//		�ړ��X�V�����֐�.
//============================================.
void CMainStageWorkGhostBase::MovePosReference()
{
	//�������Ă���Ƃ��ȊO�ꏊ�X�V.
	if (!(m_SurpriseFlag & SURPRISE_ACT_FLAG) &&
		m_MoveFlag & MOVE_FLAG) {
		m_vMovePos = m_vPos;
	}
}

//============================================.
//		��J�G�t�F�N�g�X�V�����֐�.
//============================================.
void CMainStageWorkGhostBase::UpdateFutigueEffect()
{
	//��J�̕\���ޔԍ�.
	const int FutigueEffectFaceType = static_cast<int>(CGhostIcon::enFaceType::Bad_Face);

	//��J�G�t�F�N�g�X�V����.
	if ((m_pCGhostIcon->GetFaceType() == FutigueEffectFaceType) && !(m_ActType & REST_FLAG)) {
		m_pCFatigue->SetCenterPos(m_vEffectCenterPos); {
			if (m_pCFatigue->GetDispFlag() == false && !(m_SurpriseFlag & SURPRISE_ACT_FLAG))
				m_pCFatigue->SetDispFlag(true);
		}
		m_pCFatigue->Update();
		return;
	}

	if (m_pCFatigue->GetDispFlag() == true) {
		m_pCFatigue->SetDispFlag(false);
	}
}

//=============================================.
//	�������̋߂��ɂ���l�ԍ����폜�����֐�.
//=============================================.
void CMainStageWorkGhostBase::ClearNearHumanOfGhost()
{
	if (m_NearHumanNum.size() > 0) {
		m_NearHumanNum.clear();
	}
}