#include "CBigGhost.h"

CBigGhost::CBigGhost()
	: m_pCSkinMesh			(nullptr)
	, m_dCntAnimSpeed		(0.0)
	, m_fAnimSpeed			(0.0f)
	, m_AnimNum				(0)
	, m_WakeUpCnt			(0)
	, m_SwingDirect			(1)
	, m_HaveTroubleActFlag	(0)
{
	//�����������֐�.
	Init();
}

CBigGhost::~CBigGhost()
{
	//��������֐�.
	Release();
}

//==========================================.
//		�X�V�����֐�.
//==========================================.
void CBigGhost::Update()
{
	static bool flag = false;
	if (GetAsyncKeyState(VK_F1) & 0x0001) {
		if (flag == false) {
			flag = true;
		}
		else {
			flag = false;
		}
	}

	D3DXVECTOR3 vChange;
	if (flag == false) {
		vChange = m_vPos;
	}
	else {
		vChange = m_vRot;
	}

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
		vChange.x += 0.01f;
	}
	if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
		vChange.x -= 0.01f;
	}
	if (GetAsyncKeyState(VK_UP) & 0x8000) {
		vChange.y += 0.01f;
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
		vChange.y -= 0.01f;
	}
	if (GetAsyncKeyState('Z') & 0x8000) {
		vChange.z += 0.01f;
	}
	if (GetAsyncKeyState('X') & 0x8000) {
		vChange.z -= 0.01f;
	}

	if (flag == false) {
		m_vPos = vChange;
	}
	else {
		m_vRot = vChange;
	}

	if (GetAsyncKeyState(VK_RETURN) & 0x8000) {
		m_HaveTroubleActFlag = 0;
	}


}

//==========================================.
//		�`�揈���֐�.
//==========================================.
void CBigGhost::Render()
{
	m_pCSkinMesh->SetAnimSpeed(m_fAnimSpeed);
	m_pCSkinMesh->SetScale(0.1f);
	m_pCSkinMesh->SetPosition(m_vPos);
	m_pCSkinMesh->SetRotation(m_vRot);
	m_pCSkinMesh->Render(m_mView, m_mProj, m_vCameraPos, m_stLight);
}

//==========================================.
//		�����������֐�.
//==========================================.
void CBigGhost::Init()
{
	m_pCSkinMesh = m_pCResourceManager->GetSkinMesh(enSkinMeshType::BigGhost);
	m_vPos = SLEEP_POS;
	m_vRot = SLEEP_ROT;

	m_fAnimSpeed = SLEEP_ANIM_SPEED;

	m_vPos = WAKE_UP_POS;
	m_vRot = WAKE_UP_ROT;
	
	m_HaveTroubleActFlag = MOVING_POS_FLAG | MOVING_ROT_FLAG;
}

//==========================================.
//		��������֐�.
//==========================================.
void CBigGhost::Release()
{

}

//==========================================.
//		�N�������֐�.
//==========================================.
void CBigGhost::WakeUp()
{
	//�N����܂ł̑ҋ@.
	m_WakeUpCnt++;
	if (m_WakeUpCnt <= WAKE_UP_TIMING) {
		return;
	}

	//�N����Ƃ��̃A�j���[�V�����^�C�~���O.
	if (m_fAnimSpeed > WAKE_UP_ANIM_SPEED) {
		if (m_pCSkinMesh->GetAnimPeriod(m_AnimNum) - m_pCSkinMesh->GetAnimSpeed() <= m_dCntAnimSpeed) {
			m_fAnimSpeed = WAKE_UP_ANIM_SPEED;
		}
		m_dCntAnimSpeed += m_pCSkinMesh->GetAnimSpeed();
		return;
	}

	//���W�P�ʃx�N�g���v�Z.
	const float m_fPosLength = D3DXVec3Length(&(WAKE_UP_POS - SLEEP_POS));
	const D3DXVECTOR3 vPosUnit = (WAKE_UP_POS - SLEEP_POS) / m_fPosLength;
	//�p�x�P�ʃx�N�g���v�Z.
	const float m_fRotLength = D3DXVec3Length(&(WAKE_UP_ROT - SLEEP_ROT));
	const D3DXVECTOR3 vRotUnit = (WAKE_UP_ROT - SLEEP_ROT) / m_fRotLength;

	m_vPos += WAKE_UPING_SPEED * vPosUnit;
	m_vRot += WAKE_UPING_SPEED * vRotUnit;

	if (m_vPos.y >= WAKE_UP_POS.y) {
		m_vPos = WAKE_UP_POS;
	}
	if (m_vRot.y > WAKE_UP_ROT.y) {
		m_vRot = WAKE_UP_ROT;
		m_WakeUpCnt = 0;
	}
	//�@�񓔍ŏ��̎��̃A�j���[�V����.
	m_pCSkinMesh->ChangeAnimSet_StartPos(m_AnimNum, 1.1);

}

//==========================================.
//		���銴����֐�.
//==========================================.
void CBigGhost::HaveTroubleEmotion()
{
	if (m_HaveTroubleActFlag & (MOVING_ROT_FLAG | MOVING_POS_FLAG)) {
		//�΂߂ɂȂ鏈��.
		Falldown(FALL_DOWN_DIRECTION);
		return;
	}

	if (m_HaveTroubleActFlag & SWING_FLAG) {
		//�h��鏈��.
		m_vRot.y += HAVE_TROUBLE_SPEED * m_SwingDirect;
		m_vRot.z += HAVE_TROUBLE_SPEED * m_SwingDirect;
		if (fabsf(m_vRot.y) > HAVE_TROUBLE_ROT_MAX) {
			m_SwingDirect *= CHANGE_DIRECTION;

		}
		return;
	}
	
	if (m_HaveTroubleActFlag == 0) {
		//���̑̐��ɖ߂鏈��.
		Falldown(UP_DIRECTION);
	}
}

//==========================================.
//		��Ԋ�����֐�.
//==========================================.
void CBigGhost::RejoiceEmotion()
{

}

//==========================================.
//		�Q�鏈���֐�.
//==========================================.
void CBigGhost::Sleep()
{

}

//==========================================.
//		�|��鏈���֐�.
//==========================================.
void CBigGhost::Falldown(const int& Direction)
{
	const float			fPosLength	= D3DXVec3Length(&(HAVE_TROUBLE_POS - WAKE_UP_POS));
	const D3DXVECTOR3	vPosUnit	= (HAVE_TROUBLE_POS - WAKE_UP_POS) / fPosLength;
	const float			fRotLength	= D3DXVec3Length(&(HAVE_TROUBLE_ROT - WAKE_UP_ROT));
	const D3DXVECTOR3	vRotUnit	= (HAVE_TROUBLE_ROT - WAKE_UP_ROT) / fRotLength;

	m_vRot += 0.05f * vRotUnit * static_cast<float>(Direction);
	m_vPos += 0.05f * vPosUnit * static_cast<float>(Direction);

	if (Direction >= 1) {
		if (m_vRot.x <= HAVE_TROUBLE_ROT.x) {
			m_vRot = HAVE_TROUBLE_ROT;
			m_HaveTroubleActFlag &= ~MOVING_ROT_FLAG;
		}
		if(m_vPos.y >= HAVE_TROUBLE_POS.y){
			m_vPos = HAVE_TROUBLE_POS;
			m_HaveTroubleActFlag &= ~MOVING_POS_FLAG;
		}
		if (m_HaveTroubleActFlag == 0) {
			m_HaveTroubleActFlag = SWING_FLAG;
		}
		return;
	}

	if (m_vRot.x >= WAKE_UP_ROT.x) {
		m_vRot = WAKE_UP_ROT;
	}
	if (m_vPos.y <= WAKE_UP_POS.y) {
		m_vPos = WAKE_UP_POS;
	}
}