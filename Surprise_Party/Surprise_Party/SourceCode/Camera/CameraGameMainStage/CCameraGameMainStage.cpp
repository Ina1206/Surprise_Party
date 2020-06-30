#include "CCameraGameMainStage.h"

/**********************************************
*		�Q�[�����C���X�e�[�W�̃J�����N���X.
**********************/
CCameraGameMainStage::CCameraGameMainStage()
{
	//�����������֐�.
	Init();
}

CCameraGameMainStage::~CCameraGameMainStage()
{
	//��������֐�.
	Release();
}

//================================================.
//		�X�V�����֐�.
//================================================.
void CCameraGameMainStage::Update()
{
	//�`���[�g���A�����̃J�����ړ�.
	if (m_MoveFlag & PEOPLE_LOOK_FLAG) {
		//�l�����鏈���֐�.
		LookAtPeople();
		return;
	}

	if (m_MoveFlag & GHOST_LOOK_FLAG) {
		//�����������鏈���֐�.
		LookAtGhost();
		return;
	}

	m_Camera.vLook.x = m_Camera.vPos.x = m_vTargetPos.x;

}

//================================================.
//		�����������֐�.
//================================================.
void CCameraGameMainStage::Init()
{
	m_Camera.vPos = CAMERA_START_POS;
	m_Camera.vLook = CAMERA_START_LOOK;

}

//================================================.
//		��������֐�.
//================================================.
void CCameraGameMainStage::Release()
{

}

//================================================.
//		�l�����鏈���֐�.
//================================================.
void CCameraGameMainStage::LookAtPeople()
{
	if (m_Camera.vPos.x > 11.0f) {
		m_Camera.vPos.x -= 0.6f;
		m_Camera.vLook.x = m_Camera.vPos.x;
		return;
	}
	m_bNotRenderMap = true;

	//���グ�邽�߂ɍ��W�ړ������֐�.
	MovePosLookUp();

	//���グ�邽�߂ɒ����_�ړ������֐�.
	MoveLookLookUp();

}

//================================================.
//		�����������鏈���֐�.
//================================================.
void CCameraGameMainStage::LookAtGhost()
{
	//���ݑI�����Ă��邨�����̂Ƃ���փJ������߂�.
	const D3DXVECTOR3 vSelectGhostPos = m_vTargetPos;
	m_Camera.vPos		= CAMERA_START_POS;
	m_Camera.vPos.x		= vSelectGhostPos.x;
	m_Camera.vLook		= CAMERA_START_LOOK;
	m_Camera.vLook.x	= vSelectGhostPos.x;
	m_bNotRenderMap		= false;
}

//=================================================.
//		���グ�邽�߂ɍ��W�ړ�.
//=================================================.
void CCameraGameMainStage::MovePosLookUp()
{
	const D3DXVECTOR3 vSeePeopleOldPos = D3DXVECTOR3(m_Camera.vPos.x, m_OldCamera.vPos.y, m_OldCamera.vPos.z);
	const D3DXVECTOR3 vOldPos_Camera = vSeePeopleOldPos - CAMERA_PEOPLE_SEE_POS;
	const float	vLength = D3DXVec3Length(&(vOldPos_Camera));
	const D3DXVECTOR3 vRato = vOldPos_Camera / vLength;
	
	m_Camera.vPos -= 0.2f * vRato;
	
	if (m_Camera.vPos.y < CAMERA_PEOPLE_SEE_POS.y) {
		m_Camera.vPos = CAMERA_PEOPLE_SEE_POS;
	}
}

//==================================================.
//		���グ�邽�߂ɒ����_�ړ�.
//==================================================.
void CCameraGameMainStage::MoveLookLookUp()
{
	const D3DXVECTOR3 vSeePeopleOldLook = D3DXVECTOR3(m_Camera.vLook.x, m_OldCamera.vLook.y, m_OldCamera.vLook.z);
	const D3DXVECTOR3 vOldLook_SeeLook = m_OldCamera.vLook - CAMERA_PEOPLE_SEE_LOOK;
	const float	vLookLength = D3DXVec3Length(&vOldLook_SeeLook);
	const D3DXVECTOR3 vLookRaito = vOldLook_SeeLook / vLookLength;

	m_Camera.vLook -= 0.2f * vLookRaito;

	if (m_Camera.vPos.y < CAMERA_PEOPLE_SEE_LOOK.y) {
		m_Camera.vLook = CAMERA_PEOPLE_SEE_LOOK;
	}
}