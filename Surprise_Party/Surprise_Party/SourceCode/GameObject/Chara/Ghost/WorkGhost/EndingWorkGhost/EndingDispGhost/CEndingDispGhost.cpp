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
	//ConvertRotationMatrixToQuaternion();
}

//===========================================.
//		�`�揈���֐�.
//===========================================.
void CEndingDispGhost::Render()
{
	m_pCSkinMesh->ChangeAnimSet_StartPos(0, WAIT_ANIM_START_POS, m_pAnimCtrl);
	MoveRotation(m_vPos, m_vLookAtPos);
	//D3DXQUATERNION a;
	//D3DXQuaternionRotationMatrix(&a, &m_mPoint);
	//m_vRot = D3DXVECTOR3(a.x, a.y, a.z);
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
}

//============================================.
//		��������֐�.
//============================================.
void CEndingDispGhost::Release()
{

}