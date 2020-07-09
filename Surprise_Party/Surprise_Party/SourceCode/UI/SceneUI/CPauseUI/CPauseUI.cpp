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
	//カーソルの更新処理関数.
	m_pCCursor->SetChangeWaitFlag(true);
	m_pCCursor->SetControlFlag(true);
	m_pCCursor->Update();
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
		m_pCSpriteUI.emplace_back(m_pCResourceManager->GetSpriteUI(static_cast<enSpriteUI>(SpriteNum)));
	}
	//シーンタイトル.
	m_pCSpriteUI.emplace_back(m_pCResourceManager->GetSpriteUI(enSpriteUI::Pause));

	//要素数初期化処理関数.
	InitElementCounts();

	//操作時選択座標設定処理関数.
	ControlSelectStringPos();
}