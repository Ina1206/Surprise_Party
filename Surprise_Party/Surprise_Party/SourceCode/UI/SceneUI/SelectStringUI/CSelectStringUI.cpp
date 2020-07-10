#include "CSelectStringUI.h"

/***************************************
*		選択肢UIクラス.
********************/
CSelectStringUI::CSelectStringUI()
	: CSelectStringUI(false)
{

}

CSelectStringUI::CSelectStringUI(const bool& bStartFlag)
	: m_pCSpriteUI		()
	, m_vStringPos		()
	, m_vBeforeMovePos	()
	, m_vLastPos		()
	, m_vGhostCursorPos	(0.0f, 0.0f, 0.0f)
	, m_bStartFlag		(bStartFlag)
	, m_bMoveStopFlag	(false)
	, m_MoveFlag		(0)
{
	//初期化処理関数.
	Init();
}

CSelectStringUI::~CSelectStringUI()
{
	//解放処理関数.
	Release();
}

//======================================.
//		更新処理関数.
//======================================.
void CSelectStringUI::Update()
{
	if (m_MoveFlag & CONTROL_FLAG) {
		//操作時の座標設定処理関数.
		ControlPos();
		return;
	}

	if (m_MoveFlag & MOVE_FLAG) {
		//移動処理関数.
		Move();
		return;
	}

	if (m_MoveFlag & FETCH_FLAG) {
		//取りに行く処理関数.
		Fetch();
	}

}

//======================================.
//		描画処理関数.
//======================================.
void CSelectStringUI::Render()
{
	for (int select = 0; select < SELECT_STRING_MAX; select++) {
		m_pCSpriteUI[select]->SetPosition(m_vStringPos[select]);
		m_pCDepthStencil->SetDepth(false);
		m_pCSpriteUI[select]->Render();
		m_pCDepthStencil->SetDepth(true);
	}
}

//======================================.
//		初期化処理関数.
//======================================.
void CSelectStringUI::Init()
{
	SPRITE_STATE SpriteState = m_pCResourceManager->GetSpriteUIState(enSpriteUI::StartString);

	//開始テクスチャ番号.
	int StartString = static_cast<int>(enSpriteUI::StartString);
	if (m_bStartFlag == false) {
		StartString = static_cast<int>(enSpriteUI::Continue);
	}

	for (int select = 0; select < SELECT_STRING_MAX; select++) {
		//テクスチャ.
		const enSpriteUI m_enSpriteUI = static_cast<enSpriteUI>(StartString + select);
		m_pCSpriteUI.emplace_back(m_pCResourceManager->GetSpriteUI(m_enSpriteUI));

		m_vStringPos.push_back(SELECT_STRING_POS);
		//現在の要素数.
		const int Num = m_vStringPos.size() - 1;
		m_vStringPos[Num].y += SpriteState.Disp.h * Num;

		//最終座標の設定.
		m_vLastPos.push_back(m_vStringPos[Num]);

		//画面外に設定.
		m_vStringPos[Num].x = WND_W;
		//移動前の座標設定.
		m_vBeforeMovePos.push_back(m_vStringPos[Num]);

	}

	m_bStartFlag = false;
}

//======================================.
//		解放処理関数.
//======================================.
void CSelectStringUI::Release()
{

}

//======================================.
//		取りに行く処理関数.
//======================================.
void CSelectStringUI::Fetch()
{
	m_vGhostCursorPos = m_vStringPos[m_pCSpriteUI.size() - 1];
	const SPRITE_STATE SpriteState = m_pCResourceManager->GetSpriteUIState(enSpriteUI::StartString);
	m_vGhostCursorPos.x += SpriteState.Disp.w;
	m_vGhostCursorPos.y -= SpriteState.Disp.h / 2.0f;
}

//======================================.
//		移動処理関数.
//======================================.
void CSelectStringUI::Move()
{
	for (int select = 0; select < SELECT_STRING_MAX; select++) {
		m_vStringPos[select].x = m_vBeforeMovePos[select].x + m_fMoveDistance;

		if (fabsf(m_vStringPos[select].x - m_vLastPos[select].x) <= m_fErrorRange) {
			m_vStringPos[select].x = m_vLastPos[select].x;
			m_bMoveStopFlag = true;
		}
	}
}

//======================================.
//		操作時の座標処理関数.
//======================================.
void CSelectStringUI::ControlPos()
{
	for (int select = 0; select < SELECT_STRING_MAX; select++) {
		m_vStringPos[select] = m_vLastPos[select];
	}
}