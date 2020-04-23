#include "CTutorialBlackScreen.h"

/******************************************
*		�`���[�g���A�����̍����.
**************/
CTutorialBlackScreen::CTutorialBlackScreen()
	: m_vCenterPos			(0.0f, 0.0f, 0.0f)
	, m_vOldCenterPos		(0.0f, 0.0f, 0.0f)
	, m_bDispFlag			(false)
	, m_FadeFlag			(0)
{
	//�����������֐�.
	Init();
}

CTutorialBlackScreen::~CTutorialBlackScreen()
{
	//��������֐�.
	Release();
}

//==========================================.
//		�X�V�����֐�.
//==========================================.
void CTutorialBlackScreen::Update()
{
	if (m_vCenterPos != m_vOldCenterPos) {
		//�t�F�[�h���菈���֐�.
		FadeDecision();
	}

	//���W�ݒ菈���֐�.
	if (!(m_FadeFlag & FADE_OUT_FLAG)) {
		SettingPos();
	}
	m_vOldCenterPos = m_vCenterPos;

	//�t�F�[�h�A�E�g.
	if (m_FadeFlag & FADE_OUT_FLAG) {
		FadeOut();
		return;
	}
	//�t�F�[�h�C��.
	if (m_FadeFlag & FADE_IN_FLAG) {
		m_bDispFlag = true;
		FadeIn();
		return;
	}
}

//===========================================.
//		�����������֐�.
//===========================================.
void CTutorialBlackScreen::Init()
{
	m_pCSpriteUI.push_back(m_pCResourceManager->GetSpriteUI(enSpriteUI::DescriptionBlack));
	//�����ݒ菈��.
	SettingInit();
	const int SpriteNum = static_cast<int>(m_pCSpriteUI.size()) - 1;
	m_vUIPos[SpriteNum].y -= DESCRIPTION_UI_HEIGHT;
	m_vUIScale[SpriteNum] = D3DXVECTOR3(SCALE_BASE, SCALE_BASE, SCALE_BASE);

	m_fUIAlpha[SpriteNum] = ALPHA_MIN;
}

//============================================.
//		��������֐�.
//============================================.
void CTutorialBlackScreen::Release()
{

}

//============================================.
//		���W�ݒ菈���֐�.
//============================================.
void CTutorialBlackScreen::SettingPos()
{

	const int SpriteNum = static_cast<int>(m_pCSpriteUI.size()) - 1;
	if (m_vCenterPos.x < HALF_SCREEN_SIZE) {
		m_vUIPos[SpriteNum].x = NORMAL_POS_X;
		return;
	}

	m_vUIPos[SpriteNum].x = REVERSE_POS_X;
	m_vUIRot[SpriteNum].y = REVERSE_ROT_Y;
}

//============================================.
//		�t�F�[�h���菈���֐�.
//============================================.
void CTutorialBlackScreen::FadeDecision()
{
	if (m_vCenterPos.y <= 0) {
		m_FadeFlag = FADE_OUT_FLAG;
		return;
	}
	
	m_bDispFlag = true;
	m_FadeFlag = FADE_IN_FLAG | FADE_OUT_FLAG;
}

//============================================.
//		�t�F�[�h�C�������֐�.
//============================================.
void CTutorialBlackScreen::FadeIn()
{
	const int SpriteNum = static_cast<int>(m_pCSpriteUI.size()) - 1;
	
	if (m_fUIAlpha[SpriteNum] > ALPHA_MAX) {
		m_fUIAlpha[SpriteNum] = ALPHA_MAX;
		m_FadeFlag &= ~FADE_IN_FLAG;
		return;
	}

	m_fUIAlpha[SpriteNum] += FADE_SPEED;
}

//=============================================.
//		�t�F�[�h�A�E�g�����֐�.
//=============================================.
void CTutorialBlackScreen::FadeOut()
{
	const int SpriteNum = static_cast<int>(m_pCSpriteUI.size()) - 1;

	if (m_fUIAlpha[SpriteNum] < ALPHA_MIN) {
		m_fUIAlpha[SpriteNum] = ALPHA_MIN;
		m_FadeFlag &= ~FADE_OUT_FLAG;
		m_bDispFlag = false;
		return;
	}

	m_fUIAlpha[SpriteNum] -= FADE_SPEED;


}