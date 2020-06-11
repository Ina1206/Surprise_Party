#include "CEndingDispGhost.h"

/******************************************
*	�G���f�B���O�̌���邨�����N���X.
**************/
CEndingDispGhost::CEndingDispGhost()
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
	//�ړ��p�x�����֐�.
	MoveRotation(m_vPos, m_vLookAtPos);
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
	m_fScale = 0.07f;
	m_vPrePos.y = -20.0f;

	//�ړ��p�x�����֐�.
	MoveRotation(m_vPos, m_vLookAtPos);
}

//============================================.
//		��������֐�.
//============================================.
void CEndingDispGhost::Release()
{

}