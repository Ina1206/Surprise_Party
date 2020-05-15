#include "CPlaySoundSwitch.h"

CPlaySoundSwitch::CPlaySoundSwitch()
	: m_pCMoveNoteEffect	(nullptr)
{
	//�����������֐�.
	Init();
}

CPlaySoundSwitch::~CPlaySoundSwitch()
{
	//��������֐�.
	Release();
}


//=======================================.
//		�X�V�����֐�.
//=======================================.
void CPlaySoundSwitch::Update()
{
	//�X�C�b�`�̉��s���W�ݒ�.
	m_vPos.z = SWITCH_DEPTH_POS;

	//�G�t�F�N�g�X�V�����֐�.
	EffectUpdate();

	for (unsigned int Effect = 0; Effect < m_pCSpriteEffect.size(); Effect++) {
		const D3DXVECTOR3 vEffectCenterPos = m_vPos + D3DXVECTOR3(0.0f, 0.0f, 8.0f);
		m_pCSpriteEffect[Effect]->SetCenterPos(vEffectCenterPos);
		m_pCSpriteEffect[Effect]->SetPlayFlag(m_bMoveObjectEffect);
		m_pCSpriteEffect[Effect]->Update();
	}
}

//=======================================.
//		�����������֐�.
//=======================================.
void CPlaySoundSwitch::Init()
{
	//���b�V���A�h���X�擾����.
	m_pCMesh = m_pCResourceManager->GetStaticMesh(enStaticMeshType::PlaySoundSwitch);
	m_fScale = 0.2f;

	//�G�t�F�N�g�A�h���X�擾�����֐�.
	m_pCEffect = m_pCResourceManager->GetEffect(CResourceEffect::enEffect::PlaySound_Area_Effect);
	
	//�����ړ��G�t�F�N�g�N���X�C���X�^���X��.
	m_pCSpriteEffect.emplace_back(new CMoveNoteEffect());
}

//=======================================.
//		��������֐�.
//=======================================.
void CPlaySoundSwitch::Release()
{
	m_pCEffect = nullptr;
	m_pCMesh = nullptr;
}