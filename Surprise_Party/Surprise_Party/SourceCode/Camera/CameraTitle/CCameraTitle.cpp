#include "CCameraTitle.h"

/*******************************************
*		�^�C�g���J�����N���X.
*************/
CCameraTitle::CCameraTitle()
	: m_MoveTypeFlag	(0)
	, m_fMoveDistance	(0.0f)
	, m_fMoveSpeed		(0.0f)
{
	//�����������֐�.
	Init();
}

CCameraTitle::~CCameraTitle()
{
	//��������֐�.
	Release();
}

//==========================================.
//		�X�V�����֐�.
//==========================================.
void CCameraTitle::Update()
{
	m_fMoveDistance += m_fMoveSpeed;
	m_Camera.vPos.x += m_fMoveSpeed;
	m_Camera.vLook.x += m_fMoveSpeed;

	if (m_fMoveDistance >= MOVE_DISTANCE_MAX) {
		m_fMoveDistance = 0.0f;

		if (m_fMoveSpeed >= MOVE_SPEED_FROM_FRONT) {
			m_Camera.vPos = POS_FROM_OBLIQUE;
			m_Camera.vLook = LOOK_FROM_OBLIQUE;
			m_fMoveSpeed = MOVE_SPEED_FROM_OBLIQUE;
			return;
		}

		m_Camera.vPos = POS_FROM_FRONT;
		m_Camera.vLook = LOOK_FROM_FRONT;
		m_fMoveSpeed = MOVE_SPEED_FROM_FRONT;
	}
}

//==========================================.
//		�����������֐�.
//==========================================.
void CCameraTitle::Init()
{
	//m_Camera.vPos = D3DXVECTOR3(11.9f, 7.5f, -19.9f);
	m_Camera.vPos = POS_FROM_FRONT;
	m_Camera.vLook = LOOK_FROM_FRONT;
	m_fMoveSpeed = MOVE_SPEED_FROM_FRONT;
}

//==========================================.
//		��������֐�.
//==========================================.
void CCameraTitle::Release()
{

}