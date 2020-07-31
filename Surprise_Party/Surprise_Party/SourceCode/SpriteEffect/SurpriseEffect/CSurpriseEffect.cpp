#include "CSurpriseEffect.h"

/*****************************************
*		�����G�t�F�N�g.
*******************/
CSurpriseEffect::CSurpriseEffect()
	: m_DispCnt			(0)
	, m_bAllDispFlag	(false)
	, m_Direct			(1)
	, m_vOldCenterPos	(0.0f, 0.0f, 0.0f)
	, m_bPlaySound	(false)
{
	//�����������֐�.
	Init();
}

CSurpriseEffect::~CSurpriseEffect()
{
	//��������֐�.
	Release();
}

//============================================.
//		�X�V�����֐�.
//============================================.
void CSurpriseEffect::Update()
{

	const float DIFFERENCE_CENTER_POS = m_vCenterPos.x - m_vOldCenterPos.x;
	if (DIFFERENCE_CENTER_POS != 0.0f) {
		//����.
		m_Direct = static_cast<int>(DIFFERENCE_CENTER_POS / fabsf(DIFFERENCE_CENTER_POS));
	}
	m_vOldCenterPos = m_vCenterPos;

	for (unsigned int sprite = 0; sprite < m_pCSprite.size(); sprite++) {
		if (m_bAllDispFlag == false) {
			//�\���I��.
			//�����l�ݒ�.
			SettingDefaultValue(sprite);
			m_DispCnt = 0;
			continue;
		}

		if (m_bDispFlag[sprite] == true) {
			if (ScalingTransparent(sprite)) {
				SettingDefaultValue(sprite);
				m_bAllDispFlag = false;
			}
			//�ړ������֐�.
			Move(sprite);
			continue;
		}

		//�\�����菈��
		if (m_DispCnt <= SPRITE_MAX) {
			AppeartJudgement(sprite);
		}

	}
}

//=============================================.
//		�Đ��J�n�����������������֐�.
//=============================================.
void CSurpriseEffect::PlayStartInit(const int& num)
{
	for (unsigned int sprite = 0; sprite < m_pCSprite.size(); sprite++) {
		SettingDefaultValue(sprite);
		m_fDistance[sprite] = 0.0f;
	}
}

//=============================================.
//		�����������֐�.
//=============================================.
void CSurpriseEffect::Init()
{
	//�v�f���ݒ�.
	m_pCSprite.resize(SPRITE_MAX);
	SettingElementsCount();

	//�����l�ݒ�.
	for (unsigned int sprite = 0; sprite < m_pCSprite.size(); sprite++) {
		SettingDefaultValue(sprite);

		m_pCSprite[sprite] = m_pCResourceManager->GetSprite(enSprite::Swet);
	}

	m_fScalingSpeed = SCALE_SPEED;
	m_fAlphaSpeed = ALPHA_SPEED;
}

//==============================================.
//		��������֐�.
//==============================================.
void CSurpriseEffect::Release()
{

}

//===============================================.
//		�\�����菈���֐�.
//===============================================.
void CSurpriseEffect::AppeartJudgement(const int& num)
{
	//�����ʒu.
	m_vPos[num] = m_vCenterPos;

	m_DispCnt++;
	m_bDispFlag[num] = true;

	if (m_bPlaySound == true) {
		m_pCPlaySoundManager->SetPlaySE(enSEType::Swet);
	}

}

//================================================.
//		�ړ������֐�.
//================================================.
void CSurpriseEffect::Move(const int& num)
{

	//�p�x.
	float angle = 0.0f;
	if (m_Direct > 0) {
		angle = static_cast<float>(D3DXToRadian(LEFT_ANGLE + (ANGLE_WIDTH * (num % SPRITE_MAX))));
		//�p�x.
		m_vRot[num].y = ROT_Y;
	}
	else {
		angle = static_cast<float>(D3DXToRadian(RIGHT_ANGLE + (ANGLE_WIDTH * (num % SPRITE_MAX))));
		m_vRot[num].y = 0.0f;
	}
	m_fDistance[num] += MOVE_SPEED;

	m_vPos[num].x = cos(angle) - (m_fDistance[num] * m_Direct) + m_vCenterPos.x;
	m_vPos[num].y = sin(angle) + m_fDistance[num] + m_vCenterPos.y;

}