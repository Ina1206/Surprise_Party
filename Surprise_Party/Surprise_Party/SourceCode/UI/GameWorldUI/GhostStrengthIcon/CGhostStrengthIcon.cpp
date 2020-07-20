#include "CGhostStrengthIcon.h"

/************************************************
*		�������̗̑̓A�C�R���N���X.
***************/
CGhostStrengthIcon::CGhostStrengthIcon()
{
	//�����������֐�.
	Init();
}

CGhostStrengthIcon::~CGhostStrengthIcon()
{
	//��������֐�.
	Release();
}

//===========================================.
//		�X�V�����֐�.
//===========================================.
void CGhostStrengthIcon::UpDate()
{
	//���W�ݒ�.
	m_vPos = m_vCharacterPos + ICON_POS_ADJUST;

	//�̗̓A�C�R���̌���.
	switch (static_cast<enStrengthType>(m_StrengthIcon)) {
	case enStrengthType::Bad:
		m_vPattarn = BAD_STRENGTH;
		break;
	case enStrengthType::Normal:
		m_vPattarn = NORMAL_STRENGTH;
		break;
	case enStrengthType::Good:
		m_vPattarn = GOOD_STRENGTH;
		break;
	case enStrengthType::Great:
		m_vPattarn = GREAT_STRENGTH;
		break;
	}

	//���ߒl.
	if (m_vPos.z <= ALPHA_CHANGE_POS) {
		m_fAlpha = BEFORE_WALL_ALPHA;
		return;
	}
	m_fAlpha = WALL_BACK_ALPHA;
}

//===========================================.
//		�����������֐�.
//===========================================.
void CGhostStrengthIcon::Init()
{
	m_pCSprite = m_pCResourceManager->GetSprite(enSprite::Strenght_Icon);
	m_bDepth = false;
}

//===========================================.
//		��������֐�.
//===========================================.
void CGhostStrengthIcon::Release()
{
	m_pCSprite = nullptr;
}