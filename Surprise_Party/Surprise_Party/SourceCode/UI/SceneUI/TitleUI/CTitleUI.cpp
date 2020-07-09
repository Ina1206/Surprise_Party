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
	if (m_ControlFlag & CONTROL_WAIT_FLAG) {
		if (GetAsyncKeyState(VK_RETURN) & 0x8000) {
			//操作時タイトル座標設定処理関数.
			ControlTitlePos();
			
			m_ControlFlag = CONTROL_FLAG;
		}
		return;
	}

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
	//選択肢.
	for (int spriteNum = 0; spriteNum < SELECT_STRING_MAX; spriteNum++) {
		const int StartString = static_cast<int>(enSpriteUI::StartString);
		const enSpriteUI m_enSpriteUI = static_cast<enSpriteUI>(StartString + spriteNum);

		m_pCSpriteUI.emplace_back(m_pCResourceManager->GetSpriteUI(m_enSpriteUI));
	}

	//タイトル.
	for (int title = 0; title < TITLE_MAX; title++) {
		m_pCSpriteUI.emplace_back(m_pCResourceManager->GetSpriteUI(enSpriteUI::Title));
	}

	//要素数初期化処理関数.
	InitElementCounts();

	//操作時選択文章座標設定処理関数.
	ControlSelectStringPos();

	//操作時タイトル座標設定処理関数.
	ControlTitlePos();

	//カーソル初期設定座標処理関数.
	InitCursor();
	//カーソル番号.
	const int CURSOR_NUM = static_cast<int>(m_pCSpriteUI.size()) - 1;
	m_vUIPos[CURSOR_NUM] = CURSOR_POS;

	//タイトル.
	for (int title = 0; title < TITLE_MAX; title++) {
		const int TitleNum = title + SELECT_STRING_MAX;
		D3DXVECTOR2 TitleUV = INIT_UV;
		TitleUV.y += 1.0f * title;
		m_vUV[TitleNum] = TitleUV;
	}

	//操作待機フラグに設定.
	m_ControlFlag = CONTROL_WAIT_FLAG;
}

//=======================================.
//		タイトル座標の初期化処理関数.
//=======================================.
void CTitleUI::InitTitlePos()
{

}

//=======================================.
//		操作時タイトル座標設定処理関数.
//=======================================.
void CTitleUI::ControlTitlePos()
{
	//タイトル番号.
	const int TitleStartNum = SELECT_STRING_MAX;
	
	if (m_ControlFlag == 0) {

		//タイトルの最終座標を設定.
		for (int title = 0; title < TITLE_MAX; title++) {
			SPRITE_STATE ss = m_pCResourceManager->GetSpriteUIState(enSpriteUI::Title);
			m_vTitleLastPos.push_back(TITLE_POS);
			m_vTitleLastPos[title].x += (ss.Stride.w ) * title;
		}

		return;
	}

	//タイトルの位置に設定.
	for (int title = 0; title < TITLE_MAX; title++) {
		const int TitleNum = title + TitleStartNum;
		m_vUIPos[TitleNum] = m_vTitleLastPos[title];
	}

}