#include "CHaveTroubleEffect.h"

/******************************************
*		����G�t�F�N�g�N���X.
************/
CHaveTroubleEffect::CHaveTroubleEffect()
	: m_DispCnt	(0)
{
	//�����������֐�.
	Init();
}

CHaveTroubleEffect::~CHaveTroubleEffect()
{
	//��������֐�.
	Release();
}

//===========================================.
//		�X�V�����֐�.
//===========================================.
void CHaveTroubleEffect::Update()
{
	m_DispTime++;
	for (unsigned int sprite = 0; sprite < m_pCSprite.size(); sprite++) {
		if (m_bDispFlag[sprite] == true) {
			if (ScalingTransparent(sprite) == true) {
				//�\���I��.
				//�����l�ݒ�.
				SettingDefaultValue(sprite);
			}

			//�ړ������֐�.
			Move(sprite);
			continue;
		}

		if (m_DispTime >= 20) {
			AppeartJudgement(sprite);
			if (m_DispCnt >= 3) {
				m_DispCnt = 0;
				m_DispTime = 0;
			}
		}
	}
}

//===========================================.
//		�����������֐�.
//===========================================.
void CHaveTroubleEffect::Init()
{
	//�v�f���ݒ�.
	m_pCSprite.resize(SPRITE_MAX);
	SettingElementsCount();

	for (unsigned int sprite = 0; sprite < m_pCSprite.size(); sprite++) {
		//�����l�ݒ�.
		SettingDefaultValue(sprite);

		m_pCSprite[sprite] = m_pCResourceManager->GetSprite(enSprite::Swet);
	}
	m_fAlphaSpeed = 0.04f;
	m_fScalingSpeed = 0.04f;
}

//===========================================.
//		��������֐�.
//===========================================.
void CHaveTroubleEffect::Release()
{

}

//============================================.
//		�\�����菈���֐�.
//============================================.
void CHaveTroubleEffect::AppeartJudgement(const int& num)
{
	m_vPos[num] = m_vCenterPos + INT_LOCAL_POS;
	m_DispCnt++;
	m_bDispFlag[num] = true;
}

//============================================.
//		�ړ������֐�.
//============================================.
void CHaveTroubleEffect::Move(const int& num)
{
	const float radian = 120 + (30 * (num % 3)) / 180.0f * PI;
	m_vPos[num].x += cos(radian) * 0.03f;
	m_vPos[num].y += sin(radian) * 0.03f;
}