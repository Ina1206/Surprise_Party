#include "CEndingDispGhost.h"

/******************************************
*	�G���f�B���O�̌���邨�����N���X.
**************/
CEndingDispGhost::CEndingDispGhost()
	: m_RotationDirect			(1)
	, m_bChangeRotationDirect	(false)
	, m_bStartHaveTrouble		(false)
{
	//�����������֐�.
	Init();
}

CEndingDispGhost::~CEndingDispGhost()
{

}

//===========================================.
//		�X�V�����֐�.
//===========================================.
void CEndingDispGhost::Update()
{
	//�G�t�F�N�g�ύX�����֐�.
	ChangeEffect();

	if (m_pCSpriteEffect != nullptr) {
		//�G�t�F�N�g�X�V�����֐�.
		m_pCSpriteEffect->SetCenterPos(m_vPos);
		m_pCSpriteEffect->Update();
	}

	if (m_EmotionNum == static_cast<int>(enEmotionType::Rejoice)) {
		//��ъ���s�������֐�.
		ActRejoiceEmotion();
		return;
	}

	if (m_EmotionNum == static_cast<int>(enEmotionType::GoodFeeling)) {
		//�㉺�ړ������֐�.
		MoveUpDown();

		//���@�����̍s�������֐�.
		ActGoodFeeling();

		//�G�t�F�N�g�Đ��Ǘ������֐�.
		PlayEffectManager();

		return;
	}

	if (m_EmotionNum == static_cast<int>(enEmotionType::HaveTrounble)) {
		//����������s�������֐�.
		ActHaveTrouble();

		m_pCSpriteEffect->SetPlayFlag(true);
		return;
	}

	//�ړ��p�x�����֐�.
	MoveRotation(m_vPos, m_vLookAtPos);
	m_vChangeBeforePos = m_vPos;
}

//===========================================.
//		�`�揈���֐�.
//===========================================.
void CEndingDispGhost::Render()
{
	m_pCSkinMesh->ChangeAnimSet_StartPos(0, WAIT_ANIM_START_POS, m_pAnimCtrl);
	RenderDispGhost(m_vPos);
	
	//�X�v���C�g�G�t�F�N�g�`�揈��.
	if (m_pCSpriteEffect != nullptr) {
		m_pCSpriteEffect->Render(m_mView, m_mProj, m_vCameraPos);
	}
}

//===========================================.
//		�����������֐�.
//===========================================.
void CEndingDispGhost::Init()
{
	//�A�j���[�V���������������֐�.
	InitAnimation();
	m_fScale	= SCALE;
	m_vPrePos.y = PRE_POS_Y;

	//�W�����v��������.
	m_fAccMax	= ACC_MAX;
	m_fAcc		= m_fAccMax;
	m_fAccSpeed = ACC_SPEED;
	m_fGravity	= GRAVITY;
}

//============================================.
//		��������֐�.
//============================================.
void CEndingDispGhost::Release()
{

}

//============================================.
//		��ъ���s�������֐�.
//============================================.
void CEndingDispGhost::ActRejoiceEmotion()
{
	//�W�����v�����֐�.
	Jump();

	//��]�����֐�.
	Rotation();
}

//=============================================.
//		��]�����֐�.
//=============================================.
void CEndingDispGhost::Rotation()
{
	m_vRot.z += ROTATION_SPEED * m_RotationDirect;

	if (m_vPos.y <= m_vChangeBeforePos.y) {
		m_bChangeRotationDirect = false;
		m_vRot.x = 0.0f;
	}

	//��x�ύX������オ��܂ŏ��������Ȃ�.
	if (m_bChangeRotationDirect == true) {
		return;
	}

	//������悤�ɂȂ�Ɗp�x�ύX.
	if (m_fAcc < GRAVITY) {
		m_RotationDirect *= CHANGE_DIRECT;
		m_bChangeRotationDirect = true;
	}

}

//==============================================.
//		����������s�������֐�.
//==============================================.
void CEndingDispGhost::ActHaveTrouble()
{
	if (m_bStartHaveTrouble == false) {
		//�ړ��p�x�����֐�.
		MoveRotation(m_vPos, m_vLookAtPos);
		m_vChangeBeforeRotation = m_vRot;
		m_bStartHaveTrouble		= true;
	}

	m_vRot.x += SWING_SPEED * m_RotationDirect;
	
	//�p�x�ő�l.
	if (fabsf(m_vRot.x - m_vChangeBeforeRotation.x) > static_cast<float>(D3DXToRadian(SWING_ROTATION_MAX))) {
		m_RotationDirect *= CHANGE_DIRECT;
	}
}