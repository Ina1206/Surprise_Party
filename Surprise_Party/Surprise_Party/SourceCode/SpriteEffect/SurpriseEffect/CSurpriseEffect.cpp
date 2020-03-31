#include "CSurpriseEffect.h"

/*****************************************
*		�����G�t�F�N�g.
*******************/
CSurpriseEffect::CSurpriseEffect()
	: m_DispCnt			(0)
	, m_bAllDispFlag	(false)
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
				m_bAllDispFlag = false;
			}
			//�ړ������֐�.
			Move(sprite);
			continue;
		}

		//�\�����菈��
		if (m_DispCnt <= 3) {
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
	m_fDistance.resize(m_pCSprite.size());
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
	//�p�x.
	m_vRot[num].y = ROT_Y;

	m_fDistance[num] = 0.0f;

	m_DispCnt++;
	m_bDispFlag[num] = true;

}

//================================================.
//		�ړ������֐�.
//================================================.
void CSurpriseEffect::Move(const int& num)
{
	//�p�x.
	const float angle = BASE_ANGLE + (ANGLE_WIDTH * (num % SPRITE_MAX));
	//���W�A��.
	const float radian = angle / CIRCLE_HALF_ANGLE * PI;

	m_fDistance[num] += MOVE_SPEED;

	m_vPos[num].x += (cos(radian) * m_fDistance[num]) ;
	m_vPos[num].y += (sin(radian) * m_fDistance[num]) ;

}