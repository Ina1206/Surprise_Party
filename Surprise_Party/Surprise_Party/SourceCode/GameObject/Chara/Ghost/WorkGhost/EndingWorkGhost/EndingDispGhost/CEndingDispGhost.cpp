#include "CEndingDispGhost.h"

/******************************************
*	�G���f�B���O�̌���邨�����N���X.
**************/
CEndingDispGhost::CEndingDispGhost()
	: m_RotationDirect			(1)
	, m_bChangeRotationDirect	(false)
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

	if (m_EmotionNum == static_cast<int>(enEmotionType::Rejoice)) {
		ActRejoiceEmotion();
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
	
}

//===========================================.
//		�����������֐�.
//===========================================.
void CEndingDispGhost::Init()
{
	//�A�j���[�V���������������֐�.
	InitAnimation();
	m_fScale = SCALE;
	m_vPrePos.y = PRE_POS_Y;

	m_fAcc = ACC_MAX;
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
	m_fAcc -= ACC_SPEED;
	m_vPos.y += m_fAcc - GRAVITY;

	m_vRot.z += ROTATION_SPEED * m_RotationDirect;

	if (m_vPos.y < m_vChangeBeforePos.y) {
		m_vPos = m_vChangeBeforePos;
		m_bChangeRotationDirect = false;
		m_fAcc = ACC_MAX;
		m_vRot.x = 0.0f;
	}

	if (m_bChangeRotationDirect == true) {
		return;
	}

	//������悤�ɂȂ�Ɗp�x�ύX.
	if (m_fAcc < GRAVITY) {
		m_RotationDirect *= CHANGE_DIRECT;
		m_bChangeRotationDirect = true;
	}

}