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
		//�X�v���C�g�R�Â������֐�.
		LinkSprite(sprite);

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
	m_vPos[num].x += cos((10.0f + (num * 20.0f) / CIRCLE_HALF_ANGLE * PI)) * 0.02f;
	m_vPos[num].y += sin((10.0f + (num * 20.0f) / CIRCLE_HALF_ANGLE * PI)) * 0.02f;
}

//=========================================.
//		�X�v���C�g�R�Â������֐�.
//=========================================.
void CRejoiceEffect::LinkSprite(const int& num)
{
	//�ԍ����Ƃ̕R�Â�.
	switch (static_cast<enRejoiceSpriteType>(num % SPRITE_MAX)) {
	case enRejoiceSpriteType::PinkEightPartNote:
		m_pCSprite[num] = m_pCResourceManager->GetSprite(enSprite::eight_part_note);
		m_vPart[num] = D3DXVECTOR2(0.0f, 0.0f);
		break;
	case enRejoiceSpriteType::BlueEightPartNote:
		m_pCSprite[num] = m_pCResourceManager->GetSprite(enSprite::eight_part_note);
		m_vPart[num] = D3DXVECTOR2(2.0f, 0.0f);
		break;
	case enRejoiceSpriteType::PinkFlower:
		m_pCSprite[num] = m_pCResourceManager->GetSprite(enSprite::Flower);
		m_vPart[num] = D3DXVECTOR2(0.0f, 0.0f);
		break;
	case enRejoiceSpriteType::RedFlower:
		m_pCSprite[num] = m_pCResourceManager->GetSprite(enSprite::Flower);
		m_vPart[num] = D3DXVECTOR2(0.0f, 1.0f);
		break;
	}
}