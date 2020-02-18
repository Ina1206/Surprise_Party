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
void CGhostDispPainting::UpDate()
{
	//�G�t�F�N�g�X�V�����֐�.
	EffectUpDate();

	//�I�u�W�F�N�g���ߏ����֐�.
	ObjAlpha();

}

//=================================.
//		�����������֐�.
//=================================.
void CGhostDispPainting::Init()
{
	//�G��I�u�W�F�N�g�̓ǂݍ��݃A�h���X�擾.
	m_pCMesh = nullptr;
	m_pCMesh = m_pCResourceManager->GetStaticMesh(enStaticMeshType::Painting);
	m_fScale = 0.4f;

	//�G�t�F�N�g�̓ǂݍ��݃A�h���X�擾.
	m_pCEffect = m_pCResourceManager->GetEffect(CResourceEffect::enEffect::DispGhost_Area_Effect);
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
