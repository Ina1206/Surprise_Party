#include "CTitleUI.h"

/*************************************
*		�^�C�g��UI�N���X.
****************/
CTitleUI::CTitleUI()
{

}

CTitleUI::~CTitleUI()
{

}

//=====================================.
//		�����������֐�.
//=====================================.
void CTitleUI::Init()
{
	for (int spriteNum = 0; spriteNum < SELECT_STRING_MAX; spriteNum++) {

	}
	m_pCSpriteUI[SCENE_TITLE_NUM] = m_pCResourceManager->GetSpriteUI(enSpriteUI::Title);
}