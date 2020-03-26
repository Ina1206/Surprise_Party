#include "CBoy.h"

CBoy::CBoy()
{
	//�����������֐�.
	Init();
}

CBoy::~CBoy()
{
	//��������֐�.
	Release();
}

//===================================.
//		�X�V�����֐�.
//===================================.
void CBoy::Update()
{
	//�\�����菈���֐�.
	DispDecision();

	//�l�̈ړ������֐�.
	HumanMove();

	//�����A�j���[�V�����ύX�����֐�.
	SurpriseAnimChange(static_cast<int>(enBoyAnim::Surprise));

	//�����G�t�F�N�g�X�V�����֐�.
	m_pCSkinMesh->GetPosFromBone("towa_rig_atama1", &m_vEffectCenterPos);
	m_pCSurpriseEffect->Update();

}

//===================================.
//		�����������֐�.
//===================================.
void CBoy::Init()
{
	//�X�L�����b�V���̃A�h���X�擾.
	m_pCSkinMesh = m_pCResourceManager->GetSkinMesh(enSkinMeshType::Boy);
	//�A�j���[�V�����R���g���[���̃N���[���쐬�����֐�.
	AnimCtrlCreat();
	//�A�j���[�V����.
	m_fAnimSpeed		= BASE_ANIM_SPEED;
	m_fWalkAnimSpeed	= m_fAnimSpeed;
	m_WalkAnimNo		= static_cast<int>(enBoyAnim::Walk);
	m_AnimNo			= m_WalkAnimNo;
	m_pCSkinMesh->ChangeAnimSet(m_AnimNo, m_pAnimCtrl);

	m_fScale = SCALE;

	//�X�e�[�^�X���l�擾.
	m_fMoveSpeed		= m_pCFileResource->GetStatusNum(static_cast<int>(enCharacterType::Human), static_cast<int>(enHumanType::Boy), static_cast<int>(enStatus::MoveSpeed));
	m_SurpriseQuantity	= static_cast<int>(m_pCFileResource->GetStatusNum(static_cast<int>(enCharacterType::Human), static_cast<int>(enHumanType::Boy), static_cast<int>(enStatus::Scared)));

	//�A�j���[�V�����ݒ�.
	m_AnimNo = static_cast<int>(enBoyAnim::Walk);
	m_pCSkinMesh->ChangeAnimSet(m_AnimNo, m_pAnimCtrl);

	//�����G�t�F�N�g�N���X�C���X�^���X��.
	m_pCSurpriseEffect.reset(new CSurpriseEffect());
}

//===================================.
//		��������֐�.
//===================================.
void CBoy::Release()
{
	m_pCSkinMesh = nullptr;
}