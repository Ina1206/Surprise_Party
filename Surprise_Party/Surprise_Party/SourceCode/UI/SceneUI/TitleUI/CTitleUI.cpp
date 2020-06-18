#include "CTitleUI.h"

/*************************************
*		タイトルUIクラス.
****************/
CTitleUI::CTitleUI()
{

}

CTitleUI::~CTitleUI()
{

}

//=====================================.
//		初期化処理関数.
//=====================================.
void CTitleUI::Init()
{
	for (int spriteNum = 0; spriteNum < SELECT_STRING_MAX; spriteNum++) {

	}
	m_pCSpriteUI[SCENE_TITLE_NUM] = m_pCResourceManager->GetSpriteUI(enSpriteUI::Title);
}