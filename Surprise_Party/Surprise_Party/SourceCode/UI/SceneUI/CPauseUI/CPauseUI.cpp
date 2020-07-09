#include "CPuaseUI.h"

/**************************************
*		�|�[�YUI�̃N���X.
****************/
CPauseUI::CPauseUI()
{
	//�����������֐�.
	Init();
}

CPauseUI::~CPauseUI()
{

}

//=====================================.
//		�X�V�����֐�.
//=====================================.
void CPauseUI::Update()
{
	//���쏈���֐�.
	Control(true);
}

//=====================================.
//		�����������֐�.
//=====================================.
void CPauseUI::Init()
{
	//�X�v���C�g�ݒ�.
	for (int sprite = 0; sprite < SELECT_STRING_MAX; sprite++) {
		//�I�𕶏�.
		int SpriteNum = static_cast<int>(enSpriteUI::Continue) + sprite;
		m_pCSpriteUI[sprite] = m_pCResourceManager->GetSpriteUI(static_cast<enSpriteUI>(SpriteNum));
	}
	//�V�[���^�C�g��.
	m_pCSpriteUI[SCENE_TITLE_NUM] = m_pCResourceManager->GetSpriteUI(enSpriteUI::Pause);

}