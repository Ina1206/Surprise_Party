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
}

//============================================.
//		��������֐�.
//============================================.
void CTutorialBlackScreen::Release()
{

}