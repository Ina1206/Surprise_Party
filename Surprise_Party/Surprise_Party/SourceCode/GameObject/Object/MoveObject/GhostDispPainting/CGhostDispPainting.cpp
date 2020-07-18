#include "CGhostDispPainting.h"

CGhostDispPainting::CGhostDispPainting()
{
	//�����������֐�.
	Init();
}

CGhostDispPainting::~CGhostDispPainting()
{
	//��������֐�.
	Release();
}

//=================================.
//		�X�V�����֐�.
//=================================.
void CGhostDispPainting::Update()
{
	//�G�t�F�N�g�X�V�����֐�.
	EffectUpdate();

	//�I�u�W�F�N�g���ߏ����֐�.
	ObjAlpha();

	//�X�v���C�g�G�t�F�N�g�ݒ�.
	const D3DXVECTOR3 vEffectCenterPos = D3DXVECTOR3(m_vPos.x, -1.0f, m_vPos.z);
	for (unsigned int sprite = 0; sprite < m_pCSpriteEffect.size(); sprite++) {
		m_pCSpriteEffect[sprite]->SetPlayFlag(m_bMoveObjectEffect);
		m_pCSpriteEffect[sprite]->SetCenterPos(vEffectCenterPos);
		m_pCSpriteEffect[sprite]->Update();
	}
}

//=================================.
//		�����������֐�.
//=================================.
void CGhostDispPainting::Init()
{
	//�G��I�u�W�F�N�g�̓ǂݍ��݃A�h���X�擾.
	m_pCMesh = nullptr;
	m_pCMesh = m_pCResourceManager->GetStaticMesh(enStaticMeshType::Painting);
	m_fScale = SCALE;

	//�G�t�F�N�g�̓ǂݍ��݃A�h���X�擾.
	m_pCEffect = m_pCResourceManager->GetEffect(CResourceEffect::enEffect::DispGhost_Area_Effect);

	//�X�v���C�g�G�t�F�N�g�C���X�^���X��.
	m_pCSpriteEffect.emplace_back(new CSmokeEffect());
}

//=================================.
//		��������֐�.
//=================================.
void CGhostDispPainting::Release()
{
	m_pCEffect = nullptr;
	m_pCMesh = nullptr;
}

//=================================.
//		�I�u�W�F�N�g���ߏ����֐�.
//=================================.
void CGhostDispPainting::ObjAlpha()
{
	if (fabsf(m_vCameraPos.x - m_vPos.x) <= ALPHA_DISTANCE) {
		m_fAlpha = PAINTING_ALPHA_MIN;
	}
	else {
		m_fAlpha = ALPHA_MAX;
	}
}
