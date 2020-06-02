#include "CWorkGhostBase.h"

CWorkGhostBase::CWorkGhostBase()
	: m_pCSkinMesh	(nullptr)
	, m_pAnimCtrl	(nullptr)

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

	m_fScale = 0.15f;

}

//========================================.
//		����邨�����`�揈���֐�.
//========================================.
void CWorkGhostBase::RenderDispGhost(const D3DXVECTOR3& vPos)
{
	//���W.
	m_pCSkinMesh->SetPosition(vPos);
	//�傫��.
	m_pCSkinMesh->SetScale(m_fScale);
	//�p�x.
	m_pCSkinMesh->SetRotation(m_vRot);
	//�`��.
	m_pCSkinMesh->Render(m_mView, m_mProj, m_vCameraPos, m_stLight, m_pAnimCtrl);
}