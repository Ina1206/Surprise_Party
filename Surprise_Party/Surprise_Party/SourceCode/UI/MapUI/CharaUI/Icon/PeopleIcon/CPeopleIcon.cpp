#include "CPeopleIcon.h"

CPeopleIcon::CPeopleIcon()
	: m_bSurpriseFlag		(false)
	, m_fAcc				(0.0f)
{

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