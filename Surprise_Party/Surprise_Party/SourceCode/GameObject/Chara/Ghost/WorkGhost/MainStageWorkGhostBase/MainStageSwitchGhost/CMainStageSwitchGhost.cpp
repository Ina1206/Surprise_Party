#include "CMainStageSwitchGhost.h"

CMainStageSwitchGhost::CMainStageSwitchGhost()
	: m_PushSwitchActFlag	(0)
	, m_fGravity			(0.0f)
	, m_UpDownDirection		(-1)
	, m_vPointDistance		(0.0f, 0.0f, 0.0f)
	, m_vUnitVector			(0.0f, 0.0f, 0.0f)
	, m_vOldPos				(0.0f, 0.0f, 0.0f)
{
	//�����������֐�.
	Init();
}

CMainStageSwitchGhost::~CMainStageSwitchGhost()
{
	//��������֐�.
	Release();
}

//==================================.
//		�X�V�����֐�.
//==================================.
void CMainStageSwitchGhost::Update()
{

	//�I���X�V�����֐�.
	SelectUpdate();

	//�������A�C�R���X�V�����֐�.
	GhostIconUpdate();
	
	//�������̗̓A�C�R���X�V�֐�.
	StrengthIconUpdate();

	//�ړ����x�ύX�����֐�.
	MoveSpeedChange();

	if (m_MoveFlag & SURPRISE_FLAG) {
		//�������s�������߂鏈���֐�.
		SurpriseActDecide();

		if (m_SurpriseFlag & SURPRISE_ACT_FLAG) {

			//�����������蔻�菈���֐�.
			SurpriseHit();

			//�������s�������֐�.
			SurpriseAct();

			//�㉺�ړ��ύX�����֐�.
			ChangeObjectUpDown();
		}
	}


	//�ړ��X�V�����֐�.
	MovePosReference();

	if (!(m_MoveFlag & SURPRISE_FLAG)) {
		if (m_bChangeGimmickSelect == false) {
			if (m_PushSwitchActFlag == 0) {
				ReturnMove();
			}
			else {
				m_vPointDistance = m_vPos - m_vMovePos;
				float fLength = D3DXVec3Length(&m_vPointDistance);
				m_vUnitVector = m_vPointDistance / fLength;
				//������.
				m_PushSwitchActFlag = 0;
				m_fGravity = 0.0f;
				m_UpDownDirection = -1;
				//�p�x.
				m_vRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			}
		}
	}


	//��J�G�t�F�N�g�X�V�����֐�.
	m_vEffectCenterPos = m_vMovePos + D3DXVECTOR3(0.0f, 0.5f, 0.0f);
	UpdateFutigueEffect();

	m_vOldPos = m_vMovePos;
	m_vSurpriseBeforePos = m_vPos + D3DXVECTOR3(0.0f, -STANDERD_POS_HIGHT, 0.0f);
	m_vStrengthIconPos = m_vMovePos + D3DXVECTOR3(0.0f, -STANDERD_POS_HIGHT, 0.0f);
}

//==================================.
//		�`�揈���֐�.
//==================================.
void CMainStageSwitchGhost::Render()
{
	//�X�C�b�`�������`�揈���֐�.
	RenderSwitchGhost(m_vMovePos);

	//�������A�C�R���`��.
	m_pCGhostIcon->Render();

	//�f�o�b�O�p���̕`�揈���֐�.
	DebugHitSphereRender();

	
	//��J�G�t�F�N�g�`�揈��.
	if (m_pCFatigue->GetDispFlag() == true) {
		m_pCFatigue->Render(m_mView, m_mProj, m_vCameraPos);
	}
}

//==================================.
//		�����������֐�.
//==================================.
void CMainStageSwitchGhost::Init()
{
	//�ÓI�I�u�W�F�N�g�����������������֐�.
	InitStaticMeshGhost();

	m_fScale = SWITHC_GHOST_SCALE;
	m_fScaleMax = m_fScale;

	//�s���I���C���X�^���X��.
	m_pCAct_Selection.reset(new CAct_Selection());

	//�������I�u�W�F�N�g��ސݒ�.
	m_enSurpriseObjectType = enSurpriseObjectType::Switch;

	//�X�e�[�^�X�ݒ�.
	const int CHARA_TYPE = static_cast<int>(enCharacterType::Ghost);	//�L�����N�^�^�C�v.
	const int GHOST_TYPE = static_cast<int>(enGhostType::SwitchGhost);	//�������^�C�v.
	//�̗�.
	m_fStrength = m_pCFileResource->GetStatusNum(CHARA_TYPE, GHOST_TYPE, static_cast<int>(enStatus::Strength));
	m_fStrengthMax = m_fStrength;
	//�ړ����x.
	m_fMoveSpeed = m_pCFileResource->GetStatusNum(CHARA_TYPE, GHOST_TYPE, static_cast<int>(enStatus::MoveSpeed));
	m_fMoveSpeedMax = m_fMoveSpeed;
	//�񕜑��x.
	m_fRecoverySpeed = m_pCFileResource->GetStatusNum(CHARA_TYPE, GHOST_TYPE, static_cast<int>(enStatus::RecoverySpeed));

	//�}�b�v��ł̂������A�C�R���C���X�^���X��.
	m_pCGhostIcon.reset(new CGhostIcon());
	m_pCGhostIcon->SetColor(GHOST_COLOR / COLOR_MAX);
	m_pCGhostIcon->SetStrengthMax(m_fStrengthMax);

	//�ړ��I����̍���.
	m_fMoveFinishHight = STANDERD_POS_HIGHT;
}

//===================================.
//		��������֐�.
//===================================.
void CMainStageSwitchGhost::Release()
{
	m_pCMesh = nullptr;
}

//===================================.
//		�������s�������֐�.
//===================================.
void CMainStageSwitchGhost::SurpriseAct()
{
	if (m_PushSwitchActFlag == 0) {
		m_PushSwitchActFlag = PUSH_BUTTON_FLAG | GO_TO_PUSH_FLAG;
		return;
	}

	//�̗͂����炷.
	m_fStrength -= BASIC_REDUCE_SPEED;

	if (m_PushSwitchActFlag & GO_TO_PUSH_FLAG) {
		//�������������֐�.
		PushPreparation();
		return;
	}

	if (m_PushSwitchActFlag == PUSH_BUTTON_FLAG) {
		//���������֐�.
		PushButton();
		return;
	}

	//�߂鏀��.
	if (m_PushSwitchActFlag & PUSH_END_FLAG) {
		//����.
		m_vPointDistance = m_vPos - m_vMovePos;
		//����.
		float m_fLength = D3DXVec3Length(&m_vPointDistance);
		//�P�ʃx�N�g��.
		m_vUnitVector = m_vPointDistance / m_fLength;
		//�t���O.
		m_PushSwitchActFlag &= ~PUSH_END_FLAG;
		m_PushSwitchActFlag |= PUSH_RETURN_FLAG;
		//���ɖ߂�Ƃ��̊p�x.
		m_vRot.y = RETURN_ROTATION;
	}

	if (m_PushSwitchActFlag & PUSH_RETURN_FLAG) {
		//�����I����������֐�.
		PushEnd();

		m_bNowHumanSurprise = false;
	}
}

//===================================.
//		�㉺�ړ��ύX�����֐�.
//===================================.
void CMainStageSwitchGhost::ChangeObjectUpDown()
{
	if (m_vMovePos.y <= CHANGE_UP_DOWN_FLAG_H) {
		m_UpDownObjectFlag = DOWN_FLAG;
		return;
	}

	m_UpDownObjectFlag = UP_FLAG;
}

//===================================.
//		�߂�ړ������֐�.
//===================================.
void CMainStageSwitchGhost::ReturnMove()
{
	m_vMovePos += m_vUnitVector * MOVE_SPEED;

	if (fabsf(m_vPos.x - m_vMovePos.x) > DISTANCE_ADJUSTMENT) {
		//�ړ��p�x�����֐�.
		MoveRotation(m_vOldPos, m_vMovePos);
		m_vRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		return;
	}

	m_vMovePos = m_vPos;
	m_MoveFlag |= MOVE_FLAG;
}

//===================================.
//		�������������֐�.
//===================================.
void CMainStageSwitchGhost::PushPreparation()
{
	m_vMovePos.x += MOVE_SPEED;
	//�ړ��p�x�����֐�.
	MoveRotation(m_vOldPos, m_vMovePos);

	if (m_vMovePos.x - m_vPos.x > CHANGE_ACT_DISTANCE) {
		m_vMovePos.x = m_vPos.x + CHANGE_ACT_DISTANCE;
		m_PushSwitchActFlag &= ~GO_TO_PUSH_FLAG;
	}
}

//===================================.
//		���������֐�.
//===================================.
void CMainStageSwitchGhost::PushButton()
{
	m_fGravity -= GRAVITY * m_UpDownDirection;
	m_vMovePos.y += m_fGravity * m_UpDownDirection;

	m_vMovePos.x -= MOVE_SPEED;
	//�ړ��p�x�����֐�.
	MoveRotation(m_vOldPos, m_vMovePos);

	if (m_UpDownDirection == DOWN_DIRECTION) {
		//��ɏオ��悤�ɕύX.
		if (m_vMovePos.y <= POS_HEIGHT_MIN) {
			m_vMovePos.y = POS_HEIGHT_MIN;
			m_vMovePos.x = m_vPos.x;
			//�ړ������ύX.
			m_UpDownDirection *= CHANGE_DIRECTION;
			m_bNowHumanSurprise = true;
		}
		return;
	}

	//�����I��鏈���Ɉړ�.
	if (m_vMovePos.x < m_vPos.x - CHANGE_ACT_DISTANCE) {
		m_vMovePos.y = m_vPos.y;
		m_fGravity = 0.0f;
		m_UpDownDirection = DOWN_DIRECTION;
		m_PushSwitchActFlag |= PUSH_END_FLAG;
	}
}

//===================================.
//		�����I����������֐�.
//===================================.
void CMainStageSwitchGhost::PushEnd()
{
	if (fabsf(m_vPos.x - m_vMovePos.x) < DISTANCE_ADJUSTMENT) {
		m_vMovePos = m_vPos;

		m_vRot.y += PUSH_END_ROT_SPEED;
		if(m_vRot.y >= 0.0f){
			m_PushSwitchActFlag = 0;
			m_SurpriseFlag &= ~SURPRISE_ACT_FLAG;
			m_SurpriseFlag |= SURPRISE_REST_FLAG;
		}
		return;
	}
	m_vMovePos += MOVE_SPEED * m_vUnitVector;
	//�ړ��p�x�����֐�.
	MoveRotation(m_vOldPos, m_vMovePos);

}

