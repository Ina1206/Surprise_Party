#include "CRejoiceEffect.h"

/*********************************************
*		��уG�t�F�N�g.
*********/
CRejoiceEffect::CRejoiceEffect()
	: m_DispCnt		(0)
	, m_PopCnt		(0)
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
	m_DispTime++;
	for (unsigned int sprite = 0; sprite < m_pCSprite.size(); sprite++) {
		if (m_bDispFlag[sprite] == true) {
			if (ScalingTransparent(sprite) == true) {
				//�\���I��.
				//�����l�ݒ�.
				SettingDefaultValue(sprite);
				//�X�v���C�g�̕R�Â�.
				LinkSprite(sprite);
			}

			//�ړ������֐�.
			Move(sprite);
			continue;
		}

		//�\�����菈��
		if (m_DispTime >= DISP_TIME_DELIMITER) {
			//�ԍ��O�̃X�v���C�g�͔�΂�.
			if (sprite % DISP_DELIMITER_MAX != m_PopCnt) {
				continue;
			}

			AppeartJudgement(sprite);
			
			if (m_DispCnt >= POP_MAX) {
				m_DispTime = 0;
				m_DispCnt = 0;
				m_PopCnt++;

				if (m_PopCnt >= DISP_DELIMITER_MAX) {
					m_PopCnt = 0;
				}
			}
		}
	}

}

//=========================================.
//		�G�t�F�N�g�J�n�����֐�.
//=========================================.
void CRejoiceEffect::PlayStartInit(const int& num)
{
	for (unsigned int sprite = 0; sprite < m_pCSprite.size(); sprite++) {
		SettingDefaultValue(sprite);
		m_fDistance[sprite] = 0.0f;
		LinkSprite(sprite);
	}
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
		SettingDefaultValue(sprite);
		//�X�v���C�g�R�Â������֐�.
		LinkSprite(sprite);
	}

	m_fAlphaSpeed	= ALPHA_SPEED;
	m_fScalingSpeed = SCALING_SPEED;
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
	m_fDistance[num] = 0.0f;

	m_bDispFlag[num] = true;
	m_DispCnt++;
}

//=========================================.
//		�ړ������֐�.
//=========================================.
void CRejoiceEffect::Move(const int& num)
{

	m_fDistance[num] += MOVE_SPEED;

	//�p�x.
	const float ANGLE	= START_ANGLE + (num * ANGLE_WIDTH);
	const float RADIAN	= ANGLE / (CIRCLE_HALF_ANGLE * PI);

	m_vPos[num] = m_vCenterPos;
	m_vPos[num].x += cos(RADIAN) * m_fDistance[num];
	m_vPos[num].y += sin(RADIAN) * m_fDistance[num];

	//�����̏���.
	if (num % SPRITE_TYPE_MAX < SPRITE_ATTRIBUTE_MAX) {
		m_fAngle[num] += SWING_SPEED;
		m_vPos[num].x += cos(m_fAngle[num] / (CIRCLE_HALF_ANGLE * PI)) * SWING_WIDHT;
		return;
	}

	//�Ԃ̏���.
	m_vRot[num].z += ROT_SPEED;
}

//=========================================.
//		�X�v���C�g�R�Â������֐�.
//=========================================.
void CRejoiceEffect::LinkSprite(const int& num)
{
	//�ԍ����Ƃ̕R�Â�.
	switch (static_cast<enRejoiceSpriteType>(num % SPRITE_TYPE_MAX)) {
	case enRejoiceSpriteType::YellowEightPartNote:
		m_pCSprite[num] = m_pCResourceManager->GetSprite(enSprite::eight_part_note);
		m_vPart[num] = YELLOW_NOTE;
		break;
	case enRejoiceSpriteType::BlueEightPartNote:
		m_pCSprite[num] = m_pCResourceManager->GetSprite(enSprite::eight_part_note);
		m_vPart[num] = BLUE_NOTE;
		break;
	case enRejoiceSpriteType::PinkFlower:
		m_pCSprite[num] = m_pCResourceManager->GetSprite(enSprite::Flower);
		m_vPart[num] = PINK_FLOWER;
		break;
	case enRejoiceSpriteType::RedFlower:
		m_pCSprite[num] = m_pCResourceManager->GetSprite(enSprite::Flower);
		m_vPart[num] = RED_FLOWER;
		break;
	}
}