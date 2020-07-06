#include "CPeopleIcon.h"

CPeopleIcon::CPeopleIcon()
	: m_bSurpriseFlag		(false)
	, m_fAcc				(0.0f)
	, m_pCShockingEffect	(nullptr)
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

	if (m_bSurpriseFlag == false) {
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
		m_fAcc = 0.0f;
		m_bSurpriseFlag = false;
	}
}