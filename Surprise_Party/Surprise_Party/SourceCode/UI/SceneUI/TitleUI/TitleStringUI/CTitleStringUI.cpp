#include "CTitleStringUI.h"

/*********************************************
*		タイトル文章UIクラス.
*******************/
CTitleStringUI::CTitleStringUI()
	: m_pCSpriteUI			()
	, m_vTitlePos			()
	, m_vTitleUV			()
	, m_vBeforeMovePos		()
	, m_vLastPos			()
	, m_vFetchGhostPos		(0.0f, 0.0f, 0.0f)
	, m_FetchStringNum		(0)
	, m_fMoveDistance		(0.0f)
	, m_bStopFlag			()
	, m_fErrorRange			(0.0f)
	, m_MoveFlag			(0)
	, m_pCPlaySoundManager	(CPlaySoundManager::GetPlaySoundManager())
{
	//初期化処理関数.
	Init();
}

CTitleStringUI::~CTitleStringUI()
{
	//解放処理関数.
	Release();
}

//=========================================.
//		更新処理関数.
//=========================================.
void CTitleStringUI::Update()
{
	if (m_MoveFlag & CONTROL_FLAG) {
		//操作時の座標設定.
		ControlPos();
		return;
	}

	if (m_MoveFlag & FETCH_FLAG) {
		//取りに行く座標処理関数.
		FetchPos();
		return;
	}

	if (m_MoveFlag & MOVE_FLAG) {
		//移動処理関数.
		Move();
	}
}

//=========================================.
//		描画処理関数.
//=========================================.
void CTitleStringUI::Render()
{
	for (int title = 0; title < TITLE_STRING_MAX; title++) {
		//座標.
		m_pCSpriteUI[title]->SetPosition(m_vTitlePos[title]);
		//UV.
		m_pCSpriteUI[title]->SetPattern(m_vTitleUV[title]);
		//描画.
		m_pCDepthStencil->SetDepth(false);
		m_pCSpriteUI[title]->Render();
		m_pCDepthStencil->SetDepth(true);
	}
}

//==========================================.
//		初期化処理関数.
//==========================================.
void CTitleStringUI::Init()
{
	//スプライトUI情報.
	SPRITE_STATE SpriteState = m_pCResourceManager->GetSpriteUIState(enSpriteUI::Title);

	//値を初期化処理.
	for (int title = 0; title < TITLE_STRING_MAX; title++) {
		m_pCSpriteUI.push_back(m_pCResourceManager->GetSpriteUI(enSpriteUI::Title));
		m_vTitleUV.push_back(D3DXVECTOR2(0.0f, 1.0f * title));
		m_vTitlePos.push_back(TITLE_POS);

		//画面外に配置する処理.
		m_vTitlePos[title].x = WND_W;
		if (title == 0) {
			m_vTitlePos[title].x = -SpriteState.Disp.w;
		}

		m_vBeforeMovePos.push_back(m_vTitlePos[title]);

		m_vLastPos.push_back(TITLE_POS);
		m_vLastPos[title].x += SpriteState.Disp.w * title;

		m_bStopFlag.push_back(false);
	}
}

//==========================================.
//		解放処理関数.
//==========================================.
void CTitleStringUI::Release()
{

}

//==========================================.
//		操作時の座標処理関数.
//==========================================.
void CTitleStringUI::ControlPos()
{
	for (int title = 0; title < TITLE_STRING_MAX; title++) {
		m_vTitlePos[title] = m_vLastPos[title];
	}
}

//==========================================.
//		取りに行く座標処理関数.
//==========================================.
void CTitleStringUI::FetchPos()
{
	m_vFetchGhostPos = m_vTitlePos[m_FetchStringNum];

	//一番最後の文字は３分の２のところに配置.
	if (m_FetchStringNum == m_vTitlePos.size() - 1) {
		SPRITE_STATE SpriteState = m_pCResourceManager->GetSpriteUIState(enSpriteUI::Title);
		m_vFetchGhostPos.x += (SpriteState.Disp.w / 3.0f) * 2.0f;
	}
}

//==========================================.
//		移動処理関数.
//==========================================.
void CTitleStringUI::Move()
{
	m_vTitlePos[m_FetchStringNum].x = m_vBeforeMovePos[m_FetchStringNum].x + m_fMoveDistance;

	//移動終了.
	if (fabsf(m_vTitlePos[m_FetchStringNum].x - m_vLastPos[m_FetchStringNum].x) < m_fErrorRange) {
		m_vTitlePos[m_FetchStringNum] = m_vLastPos[m_FetchStringNum];
		if (m_bStopFlag[m_FetchStringNum] == false) {
			m_pCPlaySoundManager->SetPlaySE(enSEType::EndingString);
		}
		m_bStopFlag[m_FetchStringNum] = true;
	}
}