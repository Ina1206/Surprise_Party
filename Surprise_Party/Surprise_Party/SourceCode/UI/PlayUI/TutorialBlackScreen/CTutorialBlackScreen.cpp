#include "CTutorialBlackScreen.h"

/******************************************
*		�`���[�g���A�����̍����.
**************/
CTutorialBlackScreen::CTutorialBlackScreen()
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
	m_vUIPos[SpriteNum].y += 20.0f;
	m_vUIScale[SpriteNum] = D3DXVECTOR3(1.1f, 1.1f, 1.1f);
}

//============================================.
//		��������֐�.
//============================================.
void CTutorialBlackScreen::Release()
{

}