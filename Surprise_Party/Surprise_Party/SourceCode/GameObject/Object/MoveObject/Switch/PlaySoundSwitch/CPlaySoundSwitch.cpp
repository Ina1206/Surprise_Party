#include "CPlaySoundSwitch.h"

CPlaySoundSwitch::CPlaySoundSwitch()
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
void CPlaySoundSwitch::UpDate()
{
	//�X�C�b�`�̉��s���W�ݒ�.
	m_vPos.z = SWITCH_DEPTH_POS;

	//�G�t�F�N�g�X�V�����֐�.
	EffectUpDate();
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
}

//=======================================.
//		��������֐�.
//=======================================.
void CPlaySoundSwitch::Release()
{
	m_pCEffect = nullptr;
	m_pCMesh = nullptr;
}