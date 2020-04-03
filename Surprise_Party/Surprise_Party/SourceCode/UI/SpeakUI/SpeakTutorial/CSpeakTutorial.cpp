#include "CSpeakTutorial.h"

CSpeakTutorial::CSpeakTutorial()
	: m_pCSpriteUI	()
	, m_vPos		()
	, m_stSpeak		()
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

}

//=======================================.
//		描画処理関数.
//=======================================.
void CSpeakTutorial::Render()
{
	for (int speak = 0; speak < 2; speak++) {
		if (m_pCSpriteUI[speak] == m_pCResourceManager->GetSpriteUI(enSpriteUI::Balloon)) {
			m_pCSpriteUI[speak]->SetPattern(D3DXVECTOR2(1.0f, 1.0f));
		}
		m_pCSpriteUI[speak]->SetPosition(m_vPos[speak]);
		m_pCDepthStencil->SetDepth(false);
		m_pCSpriteUI[speak]->Render();
		m_pCDepthStencil->SetDepth(true);
	}

	m_pCFontResource->SetFontScale(30.0f);
	m_pCFontResource->SetWidthMax(150.0f);
	m_pCFontResource->SetStartPos(m_vPos[2]);
	for (unsigned int font = 0; font < m_stSpeak[1].size(); font++) {
		m_pCFontResource->SetAlpha(1.0f, font);
	}
	m_pCFontResource->String_Render();
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
		m_stSpeak.push_back(m_pCFileResource->GetSpeakString(1, file, CFileString::enStringType::MainString));
	}
	m_pCFontResource->Load(m_stSpeak[0]);
	m_vPos.push_back(D3DXVECTOR3(60.0f, 210.0f, 0.0f));
}

//========================================.
//		解放処理関数.
//========================================.
void CSpeakTutorial::Release()
{

}