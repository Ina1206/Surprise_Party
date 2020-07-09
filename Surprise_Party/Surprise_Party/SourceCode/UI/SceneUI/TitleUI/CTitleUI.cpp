#include "CTitleUI.h"

/*************************************
*		タイトルUIクラス.
****************/
CTitleUI::CTitleUI()
	: m_SelectTypeFlag	(0)
	, m_ControlFlag		(0)
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
		const int StartString = static_cast<int>(enSpriteUI::StartString);
		const enSpriteUI m_enSpriteUI = static_cast<enSpriteUI>(StartString + spriteNum);

		m_pCSpriteUI.emplace_back(m_pCResourceManager->GetSpriteUI(m_enSpriteUI));
	}
	m_pCSpriteUI.emplace_back(m_pCResourceManager->GetSpriteUI(enSpriteUI::Title));

	//要素数初期化処理関数.
	InitElementCounts();

	//操作時選択文章座標設定処理関数.
	ControlSelectStringPos();

	//カーソル初期設定座標処理関数.
	InitCursor();
}