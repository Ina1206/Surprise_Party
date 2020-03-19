#include "CRejoiceEffect.h"

/*********************************************
*		��уG�t�F�N�g.
*********/
CRejoiceEffect::CRejoiceEffect()
{
	//�����������֐�.
	Init();
}

CRejoiceEffect::~CRejoiceEffect()
{
	//��������֐�.
	Release();
}

//=========================================.
//		�X�V�����֐�.
//=========================================.
void CRejoiceEffect::Update()
{

}

//=========================================.
//		�����������֐�.
//=========================================.
void CRejoiceEffect::Init()
{
	//�v�f���ݒ菈��.
	m_pCSprite.resize(SPRITE_MAX);
	SettingElementsCount();

	//�����������֐�.
	for (unsigned int sprite = 0; sprite < m_pCSprite.size(); sprite++) {


	}
}

//=========================================.
//		��������֐�.
//=========================================.
void CRejoiceEffect::Release()
{

}

//=========================================.
//		�\�����菈���֐�.
//=========================================.
void CRejoiceEffect::AppeartJudgement(const int& num)
{

}

//=========================================.
//		�ړ������֐�.
//=========================================.
void CRejoiceEffect::Move(const int& num)
{

}

//=========================================.
//		�X�v���C�g�R�Â������֐�.
//=========================================.
void CRejoiceEffect::LinkSprite(const int& num)
{
	//�ԍ����Ƃ̕R�Â�.
	switch (static_cast<enRejoiceSpriteType>(num % SPRITE_MAX)) {
	case enRejoiceSpriteType::EightPartNote:
		m_pCSprite[num] = m_pCResourceManager->GetSprite(enSprite::eight_part_note);
		break;
	case enRejoiceSpriteType::SixteenPartNote:
		m_pCSprite[num] = m_pCResourceManager->GetSprite(enSprite::sixteen_part_note);
		break;
	case enRejoiceSpriteType::Flower:
		m_pCSprite[num] = m_pCResourceManager->GetSprite(enSprite::Flower);
		break;
	}
}