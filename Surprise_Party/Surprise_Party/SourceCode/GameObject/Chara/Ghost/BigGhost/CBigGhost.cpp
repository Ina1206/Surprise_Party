#include "CBigGhost.h"

CBigGhost::CBigGhost()
	: m_pCSkinMesh			(nullptr)
	, m_dCntAnimSpeed		(0.0)
	, m_fAnimSpeed			(0.0f)
	, m_AnimNum				(0)
	, m_WakeUpCnt			(0)
	, m_LeanDirect			(1)
	, m_UpDownDirect		(1)
	, m_HaveTroubleActFlag	(0)
	, m_ChangeEmotionFlag	(false)
	, m_pCSpriteEffect		()
	, m_UsingEffectNum		(0)
	, m_EmotionNum			(0)
	, m_bSleepFlag			(true)
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
	//static bool flag = false;
	//if (GetAsyncKeyState(VK_F1) & 0x0001) {
	//	if (flag == false) {
	//		flag = true;
	//	}
	//	else {
	//		flag = false;
	//	}
	//}

	//D3DXVECTOR3 vChange;
	//if (flag == false) {
	//	vChange = m_vPos;
	//}
	//else {
	//	vChange = m_vRot;
	//}

	//if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
	//	vChange.x += 0.01f;
	//}
	//if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
	//	vChange.x -= 0.01f;
	//}
	//if (GetAsyncKeyState(VK_UP) & 0x8000) {
	//	vChange.y += 0.01f;
	//}
	//if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
	//	vChange.y -= 0.01f;
	//}
	//if (GetAsyncKeyState('Z') & 0x8000) {
	//	vChange.z += 0.01f;
	//}
	//if (GetAsyncKeyState('X') & 0x8000) {
	//	vChange.z -= 0.01f;
	//}

	//if (flag == false) {
	//	m_vPos = vChange;
	//}
	//else {
	//	m_vRot = vChange;
	//}

	if (GetAsyncKeyState(VK_RETURN) & 0x8000) {
		m_ChangeEmotionFlag = true;
	}

	//HaveTroubleEmotion();
	//RejoiceEmotion();
	//WakeUp();
	//Sleep();

	ChangeEffect();
	EmotionMove();

	//�G�t�F�N�g�X�V�����֐�.
	if (m_UsingEffectNum != static_cast<int>(enEmotionType::Nothing)) {
		m_pCSpriteEffect[m_UsingEffectNum]->Update();
	}
}

//==========================================.
//		�`�揈���֐�.
//==========================================.
void CBigGhost::Render()
{
	//�r�b�O�S�[�X�g�̕`��.
	m_pCSkinMesh->SetAnimSpeed(m_fAnimSpeed);
	m_pCSkinMesh->SetScale(0.1f);
	m_pCSkinMesh->SetPosition(m_vPos);
	m_pCSkinMesh->SetRotation(m_vRot);
	m_pCSkinMesh->Render(m_mView, m_mProj, m_vCameraPos, m_stLight);

	//�G�t�F�N�g�`��.
	if (m_UsingEffectNum != static_cast<int>(enEmotionType::Nothing)) {
		m_pCSpriteEffect[m_UsingEffectNum]->Render(m_mView, m_mProj, m_vCameraPos);
	}
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

	//m_fAnimSpeed = WAKE_UP_ANIM_SPEED;
	//m_vPos = WAKE_UP_POS;
	//m_vRot = WAKE_UP_ROT;

	//�G�t�F�N�g����������.
	m_pCSpriteEffect.resize(static_cast<int>(enEmotionType::Max));
	m_pCSpriteEffect[static_cast<int>(enEmotionType::Sleep)].reset(new CSleepEffect());
	m_pCSpriteEffect[static_cast<int>(enEmotionType::HaveTrounble)].reset(new CHaveTroubleEffect());
	m_pCSpriteEffect[static_cast<int>(enEmotionType::Rejoice)].reset(new CRejoiceEffect());

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

	//�|��鏈���֐�.
	FallDown(1);

	//�@�񓔍ŏ��̎��̃A�j���[�V����.
	m_pCSkinMesh->ChangeAnimSet_StartPos(m_AnimNum, 1.1);

}

//==========================================.
//		���銴����֐�.
//==========================================.
void CBigGhost::HaveTroubleEmotion()
{
	//����ύX����.
	if (m_ChangeEmotionFlag == true) {
		m_HaveTroubleActFlag = 0;
		m_ChangeEmotionFlag = false;
	}

	if (m_HaveTroubleActFlag & (MOVING_ROT_FLAG | MOVING_POS_FLAG)) {
		//�΂߂ɂȂ鏈��.
		Lean(FALL_DOWN_DIRECTION);
		return;
	}

	if (m_HaveTroubleActFlag & SWING_FLAG) {
		//�h��鏈��.
		m_vRot.y += HAVE_TROUBLE_SPEED * m_LeanDirect;
		m_vRot.z += HAVE_TROUBLE_SPEED * m_LeanDirect;
		if (fabsf(m_vRot.y) > HAVE_TROUBLE_ROT_MAX) {
			m_LeanDirect *= CHANGE_DIRECTION;

		}
		return;
	}
	
	if (m_HaveTroubleActFlag == 0) {
		//���̑̐��ɖ߂鏈��.
		Lean(UP_DIRECTION);
	}
}

//==========================================.
//		��Ԋ�����֐�.
//==========================================.
void CBigGhost::RejoiceEmotion()
{
	//���̏ꏊ�ɖ߂�.
	if (m_ChangeEmotionFlag == true) {
		m_vPos = WAKE_UP_POS;
		m_vRot = WAKE_UP_ROT;
		return;
	}

	//��ъ���\������.
	m_vPos.y += REJOICE_MOVE_SPEED * m_UpDownDirect;
	m_vPos.x += REJOICE_MOVE_SPEED * m_LeanDirect;

	if (m_vPos.y <= WAKE_UP_POS.y) {
		m_UpDownDirect *= CHANGE_DIRECTION;
		m_vPos.y = WAKE_UP_POS.y;
	}

	//�p�x.
	m_vRot.y += 0.01f * m_LeanDirect;
	if (fabsf(m_vRot.y) > REJOICE_ROT_MAX) {
		m_LeanDirect *= CHANGE_DIRECTION;
		m_UpDownDirect *= CHANGE_DIRECTION;
	}

	
}

//==========================================.
//		�Q�鏈���֐�.
//==========================================.
void CBigGhost::Sleep()
{
	m_fAnimSpeed = SLEEP_ANIM_SPEED;
	FallDown(-1);
}

//==========================================.
//		�X�������֐�.
//==========================================.
void CBigGhost::Lean(const int& Direction)
{
	const float			fPosLength	= D3DXVec3Length(&(HAVE_TROUBLE_POS - WAKE_UP_POS));
	const D3DXVECTOR3	vPosUnit	= (HAVE_TROUBLE_POS - WAKE_UP_POS) / fPosLength;
	const float			fRotLength	= D3DXVec3Length(&(HAVE_TROUBLE_ROT - WAKE_UP_ROT));
	const D3DXVECTOR3	vRotUnit	= (HAVE_TROUBLE_ROT - WAKE_UP_ROT) / fRotLength;

	m_vRot += LEAN_SPEED * vRotUnit * static_cast<float>(Direction);
	m_vPos += LEAN_SPEED * vPosUnit * static_cast<float>(Direction);

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

//=============================================.
//		�|��鏈���֐�.
//=============================================.
void CBigGhost::FallDown(const int& Direction)
{
	//���W�P�ʃx�N�g���v�Z.
	const float m_fPosLength = D3DXVec3Length(&(WAKE_UP_POS - SLEEP_POS));
	const D3DXVECTOR3 vPosUnit = (WAKE_UP_POS - SLEEP_POS) / m_fPosLength;
	//�p�x�P�ʃx�N�g���v�Z.
	const float m_fRotLength = D3DXVec3Length(&(WAKE_UP_ROT - SLEEP_ROT));
	const D3DXVECTOR3 vRotUnit = (WAKE_UP_ROT - SLEEP_ROT) / m_fRotLength;

	m_vPos += WAKE_UPING_SPEED * vPosUnit * static_cast<float>(Direction);
	m_vRot += WAKE_UPING_SPEED * vRotUnit * static_cast<float>(Direction);

	if (Direction >= 1) {
		if (m_vPos.y >= WAKE_UP_POS.y) {
			m_vPos = WAKE_UP_POS;
		}
		if (m_vRot.y > WAKE_UP_ROT.y) {
			m_vRot = WAKE_UP_ROT;
			m_WakeUpCnt = 0;
			m_UsingEffectNum = static_cast<int>(enEmotionType::Nothing);
			m_bSleepFlag = false;
		}
		return;
	}

	if (m_vPos.y <= SLEEP_POS.y) {
		m_vPos = SLEEP_POS;
	}
	if (m_vRot.y < SLEEP_ROT.y) {
		m_vRot = SLEEP_ROT;
	}
}

//============================================.
//		�G�t�F�N�g�ύX�����֐�.
//============================================.
void CBigGhost::ChangeEffect()
{
	bool m_bChangeFlag = false;
	if (GetAsyncKeyState('1') & 0x8000) {
		m_UsingEffectNum = static_cast<int>(enEmotionType::HaveTrounble);
		m_HaveTroubleActFlag = MOVING_ROT_FLAG | MOVING_POS_FLAG;
		m_bChangeFlag = true;
	}

	if (GetAsyncKeyState('2') & 0x8000) {
		m_UsingEffectNum = static_cast<int>(enEmotionType::Rejoice);
		m_bChangeFlag = true;
	}

	if (GetAsyncKeyState('3') & 0x8000) {
		m_UsingEffectNum = static_cast<int>(enEmotionType::Sleep);
		m_bChangeFlag = true;
	}

	if (GetAsyncKeyState('4') & 0x8000) {
		m_UsingEffectNum = static_cast<int>(enEmotionType::Nothing);
	}

	if (m_bChangeFlag == true) {
		m_vPos = WAKE_UP_POS;
		m_vRot = WAKE_UP_ROT;
		for (int sprite = 0; sprite < m_pCSpriteEffect[m_UsingEffectNum]->GetSpriteMax(); sprite++) {
			m_pCSpriteEffect[m_UsingEffectNum]->PlayStartInit(sprite);
		}
	}
}

//============================================.
//		����ړ������֐�.
//============================================.
void CBigGhost::EmotionMove()
{
	D3DXVECTOR3 vCenterPos;

	switch (static_cast<enEmotionType>(m_UsingEffectNum)) {
	case enEmotionType::Sleep:
		vCenterPos = m_vPos;
		if (m_bSleepFlag == true) {
			WakeUp();
			break;
		}
		Sleep();
		break;
	case enEmotionType::HaveTrounble:
		HaveTroubleEmotion();
		m_pCSkinMesh->GetPosFromBone("joint12", &vCenterPos);
		break;
	case enEmotionType::Rejoice:
		RejoiceEmotion();
		m_pCSkinMesh->GetPosFromBone("joint12", &vCenterPos);
		break;
	case enEmotionType::Nothing:
		m_vPos = WAKE_UP_POS;
		m_vRot = WAKE_UP_ROT;
		break;
	}

	if (m_UsingEffectNum != static_cast<int>(enEmotionType::Nothing)) {
		m_pCSpriteEffect[m_UsingEffectNum]->SetCenterPos(vCenterPos);
	}
}