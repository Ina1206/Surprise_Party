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
	ControlTitlePos();

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
}

//=======================================.
//		操作時タイトル座標設定処理関数.
//=======================================.
void CTitleUI::ControlTitlePos()
{
	static D3DXVECTOR3 a(0.0f, 0.0f, 0.0f);

	if (GetAsyncKeyState('L') & 0x8000) {
		a.x += 2.1f;
	}
	if (GetAsyncKeyState('J') & 0x8000) {
		a.x -= 2.1f;
	}
	if (GetAsyncKeyState('I') & 0x8000) {
		a.y += 2.1f;
	}
	if (GetAsyncKeyState('K') & 0x8000) {
		a.y -= 2.1f;
	}

	//タイトル番号.
	const int TitleStartNum = SELECT_STRING_MAX;
	for (int title = 0; title < TITLE_MAX; title++) {
		const int TitleNum = title + TitleStartNum;
		D3DXVECTOR3 vPos = D3DXVECTOR3(100.0f, 200.0f, 0.0f) + a;
		SPRITE_STATE ss = m_pCResourceManager->GetSpriteUIState(enSpriteUI::Title);
		vPos.x += ss.Stride.w * title;
		m_vUIPos[TitleNum] = vPos;
	}
}