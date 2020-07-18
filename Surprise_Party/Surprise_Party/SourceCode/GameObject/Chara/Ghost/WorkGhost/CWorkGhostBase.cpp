#include "CWorkGhostBase.h"

/*************************************
*		�������������N���X.
******/
CWorkGhostBase::CWorkGhostBase()
	: m_pCSkinMesh	(nullptr)
	, m_pAnimCtrl	(nullptr)
	, m_pCMesh		(nullptr)
{
}

CWorkGhostBase::~CWorkGhostBase()
{
}

//========================================.
//		�A�j���[�V���������������֐�.
//========================================.
void CWorkGhostBase::InitAnimation()
{
	//�X�L�����b�V���̃A�h���X�擾.
	m_pCSkinMesh = m_pCResourceManager->GetSkinMesh(enSkinMeshType::DispGhost);

	//�A�j���[�V�����R���g���[���̃N���[���쐬.
	LPD3DXANIMATIONCONTROLLER	pAC = m_pCSkinMesh->GetAnimationController();
	if (FAILED(pAC->CloneAnimationController(
		pAC->GetMaxNumAnimationOutputs(),
		pAC->GetMaxNumAnimationSets(),
		pAC->GetMaxNumTracks(),
		pAC->GetMaxNumEvents(),
		&m_pAnimCtrl))) {
		_ASSERT_EXPR(false, L"����邨�����̃A�j���[�V�����R���g���[���̃N���[���쐬���s");
	}


}

//========================================.
//		����邨�����`�揈���֐�.
//========================================.
void CWorkGhostBase::RenderDispGhost(const D3DXVECTOR3& vPos)
{
	//�A�j���[�V�������x.
	if (m_bPauseFlag == true) {
		m_pCSkinMesh->SetAnimSpeed(PAUSE_ANIM_SPEED);
	}

	//���W.
	m_pCSkinMesh->SetPosition(vPos);
	//�傫��.
	m_pCSkinMesh->SetScale(m_fScale);
	//�p�x.
	m_pCSkinMesh->SetRotation(m_vRot);
	//���߂̊p�x.
	m_pCSkinMesh->SetPrePos(m_vPrePos);
	//�`��.
	m_pCSkinMesh->Render(m_mView, m_mProj, m_vCameraPos, m_stLight, m_pAnimCtrl);
}

//=========================================.
//	�ÓI�I�u�W�F�N�g�����������������֐�.
//=========================================.
void CWorkGhostBase::InitStaticMeshGhost()
{
	//���b�V���̓ǂݍ��݃A�h���X�擾.
	m_pCMesh = m_pCResourceManager->GetStaticMesh(enStaticMeshType::SwitchPushGhost);
}

//=========================================.
//		�X�C�b�`�������`�揈���֐�.
//=========================================.
void CWorkGhostBase::RenderSwitchGhost(const D3DXVECTOR3& vPos)
{
	m_pCMesh->SetPosition(vPos);
	m_pCMesh->SetRotation(m_vRot);
	m_pCMesh->SetScale(m_fScale);
	m_pCMesh->SetPrePos(SWITCH_GHOST_PRE_POS);
	m_pCMesh->Render(m_mView, m_mProj, m_vCameraPos, m_stLight);

}