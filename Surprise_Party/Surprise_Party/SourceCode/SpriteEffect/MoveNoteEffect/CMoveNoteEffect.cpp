#include "CMoveNoteEffect.h"

/*************************************
*	�����ړ��G�t�F�N�g�N���X.
*************/
CMoveNoteEffect::CMoveNoteEffect()
{

}

CMoveNoteEffect::~CMoveNoteEffect()
{

}

//========================================.
//		�X�V�����֐�.
//========================================.
void CMoveNoteEffect::Update()
{

}

//========================================.
//		�G�t�F�N�g�J�n�����������֐�.
//========================================.
void CMoveNoteEffect::PlayStartInit(const int& num)
{

}

//========================================.
//		�����������֐�.
//========================================.
void CMoveNoteEffect::Init()
{
	m_pCSprite.push_back(m_pCResourceManager->GetSprite(enSprite::eight_part_note));
	m_pCSprite.push_back(m_pCResourceManager->GetSprite(enSprite::Wave));
	//�v�f���ݒ菈���֐�.
	SettingElementsCount();
	for (unsigned int Effect = 0; Effect < m_pCSprite.size(); Effect++) {
		//�����l�ݒ菈���֐�.
		SettingDefaultValue(Effect);
	}
}

//========================================.
//		��������֐�.
//========================================.
void CMoveNoteEffect::Release()
{

}

//========================================.
//		�\�����菈���֐�.
//========================================.
void CMoveNoteEffect::AppeartJudgement(const int& num)
{

}

//========================================.
//		�ړ������֐�.
//========================================.
void CMoveNoteEffect::Move(const int& num)
{

}