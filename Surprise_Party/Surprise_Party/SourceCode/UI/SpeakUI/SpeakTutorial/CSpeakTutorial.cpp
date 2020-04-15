#include "CSpeakTutorial.h"

CSpeakTutorial::CSpeakTutorial()
	: m_pCSpriteUI			()
	, m_vPos				()
	, m_TutorialFlag		(0)
	, m_bAdvanceCommentFlag	(true)
	, m_SelectMoveCount		(0)
{
	//初期化処理関数.
	Init();
}

CSpeakTutorial::~CSpeakTutorial()
{
	//解放処理関数.
	Release();
}

//======================================.
//		更新処理関数.
//======================================.
void CSpeakTutorial::Update()
{
	if (m_bAdvanceCommentFlag == true) {
		if (GetAsyncKeyState(VK_RETURN) & 0x0001) {
			//コメント一回進める処理.
			AdvanceOnceComment();
		}
	}
}

//=======================================.
//		描画処理関数.
//=======================================.
void CSpeakTutorial::Render()
{
	//吹き出しの描画.
	for (int speak = 0; speak < 2; speak++) {
		//吹き出し種類設定.
		if (m_pCSpriteUI[speak] == m_pCResourceManager->GetSpriteUI(enSpriteUI::Balloon)) {
			m_pCSpriteUI[speak]->SetPattern(D3DXVECTOR2(1.0f, 1.0f));
		}
		m_pCSpriteUI[speak]->SetPosition(m_vPos[speak]);
		m_pCDepthStencil->SetDepth(false);
		m_pCSpriteUI[speak]->Render();
		m_pCDepthStencil->SetDepth(true);
	}

	//テキストの描画.
	m_pCFontResource->SetFontScale(30.0f);
	m_pCFontResource->SetWidthMax(150.0f);
	m_pCFontResource->SetStartPos(m_vPos[2]);
	for (unsigned int font = 0; font < m_stSpeakString[m_SpeakNum].length() / 2; font++) {
		m_pCFontResource->SetAlpha(1.0f, font);
	}
	m_pCFontResource->String_Render();
}

//========================================.
//		一回コメントを進める処理関数.
//========================================.
void CSpeakTutorial::AdvanceOnceComment()
{
	m_SpeakNum++;
	if (static_cast<unsigned int>(m_SpeakNum) >= m_stSpeakString.size()) {
		m_SpeakNum = 0;
	}
	m_pCFontResource->Load(m_stSpeakString[m_SpeakNum]);
	//チュートリアル探索処理関数.
	SerchTutorial();
}

//========================================.
//		選択移動カウント追加処理関数.
//========================================.
void CSpeakTutorial::AddSelectMoveCount()
{
	//例外処理.
	if (m_TutorialFlag & DECIDE_GHOST_FLAG) {
		if (!(m_TutorialFlag & SELECT_GIMMICK_FLAG)) {
			return;
		}
		if (m_TutorialFlag & DECIDE_GIMMICK_FLAG) {
			return;
		}
	}

	m_SelectMoveCount++;

	if (m_SelectMoveCount >= 2) {
		//一回コメントを進める処理関数.
		AdvanceOnceComment();

		m_SelectMoveCount = 0;
	}
}

//========================================.
//		初期化処理関数.
//========================================.
void CSpeakTutorial::Init()
{
	m_pCSpriteUI.push_back(m_pCResourceManager->GetSpriteUI(enSpriteUI::BigGhostIcon));
	m_pCSpriteUI.push_back(m_pCResourceManager->GetSpriteUI(enSpriteUI::Balloon));
	
	for (unsigned int speak = 0; speak < 2; speak++) {
		m_vPos.push_back(D3DXVECTOR3(10.0f + (10.0f * speak), 400.0f - (250.0f * speak), 0.0f));
	}
	
	CFileResource*	m_pCFileResource = CFileResource::GetResourceInstance();
	for (int file = 0; file < m_pCFileResource->GetSringMax(1); file++) {
		m_stSpeakString.push_back(m_pCFileResource->GetSpeakString(1, file, CFileString::enStringType::MainString));
		m_stSelectString.push_back(m_pCFileResource->GetSpeakString(1, file, CFileString::enStringType::SelectString));
	}
	m_pCFontResource->Load(m_stSpeakString[m_SpeakNum]);
	m_vPos.push_back(D3DXVECTOR3(60.0f, 210.0f, 0.0f));
}

//========================================.
//		解放処理関数.
//========================================.
void CSpeakTutorial::Release()
{

}

//========================================.
//		チュートリアル検索処理関数.
//========================================.
void CSpeakTutorial::SerchTutorial()
{
	if (m_stSelectString[m_SpeakNum] == "0") {
		m_bAdvanceCommentFlag = true;
		return;
	}

	if (m_stSelectString[m_SpeakNum] == "GhostSelect") {
		m_TutorialFlag |= SELECT_GHOST_FLAG;
		//コメント進めるの停止.
		m_bAdvanceCommentFlag = false;
		return;
	}

	if (m_stSelectString[m_SpeakNum] == "GhostDecide") {
		m_TutorialFlag |= DECIDE_GHOST_FLAG;
		return;
	}

	if (m_stSelectString[m_SpeakNum] == "ActDecide") {
		m_TutorialFlag |= DECIDE_ACT_FLAG;
		//コメント進めるの停止.
		m_bAdvanceCommentFlag = false;
		return;
	}

	if (m_stSelectString[m_SpeakNum] == "GimmickSelect") {
		m_TutorialFlag |= SELECT_GIMMICK_FLAG;
		m_bAdvanceCommentFlag = false;
	}

	if (m_stSelectString[m_SpeakNum] == "GimmickDecide") {
		m_TutorialFlag |= DECIDE_GIMMICK_FLAG;
		//コメントをEnterで進めることが可能.
		//m_bAdvanceCommentFlag = true;
	}
}