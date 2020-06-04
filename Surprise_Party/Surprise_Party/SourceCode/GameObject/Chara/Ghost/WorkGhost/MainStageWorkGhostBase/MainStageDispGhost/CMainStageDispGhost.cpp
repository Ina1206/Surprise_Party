#include "CMainStageDispGhost.h"

/***********************************************
*		���C���X�e�[�W�̌���邨�����N���X.
******************/
CMainStageDispGhost::CMainStageDispGhost()
	: m_fAnimSpeed		(0.0f)
	, m_SurpriseActFlag	(0)
	, m_dAnimTime		(0.0)
{
	//�����������֐�.
	Init();
}

CMainStageDispGhost::~CMainStageDispGhost()
{
	//��������֐�.
	Release();
}

//=================================.
//		�X�V�����֐�.
//=================================.
void CMainStageDispGhost::Update()
{
	//�I���X�V�����֐�.
	SelectUpdate();

	//�������A�C�R���X�V�����֐�.
	GhostIconUpdate();

	//�������̗̓A�C�R���X�V�����֐�.
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
	else {
		//�����ɖ߂�.
		m_SurpriseActFlag = APPEAR_FLAG;
		m_dAnimTime = 0.0;
		//�G��͏グ�Ƃ�.
		m_UpDownObjectFlag = UP_FLAG;
	}

	//�ړ��X�V�����֐�.
	MovePosReference();

	if (!(m_MoveFlag & SURPRISE_FLAG)) {
		if (m_bChangeGimmickSelect == false) {
			ReturnMove();
		}
	}

	//��J�G�t�F�N�g�X�V�����֐�.
	m_pCSkinMesh->GetPosFromBone("gost_b_joint4", &m_vEffectCenterPos);
	m_vEffectCenterPos.y += 1.5f;
	UpdateFutigueEffect();

	//�I���X�v���C�g�\�����W�ݒ�.
	m_vSurpriseBeforePos = m_vPos;
	//�̗̓A�C�R�����W�ݒ�.
	m_vStrengthIconPos = m_vMovePos;

}

//=================================.
//		�`�揈���֐�.
//=================================.
void CMainStageDispGhost::Render()
{
	if (fabsf(m_vCameraPos.x - m_vPos.x) < CAMERA_DISP_RANGE) {
		if (!(m_RestFlag & IN_REST_FLAG)) {
			//�A�j���[�V�������x.
			if (m_SurpriseFlag & SURPRISE_ACT_FLAG) {
				m_pCSkinMesh->SetAnimSpeed(m_fAnimSpeed);
			}
			else {
				m_pCSkinMesh->ChangeAnimSet_StartPos(0, WAIT_ANIM_START_POS, m_pAnimCtrl);
			}

			RenderDispGhost(m_vMovePos);
			////���W.
			//m_pCSkinMesh->SetPosition(m_vMovePos);
			////�傫��.
			//m_pCSkinMesh->SetScale(m_fScale);
			////�p�x.
			//m_pCSkinMesh->SetRotation(m_vRot);
			////�`��.
			//m_pCSkinMesh->Render(m_mView, m_mProj, m_vCameraPos, m_stLight, m_pAnimCtrl);
		}
	}


	//�������A�C�R���`�揈���֐�.
	m_pCGhostIcon->Render();


	//�f�o�b�O�p���̕`�揈���֐�.
	DebugHitSphereRender();

	//��J�G�t�F�N�g�`��.
	m_pCFatigue->Render(m_mView, m_mProj, m_vCameraPos);

}

//=================================.
//		�����������֐�.
//=================================.
void CMainStageDispGhost::Init()
{
	////�X�L�����b�V���̃A�h���X�擾.
	//m_pCSkinMesh = m_pCResourceManager->GetSkinMesh(enSkinMeshType::DispGhost);

	////�A�j���[�V�����R���g���[���̃N���[���쐬.
	//LPD3DXANIMATIONCONTROLLER	pAC = m_pCSkinMesh->GetAnimationController();
	//if (FAILED(pAC->CloneAnimationController(
	//	pAC->GetMaxNumAnimationOutputs(),
	//	pAC->GetMaxNumAnimationSets(),
	//	pAC->GetMaxNumTracks(),
	//	pAC->GetMaxNumEvents(),
	//	&m_pAnimCtrl))) {
	//	_ASSERT_EXPR(false, L"����邨�����̃A�j���[�V�����R���g���[���̃N���[���쐬���s");
	//}

	m_fScale = 0.15f;

	//�A�j���[�V���������������֐�.
	InitAnimation();

	m_fScaleMax = m_fScale;

	m_fAnimSpeed = SURPRISE_ANIM_SPEED;

	//�̗�.
	m_fStrength = m_pCFileResource->GetStatusNum(static_cast<int>(enCharacterType::Ghost), static_cast<int>(enGhostType::DispGhost), static_cast<int>(enStatus::Strength));
	m_fStrengthMax = m_fStrength;
	//���x.
	m_fMoveSpeed = m_pCFileResource->GetStatusNum(static_cast<int>(enCharacterType::Ghost), static_cast<int>(enGhostType::DispGhost), static_cast<int>(enStatus::MoveSpeed));
	m_fMoveSpeedMax = m_fMoveSpeed;
	//�񕜑��x.
	m_fRecoverySpeed = m_pCFileResource->GetStatusNum(static_cast<int>(enCharacterType::Ghost), static_cast<int>(enGhostType::DispGhost), static_cast<int>(enStatus::RecoverySpeed));

	//�s���I���N���X�C���X�^���X��.
	m_pCAct_Selection.reset(new CAct_Selection());

	//�������A�C�R���C���X�^���X��.
	m_pCGhostIcon.reset(new CGhostIcon());
	m_pCGhostIcon->SetColor(D3DXVECTOR3(1.0f, 195.0f / 255.0f, 201.0f / 255.0f));
	m_pCGhostIcon->SetStrengthMax(m_fStrengthMax);

	//�������I�u�W�F�N�g��ސݒ�.
	m_enSurpriseObjectType = enSurpriseObjectType::Disp;

	//�������s���t���O.
	m_SurpriseActFlag = APPEAR_FLAG;

	//�ړ��I����̍���.
	m_fMoveFinishHight = HIGHT_MIN;
}

//==================================.
//		��������֐�.
//==================================.
void CMainStageDispGhost::Release()
{
	m_pCSkinMesh = nullptr;
}

//==================================.
//		�������s�������֐�.
//==================================.
void CMainStageDispGhost::SurpriseAct()
{
	//�������Ɍ���鏈��.
	if (m_SurpriseActFlag & APPEAR_FLAG) {
		m_vMovePos.z -= APPEAR_SPEED;
		if (m_vMovePos.z <= APPEAR_POS_MAX) {
			m_vMovePos.z = APPEAR_POS_MAX;

			//�͈͓��̐l�������t���O.
			m_bNowHumanSurprise = true;
		}

		//�߂鏈���ɕύX����.
		if (m_dAnimTime >= RETURN_ANIM_TIME) {
			m_SurpriseActFlag = RETURN_FLAG;
			m_bNowHumanSurprise = false;
		}
	}

	//�߂鏈��.
	if (m_SurpriseActFlag & RETURN_FLAG) {
		m_vMovePos.z += RETURN_SPEED;
		if (m_vMovePos.z >= RETURN_POS_MAX) {
			m_vMovePos.z = RETURN_POS_MAX	;
		}

		//�������s���I������.
		if (m_dAnimTime >= WAIT_ANIM_TIME) {
			//�����ɖ߂�.
			m_SurpriseActFlag = APPEAR_FLAG;
			m_dAnimTime = 0.0;
			//�����s���t���O���~�낷.
			m_SurpriseFlag &= ~SURPRISE_ACT_FLAG;

			m_SurpriseFlag |= SURPRISE_REST_FLAG;
		}
	}

	//�A�j���[�V�������x���Z.
	m_dAnimTime += m_pCSkinMesh->GetAnimSpeed();
	//�̗͌�������.
	m_fStrength -= BASIC_REDUCE_SPEED;
}

//==================================.
//		�㉺�ړ��ύX�����֐�.
//==================================.
void CMainStageDispGhost::ChangeObjectUpDown()
{
	//������.
	if (m_vMovePos.z <= OBJECT_DOWN_POS) {
		m_UpDownObjectFlag = DOWN_FLAG;
		return;
	}

	//�グ��.
	m_UpDownObjectFlag = UP_FLAG;
}

//==================================.
//		�߂�ړ������֐�.
//==================================.
void CMainStageDispGhost::ReturnMove()
{
	if (m_vMovePos.z < GHOST_POS_Z) {
		m_vMovePos.z += RETURN_SPEED;
		return;
	}

	//�ړ��t���O.
	m_MoveFlag |= MOVE_FLAG;
}