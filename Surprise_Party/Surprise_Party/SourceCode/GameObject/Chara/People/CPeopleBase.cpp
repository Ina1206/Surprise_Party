#include "CPeopleBase.h"

CPeopleBase::CPeopleBase()
	: m_pCSkinMesh		(nullptr)
	, m_fAnimSpeed		(0.0f)
	, m_fWalkAnimSpeed	(0.0f)
	, m_fStageMax		(0.0f)
	, m_fMoveSpeed		(0.0f)
	, m_SurpriseQuantity(0)
	, m_pAnimCtrl		(nullptr)
	, m_bSurpriseFlag	(false)
	, m_AnimNo			(0)
	, m_WalkAnimNo		(0)
	, m_SurpriseActFlag	(0)
	, m_AnimTime		(0.0)
	, m_HumanNearNum	(FAR_NUM)
	, m_SurpriseHumanMax(0)
{
	m_vRot = PERSON_ROT;
}

CPeopleBase::~CPeopleBase()
{
	if (m_pAnimCtrl != nullptr) {
		m_pAnimCtrl->Release();
		m_pAnimCtrl = nullptr;
	}
}

//======================================.
//		�`�揈���֐�.
//======================================.
void CPeopleBase::Render()
{
	//���W.
	m_pCSkinMesh->SetPosition(m_vPos);
	//�p�x.
	m_pCSkinMesh->SetRotation(m_vRot);
	//�傫��.
	m_pCSkinMesh->SetScale(m_fScale);
	//�A�j���[�V�������x.
	if (m_AnimNo == m_WalkAnimNo) {
		m_pCSkinMesh->SetAnimSpeed(m_fWalkAnimSpeed);
	}
	else {
		m_pCSkinMesh->SetAnimSpeed(m_fAnimSpeed);
	}
	//�`��.
	m_pCSkinMesh->Render(m_mView, m_mProj, m_vLightPos, m_vCameraPos, m_pAnimCtrl);
}

//======================================.
//		�ǉ��|�C���g�ʊl�������֐�.
//======================================.
int CPeopleBase::GetAddPointQuantity(int NearNo)
{
	//�����s�����Ă���Ƃ��ɂ̓|�C���g�͉��Z���Ȃ�.
	if (m_bSurpriseFlag == true) {
		return 0;
	}

	int m_AddPointQuantity;	//�ǉ��|�C���g��.
	m_AddPointQuantity = m_SurpriseQuantity - (NearNo * DECREMENT_POINT);

	if (m_AddPointQuantity < 0) {
		return 0;
	}

	return m_AddPointQuantity;
}

//======================================.
//		�\�����菈���֐�.
//======================================.
void CPeopleBase::DispDecision()
{
	if (m_vPos.x > m_fStageMax) {
		m_bDisp = false;
	}
}

//=======================================.
//	�A�j���[�V�����R���g���[���쐬�����֐�.
//=======================================.
void CPeopleBase::AnimCtrlCreat() 
{
	LPD3DXANIMATIONCONTROLLER pAC = m_pCSkinMesh->GetAnimationController();

	if (FAILED(pAC->CloneAnimationController(
		pAC->GetMaxNumAnimationOutputs(),
		pAC->GetMaxNumAnimationSets(),
		pAC->GetMaxNumTracks(),
		pAC->GetMaxNumEvents(),
		&m_pAnimCtrl))) {
		_ASSERT_EXPR(false, L"�A�j���[�V�����R���g���[���̃N���[���쐬���s");
	}
}

//========================================.
//		�l�̈ړ������֐�.
//========================================.
void CPeopleBase::HumanMove()
{
	if (m_AnimNo == m_WalkAnimNo) {
		m_vPos.x += m_fMoveSpeed;
	}

}

//========================================.
//		�����A�j���[�V�����ύX�����֐�.
//========================================.
void CPeopleBase::SurpriseAnimChange(int surpriseAnimNo)
{
	if (m_SurpriseActFlag != 0) {
		//�����s���I������.
		if (m_bSurpriseFlag == false) {
			m_SurpriseActFlag &= ~SURPRISE_ACT;
			return;
		}
	}

	//�����A�j���[�V�����ύX����.
	if ( m_bSurpriseFlag == true && m_SurpriseActFlag == 0) {
		m_AnimNo = surpriseAnimNo;
		m_pCSkinMesh->ChangeAnimSet(m_AnimNo, m_pAnimCtrl);
		m_AnimTime = 0.0;
		m_SurpriseActFlag = SURPRISE_ACT;
	}

	if (m_SurpriseActFlag & SURPRISE_ACT) {
		//�����A�j���[�V�����ύX.
		if (m_pCSkinMesh->GetAnimPeriod(m_AnimNo) - m_pCSkinMesh->GetAnimSpeed() <= m_AnimTime) {
			m_AnimNo = m_WalkAnimNo;
			m_pCSkinMesh->ChangeAnimSet(m_AnimNo, m_pAnimCtrl);
			m_AnimTime = 0.0;
			m_bSurpriseFlag = false;

			//���x���������֐�.
			SpeedAcceleration();
			return;
		}
	}

	m_AnimTime += m_pCSkinMesh->GetAnimSpeed();
}

//===========================================.
//		���x���������֐�.
//===========================================.
void CPeopleBase::SpeedAcceleration()
{
	//���������Ԃɂ���Ĉړ����x�ƃA�j���[�V�������x�̒ǉ��v�Z.
	m_fMoveSpeed += (m_SurpriseHumanMax - m_HumanNearNum) * ACCELERATION_SPEED;
	m_fWalkAnimSpeed += (m_SurpriseHumanMax - m_HumanNearNum) * ADD_ANIM_SPEED;

	//�����ɐl������ԍ��ɖ߂�.
	m_HumanNearNum = FAR_NUM;
}
