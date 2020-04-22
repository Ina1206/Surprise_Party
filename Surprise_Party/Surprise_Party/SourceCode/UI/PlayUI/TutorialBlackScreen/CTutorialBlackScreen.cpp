#include "CTutorialBlackScreen.h"

/******************************************
*		�`���[�g���A�����̍����.
**************/
CTutorialBlackScreen::CTutorialBlackScreen()
	: m_vCenterPos	(0.0f, 0.0f, 0.0f)
	, m_bDispFlag	(false)
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
	//���W�ݒ菈���֐�.
	SettingPos();
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
	m_vUIPos[SpriteNum].y -= 90.0f;
	m_vUIScale[SpriteNum] = D3DXVECTOR3(1.2f, 1.2f, 1.2f);
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
		m_vUIPos[SpriteNum].x = 0.0f;
		return;
	}

	m_vUIPos[SpriteNum].x = 1300.0f;
	m_vUIRot[SpriteNum].y = 3.1f;
}