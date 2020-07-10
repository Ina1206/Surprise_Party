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
	//文章移動処理関数.
	MoveString();

	//操作処理関数.
	m_pCCursor->SetChangeWaitFlag(false);
	m_pCCursor->Update();

	//タイトル更新処理関数.
	m_pCTitleStringUI->Update();

	if (m_ControlFlag & CONTROL_WAIT_FLAG) {
		if (GetAsyncKeyState(VK_RETURN) & 0x8000) {
			//操作時選択文章座標設定処理関数.
			ControlSelectStringPos();

			m_ControlFlag = CONTROL_FLAG;
			
			m_pCCursor->SetControlFlag(true);

			//操作フラグに変更.
			m_pCTitleStringUI->SetMoveFlag(m_pCTitleStringUI->CONTROL_FLAG);
		}
		return;
	}

}

//=====================================.
//		選択種類フラグ取得処理関数.
//=====================================.
unsigned int CTitleUI::GetSelectTypeFlag() const 
{
	if (m_pCCursor->GetSelectFinishFlag() == false) {
		return 0;
	}

	//ゲーム開始.
	if (m_pCCursor->GetSelectNum() == 0) {
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

	m_vBeforeMovePos.resize(m_pCSpriteUI.size());

	//要素数初期化処理関数.
	InitElementCounts();

	//選択初期化処理関数.
	InitSelect();

	//操作待機フラグに設定.
	m_ControlFlag = CONTROL_WAIT_FLAG;

	//タイトル文章インスタンス化.
	m_pCTitleStringUI.reset(new CTitleStringUI());
}

//========================================.
//		文章移動処理関数.
//========================================.
void CTitleUI::MoveString()
{

	if (m_pCCursor->GetCarryFlag() == 0) {
		//文章移動準備処理関数.
		PreparingMoveString();
		return;
	}

	//タイトル文字の移動処理.
	const unsigned int CARRY_TITLE_ALL_FLAG = m_pCCursor->LEFT_TITLE_CARRY_FLAG | m_pCCursor->RIGHT_TITLE_CARRY_FLAG;
	if (m_pCCursor->GetCarryFlag() & CARRY_TITLE_ALL_FLAG) {
		//誤差範囲を設定(1フレームごとのPlayerの移動速度を基準).
		m_pCTitleStringUI->SetErrorRange(m_pCCursor->MOVE_SPEED);
		//移動フラグを設定.
		m_pCTitleStringUI->SetMoveFlag(m_pCTitleStringUI->MOVE_FLAG);
		//移動距離を設定.
		m_pCTitleStringUI->SetMoveDistance(m_pCCursor->GetCarryDistance());

		//移動停止処理.
		if (m_pCTitleStringUI->GetStopMoveFlag() == true) {
			m_pCTitleStringUI->SetMoveFlag(0);
			//次の文章番号へ.
			m_pCTitleStringUI->SetChangeNextStringNum();
			//運ぶの終了.
			m_pCCursor->SetFinishCarry();
		}
	}

	int MoveStringNum = 0;
	if (m_pCCursor->GetCarryFlag() & m_pCCursor->LEFT_TITLE_CARRY_FLAG) {
	}
	else if(m_pCCursor->GetCarryFlag() & m_pCCursor->RIGHT_TITLE_CARRY_FLAG){
	}
	else{
		for (int string = MoveStringNum; string < SELECT_STRING_MAX; string++) {
			m_vUIPos[string].x = m_vBeforeMovePos[string].x + m_pCCursor->GetCarryDistance();
		}
	}

	if (MoveStringNum == 0)
	{
	}
	else {
		if (fabsf(m_vUIPos[MoveStringNum].x - m_vTitleLastPos[MoveStringNum - SELECT_STRING_MAX].x) < 1.0f) {
			m_vUIPos[MoveStringNum] = m_vTitleLastPos[MoveStringNum - SELECT_STRING_MAX];
			m_pCCursor->SetFinishCarry();
		}
	}
}

//=========================================.
//		文章移動準備処理関数.
//=========================================.
void CTitleUI::PreparingMoveString() 
{
	const unsigned int FetchFlag = m_pCCursor->GetFetchFlag();
	if (m_pCCursor->GetFetchFlag() == 0) {
		return;
	}
	
	D3DXVECTOR3 GhostCursorCarryPos(0.0f, 0.0f, 0.0f);
	int FetchStringNum = 0;
	if (FetchFlag & m_pCCursor->LEFT_TITLE_FETCH_FLAG) {
	}
	else if(FetchFlag & m_pCCursor->RIGHT_TITLE_CARRY_FLAG){
	}
	else {
		GhostCursorCarryPos = m_vUIPos[FetchStringNum];
		SPRITE_STATE SpriteState = m_pCResourceManager->GetSpriteUIState(enSpriteUI::FinishString);
		GhostCursorCarryPos.y += SpriteState.Disp.h / 2.0f;
		GhostCursorCarryPos.x += SpriteState.Disp.w;
		
	}

	//タイトルの移動準備処理.
	const unsigned int FETCH_TITLE_ALL_FLAG = m_pCCursor->LEFT_TITLE_FETCH_FLAG | m_pCCursor->RIGHT_TITLE_FETCH_FLAG;
	if (m_pCCursor->GetFetchFlag() & FETCH_TITLE_ALL_FLAG) {
		//取りに行くフラグ.
		m_pCTitleStringUI->SetMoveFlag(m_pCTitleStringUI->FETCH_FLAG);
		//お化けが行くべき座標を設定.
		GhostCursorCarryPos = m_pCTitleStringUI->GetFetchGhostPos();
	}

	m_pCCursor->SetCarryStartPos(GhostCursorCarryPos);
}

//==========================================.
//		選択初期化処理関数.
//==========================================.
void CTitleUI::InitSelect()
{
	SPRITE_STATE SpriteState = m_pCResourceManager->GetSpriteUIState(enSpriteUI::StartString);
	for (int select = 0; select < SELECT_STRING_MAX; select++) {
		m_vUIPos[select] = SELECT_STRING_POS;
		m_vUIPos[select].x = WND_W;
		m_vUIPos[select].y += select * SpriteState.Disp.h;
		m_vBeforeMovePos[select] = m_vUIPos[select];
	}
}

//=========================================.
//		他の物描画処理関数.
//=========================================.
void CTitleUI::RenderOther()
{
	//タイトルの描画.
	m_pCTitleStringUI->Render();
}