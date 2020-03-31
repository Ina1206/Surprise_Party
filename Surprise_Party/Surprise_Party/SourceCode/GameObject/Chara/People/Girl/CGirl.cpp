#include "CGirl.h"
#include <random>

CGirl::CGirl()
	: m_SuspendTime		(0)
	, m_dAnimTime		(0.0)
	, m_SuspendInterval	(0)
{
	//�����������֐�.
	Init();
}

CGirl::~CGirl()
{
	//��������֐�.
	Release();
}

//========================================.
//		�X�V�����֐�.
//========================================.
void CGirl::Update()
{
	//�\�����菈���֐�.
	DispDecision();

	//�l�̈ړ������֐�.
 	HumanMove();

	//�����A�j���[�V�����ύX�����֐�.
	SurpriseAnimChange(static_cast<int>(enGirlAnimType::Rejoice));

	//�ꎞ��~�����֐�.
	SearchMotion();

	if (m_AnimNo == static_cast<int>(enGirlAnimType::Rejoice)) {
		m_pCSurpriseEffect->SetDispFlag(true);
	}
	//�����G�t�F�N�g�X�V�����֐�.
	m_pCSurpriseEffect->Update();
	m_vEffectCenterPos = m_vPos;
	m_vEffectCenterPos.y += 4.0f;
}

//========================================.
//		�����������֐�.
//========================================.
void CGirl::Init()
{
	//�X�L�����b�V���̃A�h���X�擾����.
	m_pCSkinMesh = m_pCResourceManager->GetSkinMesh(enSkinMeshType::Girl);

	//�A�j���[�V�����R���g���[���̃N���[���쐬�����֐�.
	AnimCtrlCreat();
	//�A�j���[�V����.
	m_fAnimSpeed		= BASE_ANIM_SPEED;
	m_fWalkAnimSpeed	= m_fAnimSpeed;
	m_WalkAnimNo		= static_cast<int>(enGirlAnimType::Walk);
	m_AnimNo			= m_WalkAnimNo;
	m_pCSkinMesh->ChangeAnimSet(m_AnimNo, m_pAnimCtrl);

	m_fScale			= SCALE;

	//�X�e�[�^�X���l�擾.
	m_fMoveSpeed		= m_pCFileResource->GetStatusNum(static_cast<int>(enCharacterType::Human), static_cast<int>(enHumanType::Girl), static_cast<int>(enStatus::MoveSpeed));
	m_SurpriseQuantity	= static_cast<int>(m_pCFileResource->GetStatusNum(static_cast<int>(enCharacterType::Human), static_cast<int>(enHumanType::Girl), static_cast<int>(enStatus::Scared)));
	
	//�ꎞ��~�Ԋu�ݒ菈��.
	std::random_device rnd;
	std::mt19937 mt(rnd());
	std::uniform_int_distribution<> IntervalRand(SUSPEND_INTERVAL_TIME_MIN, SUSPEND_INRERVAL_TIME_MAX);
	m_SuspendInterval = IntervalRand(mt);
	
	//�����G�t�F�N�g�N���X�C���X�^���X��.
	m_pCSurpriseEffect.reset(new CSurpriseEffect());
}

//========================================.
//		��������֐�.
//========================================.
void CGirl::Release()
{
	m_pCSkinMesh = nullptr;
}

//=========================================.
//		�T�������֐�.
//=========================================.
void CGirl::SearchMotion()
{
	//�����Ă���Ƃ��͗�O�Ƃ��ď���.
	if (m_AnimNo == static_cast<int>(enGirlAnimType::Rejoice)) {
		return;	
	}

	if (m_AnimNo == static_cast<int>(enGirlAnimType::Walk)) {
		//�T���A�j���[�V�����ύX����.
		SearchAnimChange();
		return;
	}

	//�T�����Ă��Ȃ��Ƃ��͗�O�Ƃ��ď���.
	if (m_AnimNo != static_cast<int>(enGirlAnimType::Search)) {
		return;
	}

	//�������[�V�����֕ύX����.
	if (m_pCSkinMesh->GetAnimPeriod(m_AnimNo) - m_pCSkinMesh->GetAnimSpeed() <= m_dAnimTime) {
		m_AnimNo = static_cast<int>(enGirlAnimType::Walk);
		m_pCSkinMesh->ChangeAnimSet(m_AnimNo, m_pAnimCtrl);
		m_dAnimTime = 0.0;
	}

	m_dAnimTime += m_pCSkinMesh->GetAnimSpeed();
}

//============================================.
//		�T���A�j���[�V�����ύX�����֐�.
//============================================.
void CGirl::SearchAnimChange()
{
	if (m_SuspendTime >= m_SuspendInterval * SECONDS_DELIMITER) {
		m_AnimNo = static_cast<int>(enGirlAnimType::Search);
		m_pCSkinMesh->ChangeAnimSet(m_AnimNo, m_pAnimCtrl);
		m_SuspendTime = 0;
		m_dAnimTime = 0.0;
	}

	m_SuspendTime++;
}