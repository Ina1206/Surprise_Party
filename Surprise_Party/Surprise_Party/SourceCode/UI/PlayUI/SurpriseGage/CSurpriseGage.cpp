#include "CSurpriseGage.h"

CSurpriseGage::CSurpriseGage()
	: CSurpriseGage(0)
{

}

CSurpriseGage::CSurpriseGage(int SurprisePointMax)
	: m_SurprisePoint		(0)
	, m_SurprisePointMax	(SurprisePointMax)
	, m_bSurprisePointMax	(false)
	, m_bBorusGetFlag		(false)
{
	//�����������֐�.
	Init();
}

CSurpriseGage::~CSurpriseGage()
{
	//��������֐�.
	Release();
}

//======================================.
//		�X�V�����֐�.
//======================================.
void CSurpriseGage::Update()
{
	if (m_SurprisePoint >= m_SurprisePointMax) {
		m_SurprisePoint = m_SurprisePointMax;
		m_bSurprisePointMax = true;

		//�X�^���v�\�������֐�.
		StampDisp();
	}

	if (m_SurprisePoint >= m_SurprisePointMax * GET_BONUS_POINT_RATIO) {
		//�ʒm�ړ������֐�.
		InfomMove();
		
		m_bBorusGetFlag = true;
	}

	m_vUIScale[GAGE_NUM].x = static_cast<float>(m_SurprisePoint) / static_cast<float>(m_SurprisePointMax);
}

//======================================.
//		�����|�C���g�ǉ������֐�.
//======================================.
void CSurpriseGage::AddSurprisePoint(int Point)
{
	m_SurprisePoint += Point;
}

//======================================.
//		�����������֐�.
//======================================.
void CSurpriseGage::Init()
{
	//�T�C�Y.
	m_pCSpriteUI.resize(UI_MAX);
	//�����ݒ菈���֐�.
	SettingInit();

	//����������.
	m_vUIScale[STAMP_NUM]	= SCALE_MIN;

	m_fUIAlpha[INFOM_NUM]	= ALPHA_MIN;

	m_vUIPos[GAGE_GROUND_NUM]	= GAGE_GROUND_POS;
	m_vUIPos[GAGE_NUM]			= GAGE_POS;
	m_vUIPos[STAMP_NUM]			= STAMP_POS;
	m_vUIPos[INFOM_NUM]			= INFOM_POS;

	//�A�h���X�擾����.
	m_pCSpriteUI[GAGE_GROUND_NUM]	= m_pCResourceManager->GetSpriteUI(enSpriteUI::GageGround);
	m_pCSpriteUI[GAGE_NUM]			= m_pCResourceManager->GetSpriteUI(enSpriteUI::Gage);
	m_pCSpriteUI[STAMP_NUM]			= m_pCResourceManager->GetSpriteUI(enSpriteUI::ThankYouStamp);
	m_pCSpriteUI[INFOM_NUM]			= m_pCResourceManager->GetSpriteUI(enSpriteUI::ExtendedNotification);
}

//======================================.
//		��������֐�.
//======================================.
void CSurpriseGage::Release()
{
	for (int ui = UI_MAX - 1; ui >= 0; ui--) {
		m_pCSpriteUI[ui] = nullptr;
	}
}

//=====================================.
//		�X�^���v�\�������֐�.
//=====================================.
void CSurpriseGage::StampDisp()
{
	
	if (m_vUIScale[STAMP_NUM].x <= SCALE_MIN.x) {
		m_vUIScale[STAMP_NUM] = SCALE_MAX;
		return;
	}

	//�K��l�܂ŏ������Ȃ�ƏI��.
	if (m_vUIScale[STAMP_NUM].x <= SHRINK_STOP_SCALE.x) {
		m_vUIScale[STAMP_NUM] = SHRINK_STOP_SCALE;
		return;
	}

	m_vUIScale[STAMP_NUM] -= SHRINK_SPEED;
}

//==========================================.
//		�ʒm�ړ������֐�.
//==========================================.
void CSurpriseGage::InfomMove()
{
	m_vUIPos[INFOM_NUM].y += INFOM_MOVE_SPEED;

	//���ߒl���グ�鏈��.
	if (m_vUIPos[INFOM_NUM].y <= CHANGE_ALPHA_HEIGHT) {
		m_fUIAlpha[INFOM_NUM] += INFOM_ALPHA_SPEED;
		if (m_fUIAlpha[INFOM_NUM] >= ALPHA_MAX) {
			m_fUIAlpha[INFOM_NUM] = ALPHA_MAX;
		}
		return;
	}

	//���ߒl�����鏈��.
	m_fUIAlpha[INFOM_NUM] -= INFOM_ALPHA_SPEED;
	if (m_fUIAlpha[INFOM_NUM] <= ALPHA_MIN) {
		m_fUIAlpha[INFOM_NUM] = ALPHA_MIN;
	}

}