#include "CEndingSwitchGhost.h"

/*******************************************
*		�G���f�B���O�X�C�b�`�������N���X.
******************/
CEndingSwitchGhost::CEndingSwitchGhost()
{
	//�����������֐�.
	Init();
}

CEndingSwitchGhost::~CEndingSwitchGhost()
{
	//��������֐�.
	Release();
}

//===========================================.
//		�X�V�����֐�.
//===========================================.
void CEndingSwitchGhost::Update()
{
	//�ړ��p�x�����֐�.
	MoveRotation(m_vPos, m_vLookAtPos);

}

//===========================================.
//		�`�揈���֐�.
//===========================================.
void CEndingSwitchGhost::Render()
{
	//�X�C�b�`�������`�揈���֐�.
	RenderSwitchGhost(m_vPos);
}

//===========================================.
//		�����������֐�.
//===========================================.
void CEndingSwitchGhost::Init()
{
	//�ÓI�I�u�W�F�N�g�����������������֐�.
	InitStaticMeshGhost();

	m_fScale = SCALE;
	m_vPrePos.y = PRE_POS_Y;

}

//===========================================.
//		��������֐�.
//===========================================.
void CEndingSwitchGhost::Release()
{

}

//===========================================.
//		��ъ���s����������.
//===========================================.
void CEndingSwitchGhost::ActRejoiceEmotion()
{

}