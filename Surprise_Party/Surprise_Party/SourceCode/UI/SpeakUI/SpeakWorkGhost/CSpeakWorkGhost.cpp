#include "CSpeakWorkGhost.h"

/*************************************
*		働くお化け会話クラス.
************/
CSpeakWorkGhost::CSpeakWorkGhost()
	: m_pCBalloonSpriteUI	(nullptr)
	, m_pCCommentSpriteUI	()
	, m_GhostTypeNum		(0)
	, m_vPatternNum			()
{
	//初期化処理関数.
	Init();
}

CSpeakWorkGhost::~CSpeakWorkGhost()
{
	//解放処理関数.
	Release();
}

//==================================.
//		更新処理関数.
//==================================.
void CSpeakWorkGhost::Update()
{

}

//==================================.
//		描画処理関数.
//==================================.
void CSpeakWorkGhost::Render()
{
	//吹き出し描画処理関数.
	RenderBalloon();

	//コメント描画処理関数.
	RenderComment();
}

//==================================.
//		初期化処理関数.
//==================================.
void CSpeakWorkGhost::Init()
{
	//スプライトUI設定.
	m_pCBalloonSpriteUI = m_pCResourceManager->GetSpriteUI(enSpriteUI::Balloon);
	m_pCCommentSpriteUI.push_back(m_pCResourceManager->GetSpriteUI(enSpriteUI::DispPaintGhostComment));
	m_pCCommentSpriteUI.push_back(m_pCResourceManager->GetSpriteUI(enSpriteUI::SwitchGhostComment));

	//パターン設定.
	m_vPatternNum.push_back(DISP_GHOST_BALLOON);
	m_vPatternNum.push_back(SWITCH_GHOST_BALLOON);
}

//==================================.
//		解放処理関数.
//==================================.
void CSpeakWorkGhost::Release()
{
	for (int comment = static_cast<int>(m_pCCommentSpriteUI.size()) - 1; comment >= 0; comment--) {
		m_pCCommentSpriteUI[comment] = nullptr;
	}
	m_pCBalloonSpriteUI = nullptr;
}

//==================================.
//		吹き出し描画処理関数.
//==================================.
void CSpeakWorkGhost::RenderBalloon()
{
	const float SCALE_BASE = 1.0f;
	m_pCBalloonSpriteUI->SetPattern(m_vPatternNum[m_GhostTypeNum]);
	m_pCBalloonSpriteUI->SetPosition(BALLOON_POS);
	m_pCBalloonSpriteUI->SetScale(SCALE_BASE);
	m_pCDepthStencil->SetDepth(false);
	m_pCBalloonSpriteUI->Render();
	m_pCDepthStencil->SetDepth(true);
}

//==================================.
//		コメント描画処理関数.
//==================================.
void CSpeakWorkGhost::RenderComment()
{
	m_pCCommentSpriteUI[m_GhostTypeNum]->SetPosition(COMMENT_POS);
	m_pCDepthStencil->SetDepth(false);
	m_pCCommentSpriteUI[m_GhostTypeNum]->Render();
	m_pCDepthStencil->SetDepth(true);
}