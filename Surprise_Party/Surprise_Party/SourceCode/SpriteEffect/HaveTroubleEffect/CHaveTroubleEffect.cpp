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
			ScalingTransparent(sprite);

			//�ړ������֐�.
			Move(sprite);
			continue;
		}

		if (m_DispTime >= 50) {
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
		//m_fAlpha[sprite] = ALPHA_MAX;
		//m_fScale[sprite] = SCALE_MAX;
		//m_vPos[sprite] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//m_bDispFlag[sprite] = false;
		SettingDefaultValue(sprite);

		m_pCSprite[sprite] = m_pCResourceManager->GetSprite(enSprite::Swet);
	}
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
	m_vPos[num].x += cos(120 + ( 20 * (num % 3)) / 180.0f * PI) * 0.03f;
	m_vPos[num].y += sin(120 + ( 20 * (num % 3)) / 180.0f * PI) * 0.03f;
}