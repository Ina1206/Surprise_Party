#include "CPuaseUI.h"

/**************************************
*		ポーズUIのクラス.
****************/
CPauseUI::CPauseUI()
{
	//初期化処理関数.
	Init();
}

CPauseUI::~CPauseUI()
{

}

//=====================================.
//		更新処理関数.
//=====================================.
void CPauseUI::Update()
{
	//操作処理関数.
	Control(true);
}

//=====================================.
//		初期化処理関数.
//=====================================.
void CPauseUI::Init()
{
	//スプライト設定.
	for (int sprite = 0; sprite < SELECT_STRING_MAX; sprite++) {
		//選択文章.
		int SpriteNum = static_cast<int>(enSpriteUI::Continue) + sprite;
		m_pCSpriteUI[sprite] = m_pCResourceManager->GetSpriteUI(static_cast<enSpriteUI>(SpriteNum));
	}
	//シーンタイトル.
	m_pCSpriteUI[SCENE_TITLE_NUM] = m_pCResourceManager->GetSpriteUI(enSpriteUI::Pause);

}