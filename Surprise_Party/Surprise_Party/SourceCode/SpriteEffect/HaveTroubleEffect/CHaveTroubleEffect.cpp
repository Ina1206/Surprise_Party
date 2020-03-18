#include "CHaveTroubleEffect.h"

/******************************************
*		����G�t�F�N�g�N���X.
************/
CHaveTroubleEffect::CHaveTroubleEffect()
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
	m_DispCnt++;
	for (unsigned int sprite = 0; sprite < m_pCSprite.size(); sprite++) {
		if (m_bDispFlag[sprite] == true) {

			//�ړ������֐�.
			Move(sprite);
			continue;
		}

		if (m_DispCnt <= 50) {
			AppeartJudgement(sprite);
			m_DispCnt = 0;
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
		m_fAlpha[sprite] = ALPHA_MAX;
		m_fScale[sprite] = SCALE_MAX;
		m_vPos[sprite] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_bDispFlag[sprite] = false;
		
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
	m_bDispFlag[num] = true;
}

//============================================.
//		�ړ������֐�.
//============================================.
void CHaveTroubleEffect::Move(const int& num)
{
	m_vPos[num].x += cos(60 / 180.0f * PI) * 0.01f;
	m_vPos[num].y += cos(60 / 180.0f * PI) * 0.01f;
}