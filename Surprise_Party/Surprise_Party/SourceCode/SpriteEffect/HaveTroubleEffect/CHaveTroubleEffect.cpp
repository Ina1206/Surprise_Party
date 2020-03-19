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

		//�\�����菈��
		if (m_DispTime >= DISP_TIME_MAX) {
			AppeartJudgement(sprite);
			if (m_DispCnt >= LINE_MAX) {
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
		//���摜.
		m_pCSprite[sprite] = m_pCResourceManager->GetSprite(enSprite::Swet);
	}
	m_fAlphaSpeed	= ALPHA_SPEED;
	m_fScalingSpeed = SCALING_SPEED;
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
	//�����ʒu.
	m_vPos[num] = m_vCenterPos + INT_LOCAL_POS;
	//�p�x.
	m_vRot[num].z = -ROT_WIDTH + ((num % LINE_MAX)* ROT_WIDTH);

	m_DispCnt++;
	m_bDispFlag[num] = true;
}

//============================================.
//		�ړ������֐�.
//============================================.
void CHaveTroubleEffect::Move(const int& num)
{
	//�p�x.
	const float angle = START_ANGLE + (ANGLE_WIDTH * (num % LINE_MAX));
	//���W�A��.
	const float radian = angle / CIRCLE_HALF_ANGLE * PI;
	m_vPos[num].x += cos(radian) * MOVE_SPEED;
	m_vPos[num].y += sin(radian) * MOVE_SPEED;
}