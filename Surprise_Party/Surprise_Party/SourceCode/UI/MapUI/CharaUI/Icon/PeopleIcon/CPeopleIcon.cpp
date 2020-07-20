#include "CPeopleIcon.h"

/*********************************
*		�l�̃A�C�R���N���X.
*****/
CPeopleIcon::CPeopleIcon()
	: m_bSurpriseFlag		(false)
	, m_bShoutWoman			(false)
	, m_fAcc				(0.0f)
	, m_pCShockingEffect	(nullptr)
	, m_bJumpFlag			(false)
	, m_bShoutFlag			(false)
	, m_pCSoundPlayManager	(CPlaySoundManager::GetPlaySoundManager())
{
	m_pCShockingEffect.reset(new CShockingEffect());
}

CPeopleIcon::~CPeopleIcon()
{

}

//=====================================.
//		�X�V�����֐�.
//=====================================.
void CPeopleIcon::UpDate()
{
	//�Q�[��������}�b�v���ɍ��W�ϊ������֐�.
	GameMapConversion();

	//�����W�����v���菈���֐�.
	if (DecisionSurpriseJump() == false) {
		//�W�����v���Ȃ��ꍇ�����I��.
		return;
	}

	//�����s�������֐�.
	SurpriseAct();

	//�Ռ��G�t�F�N�g�X�V�����֐�.
	m_pCShockingEffect->SetCenterPos(m_vPos);
	m_pCShockingEffect->Update();
}

//=====================================.
//		�G�t�F�N�g�`�揈���֐�.
//=====================================.
void CPeopleIcon::RenderEffect()
{
	if (m_bSurpriseFlag == false) {
		return;
	}

	m_pCShockingEffect->Render();
}

//=====================================.
//		�����s�������֐�.
//=====================================.
void CPeopleIcon::SurpriseAct()
{
	m_fAcc += ACC_SPEED;
	m_vPos.y += m_fAcc - GRAVITY;

	if (m_vPos.y >= START_POS.y) {
		m_vPos.y = START_POS.y;
		m_bJumpFlag = false;
	}
}

//======================================.
//		�����W�����v���菈���֐�.
//======================================.
bool CPeopleIcon::DecisionSurpriseJump()
{
	if (m_bSurpriseFlag == false) {
		if (m_bJumpFlag == false) {
			m_fAcc = 0.0f;
			m_bShoutFlag = false;
			return false;
		}
	}
	m_bJumpFlag = true;

	if (m_bShoutPossibleFlag == false) {
		return true;
	}

	if (m_bShoutFlag == false) {
		m_bShoutFlag = true;
		if (m_bShoutWoman == true) {
			//�j�̎q�̋��ѐ�.
			m_pCSoundPlayManager->SetPlaySE(enSEType::WomanShout);
			m_pCSoundPlayManager->SetSEVolume(enSEType::WomanShout, m_pCSoundPlayManager->VOLUME_MAX);
			return true;
		}

		//���̎q�̋��ѐ�.
		m_pCSoundPlayManager->SetPlaySE(enSEType::ManShout);
		m_pCSoundPlayManager->SetSEVolume(enSEType::ManShout, m_pCSoundPlayManager->VOLUME_MAX);
	}

	return true;

}