#include "CTitleUI.h"

/*************************************
*		タイトルUIクラス.
****************/
CTitleUI::CTitleUI()
	: m_SelectTypeFlag	(0)
{
	//初期化処理関数.
	Init();
}

CTitleUI::~CTitleUI()
{

}

//=====================================.
//		更新処理関数.
//=====================================.
void CTitleUI::Update()
{
	//操作処理関数.
	Control(false);
}

//=====================================.
//		選択種類フラグ取得処理関数.
//=====================================.
unsigned int CTitleUI::GetSelectTypeFlag() const 
{
	if (m_bSelectFinishFlag == false) {
		return 0;
	}

	//ゲーム開始.
	if (m_SelectNum == 0) {
		return GAME_START_FLAG;
	}

	//ゲーム終了.
	return GAME_FINISH_FLAG;
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