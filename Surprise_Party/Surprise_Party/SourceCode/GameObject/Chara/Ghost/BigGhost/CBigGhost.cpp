#include "CBigGhost.h"

/******************************************
*		�傫���������N���X.
**********/
CBigGhost::CBigGhost()
	: m_pCSkinMesh			(nullptr)
	, m_dCntAnimSpeed		(0.0)
	, m_fAnimSpeed			(0.0f)
	, m_AnimNum				(0)
	, m_vPreRot				(0.0f, 0.0f, 0.0f)
	, m_WakeUpCnt			(0)
	, m_LeanDirect			(1)
	, m_UpDownDirect		(1)
	, m_HaveTroubleActFlag	(0)
	, m_ChangeEmotionFlag	(false)
	, m_pCSpriteEffect		()
	, m_UsingEffectNum		(0)
	, m_OldEmotionNum		(0)
	, m_bSleepFlag			(true)
	, m_bSkipFlag			(false)
	, m_pCPlaySoundManager	(CPlaySoundManager::GetPlaySoundManager())
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
	//�G�t�F�N�g�ύX�����֐�.
	if (m_EmotionNum != m_OldEmotionNum) {
		ChangeEffect();
		m_OldEmotionNum = m_EmotionNum;
	}
	//����ړ������֐�.
	EmotionMove();

	//�G�t�F�N�g�X�V�����֐�.
	if (m_UsingEffectNum < static_cast<int>(m_pCSpriteEffect.size())) {
		m_pCSpriteEffect[m_UsingEffectNum]->Update();
	}

}

//==========================================.
//		�`�揈���֐�.
//==========================================.
void CBigGhost::Render()
{
	//�r�b�O�S�[�X�g�̕`��.
	if (m_bPauseFlag == false) {
		m_pCSkinMesh->SetAnimSpeed(m_fAnimSpeed);
	}
	else {
		m_pCSkinMesh->SetAnimSpeed(PAUSE_ANIM_SPEED);
	}
	m_pCSkinMesh->SetScale(SCALE);
	m_pCSkinMesh->SetPosition(m_vPos);
	m_pCSkinMesh->SetRotation(m_vRot);
	m_pCSkinMesh->SetPreRot(m_vPreRot);
	m_pCSkinMesh->SetPrePos(m_vPrePos);
	m_pCSkinMesh->Render(m_mView, m_mProj, m_vCameraPos, m_stLight);

	//�G�t�F�N�g�`��.
	if (m_UsingEffectNum < static_cast<int>(m_pCSpriteEffect.size())) {
		m_pCSpriteEffect[m_UsingEffectNum]->Render(m_mView, m_mProj, m_vCameraPos);
	}
}

//==========================================.
//		�����������֐�.
//==========================================.
void CBigGhost::Init()
{
	//�������̏����ݒ�.
	m_pCSkinMesh	= m_pCResourceManager->GetSkinMesh(enSkinMeshType::BigGhost);
	m_vPos			= SLEEP_POS;
	m_vRot			= SLEEP_ROT;
	m_fAnimSpeed	= SLEEP_ANIM_SPEED;
	m_EmotionNum	= static_cast<int>(enEmotionType::WakeUp);
	m_OldEmotionNum = m_EmotionNum;

	//�G�t�F�N�g����������.
	m_pCSpriteEffect.emplace_back(new CSleepEffect());
	m_pCSpriteEffect.emplace_back(new CHaveTroubleEffect());
	m_pCSpriteEffect.emplace_back(new CRejoiceEffect());
	m_pCSpriteEffect.emplace_back(new CQuestionEffect());

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
	//�X�L�b�v�����ꍇ.
	if (m_bSkipFlag == true) {
		m_WakeUpCnt = WAKE_UP_TIMING;
		m_fAnimSpeed = WAKE_UP_ANIM_SPEED;
	}

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
	FallDown(WAKE_UP_DIRECT);

	//�@�񓔍ŏ��̎��̃A�j���[�V����.
	m_pCSkinMesh->ChangeAnimSet_StartPos(m_AnimNum, WAKE_UP_ANIM_POS);

}

//==========================================.
//		���銴����֐�.
//==========================================.
void CBigGhost::HaveTroubleEmotion()
{
	//����ύX����.
	if (m_ChangeEmotionFlag == true) {
		m_HaveTroubleActFlag	= 0;
		m_ChangeEmotionFlag		= false;
		m_vPos					= WAKE_UP_POS;
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
			//�����ύX.
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

	//�ʒu.
	if (m_vPos.y <= m_vChangeBeforePos.y) {
		m_UpDownDirect *= CHANGE_DIRECTION;
		m_vPos.y		= m_vChangeBeforePos.y;
	}

	//�p�x.
	m_vRot.y += REJOICE_ROT_SPEED * m_LeanDirect;
	if (fabsf(m_vRot.y) > REJOICE_ROT_MAX) {
		m_LeanDirect	*= CHANGE_DIRECTION;
		m_UpDownDirect	*= CHANGE_DIRECTION;
		//���SE�Đ�.
		m_pCPlaySoundManager->SetPlaySE(enSEType::Redjuice);
	}

	
}

//==========================================.
//		�^�⊴����֐�.
//==========================================.
void CBigGhost::QuestionEmotion()
{
	m_vRot.z -= QUESTION_LEAN_SPEED;

	//�X���ŏ��l.
	const float LEAN_ROT_MIN = static_cast<float>(D3DXToRadian(QUESTION_LEAN_MIN));
	if (m_vRot.z < LEAN_ROT_MIN) {
		m_vRot.z = LEAN_ROT_MIN;
	}
}

//==========================================.
//		�Q�鏈���֐�.
//==========================================.
void CBigGhost::Sleep()
{
	m_fAnimSpeed = SLEEP_ANIM_SPEED;
	//�|��鏈���֐�.
	FallDown(SLEEP_DIRECT);
}

//==========================================.
//		�X�������֐�.
//==========================================.
void CBigGhost::Lean(const int& Direction)
{
	//���W.
	const float			fPosLength	= D3DXVec3Length(&(HAVE_TROUBLE_POS - m_vChangeBeforePos));	//����.
	const D3DXVECTOR3	vPosUnit	= (HAVE_TROUBLE_POS - m_vChangeBeforePos) / fPosLength;		//�䗦.
	//�p�x.
	const float			fRotLength	= D3DXVec3Length(&(HAVE_TROUBLE_ROT - WAKE_UP_ROT));		//����.
	const D3DXVECTOR3	vRotUnit	= (HAVE_TROUBLE_ROT - WAKE_UP_ROT) / fRotLength;			//�䗦.

	m_vRot += LEAN_SPEED * vRotUnit * static_cast<float>(Direction);
	m_vPos += LEAN_SPEED * vPosUnit * static_cast<float>(Direction);

	//�|���Ƃ�.
	if (Direction >= FALL_DOWN_DIRECTION) {
		if (m_vRot.x <= HAVE_TROUBLE_ROT.x) {
			m_HaveTroubleActFlag	&= ~MOVING_ROT_FLAG;
			m_vRot	= HAVE_TROUBLE_ROT;
		}
		if(m_vPos.y >= HAVE_TROUBLE_POS.y){
			m_HaveTroubleActFlag &= ~MOVING_POS_FLAG;
			m_vPos		= m_vChangeBeforePos;
			m_vPos.y	= HAVE_TROUBLE_POS.y;
		}
		if (m_HaveTroubleActFlag == 0) {
			m_HaveTroubleActFlag = SWING_FLAG;
		}
		return;
	}

	//���̑Ԑ��ɖ߂�Ƃ�.
	if (m_vRot.x >= m_vChangeBeforePos.x) {
		m_vRot = m_vChangeBeforePos;
	}
	if (m_vPos.y <= m_vChangeBeforePos.y) {
		m_vPos = m_vChangeBeforePos;
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

	//�N��������̎�.
	if (Direction >= WAKE_UP_DIRECT) {
		if (m_vRot.y > WAKE_UP_ROT.y ||
			m_vPos.y >= WAKE_UP_POS.y) {
			m_vRot				= WAKE_UP_ROT;
			m_WakeUpCnt			= 0;
			m_UsingEffectNum	= static_cast<int>(enEmotionType::Nothing);
			m_bSleepFlag		= false;
			m_bSkipFlag			= false;
		}
		return;
	}

	//��������̎�.
	if (m_vPos.y <= SLEEP_POS.y ||
		m_vRot.y < SLEEP_ROT.y) {
		m_vPos			= SLEEP_POS;
		m_vRot			= SLEEP_ROT;
		m_bSleepFlag	= true;
		m_bSkipFlag		= false;
	}
}

//============================================.
//		�G�t�F�N�g�ύX�����֐�.
//============================================.
void CBigGhost::ChangeEffect()
{
	//������.
	if (m_EmotionNum != static_cast<int>(enEmotionType::ViewSmartphone)) {
		m_vPos		= WAKE_UP_POS;
		m_vPrePos	= BASE_PRE_POS;
		m_vPreRot	= BASE_PRE_ROT;
	}
	m_vRot = WAKE_UP_ROT;

	//�ύX�O�̍��W(�O���ҏW�p�ϐ��j.
	if (m_vChangeBeforePos.y > 0.0f) {
		m_vPos = m_vChangeBeforePos;
	}
	else {
		m_vChangeBeforePos = WAKE_UP_POS;
	}

	switch (static_cast<enEmotionType>(m_EmotionNum)) {
	case enEmotionType::Sleep:
	case enEmotionType::WakeUp:
		m_UsingEffectNum = static_cast<int>(enEmotionType::Sleep);
		break;
	case enEmotionType::HaveTrounble:
		m_UsingEffectNum = static_cast<int>(enEmotionType::HaveTrounble);
		m_HaveTroubleActFlag = MOVING_ROT_FLAG | MOVING_POS_FLAG;
		break;
	case enEmotionType::Rejoice:
		m_UsingEffectNum = static_cast<int>(enEmotionType::Rejoice);

		break;
	case enEmotionType::Question:
		m_UsingEffectNum = static_cast<int>(enEmotionType::Question);
		break;
	case enEmotionType::ViewSmartphone:
		//�ړ��p�x�����֐�.
		MoveRotation(m_vPos, m_vLookAtPos);

		m_vPrePos.z = VIEW_PRE_POS_Y;
		m_vPreRot	= WAKE_UP_ROT;

		m_bSleepFlag = true;
		m_UsingEffectNum = static_cast<int>(enEmotionType::ViewSmartphone);

		break;
	default:
		m_UsingEffectNum = static_cast<int>(enEmotionType::Nothing);
		break;
	}

	if(m_EmotionNum < static_cast<int>(m_pCSpriteEffect.size())){
		for (int sprite = 0; sprite < m_pCSpriteEffect[m_UsingEffectNum]->GetSpriteMax(); sprite++) {
			//�G�t�F�N�g�J�n�����������֐�.
			m_pCSpriteEffect[m_UsingEffectNum]->PlayStartInit(sprite);
		}
	}
}

//============================================.
//		����ړ������֐�.
//============================================.
void CBigGhost::EmotionMove()
{
	if (static_cast<enEmotionType>(m_UsingEffectNum) != enEmotionType::Sleep) {
		m_pCSkinMesh->ChangeAnimSet_StartPos(m_AnimNum, WAKE_UP_ANIM_POS);
		m_fAnimSpeed = WAKE_UP_ANIM_SPEED;
	}

	D3DXVECTOR3 vCenterPos;	//�G�t�F�N�g�o�����S���W.
	m_pCSkinMesh->GetPosFromBone("joint12", &vCenterPos);

	switch (static_cast<enEmotionType>(m_UsingEffectNum)) {
	case enEmotionType::Sleep:
		vCenterPos = m_vPos;
		if (m_EmotionNum == static_cast<int>(enEmotionType::WakeUp)) {
			//�N�������֐�.
			WakeUp();
			break;
		}
		//�Q�鏈���֐�.
		Sleep();
		break;
	case enEmotionType::HaveTrounble:
		//���銴����֐�.
		HaveTroubleEmotion();
		break;
	case enEmotionType::Rejoice:
		//��Ԋ�����֐�.
		RejoiceEmotion();
		break;
	case enEmotionType::Question:
		//�^�⊴����֐�.
		QuestionEmotion();
		//�㉺�ړ������֐�.
		MoveUpDown();
		break;
	case enEmotionType::ViewSmartphone:
		
		break;
	case enEmotionType::Nothing:
		//�㉺�ړ������֐�.
		MoveUpDown();
		break;
	}

	//�G�t�F�N�g�o�����S���W�ݒ�.
	if (m_UsingEffectNum < static_cast<int>(m_pCSpriteEffect.size())) {
		m_pCSpriteEffect[m_UsingEffectNum]->SetCenterPos(vCenterPos);
	}
}