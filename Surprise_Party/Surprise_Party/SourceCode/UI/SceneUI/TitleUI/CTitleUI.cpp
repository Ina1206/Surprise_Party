#include "CTitleUI.h"

/*************************************
*		タイトルUIクラス.
****************/
CTitleUI::CTitleUI()
{
	//初期化処理関数.
	Init();
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
		int StartString = static_cast<int>(enSpriteUI::StartString);
		enSpriteUI m_enSpriteUI = static_cast<enSpriteUI>(StartString + spriteNum);

		m_pCSpriteUI[spriteNum] = m_pCResourceManager->GetSpriteUI(m_enSpriteUI);
	}
	m_pCSpriteUI[SCENE_TITLE_NUM] = m_pCResourceManager->GetSpriteUI(enSpriteUI::Title);
}