#include "CSpeakTutorial.h"

CSpeakTutorial::CSpeakTutorial()
	: m_pCSpriteUI	()
	, m_vPos		()
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
		m_pCSpriteUI[speak]->SetPosition(m_vPos[speak]);
		m_pCDepthStencil->SetDepth(false);
		m_pCSpriteUI[speak]->Render();
		m_pCDepthStencil->SetDepth(true);

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
		m_vPos.push_back(D3DXVECTOR3(10.0f + (10.0f * (speak * 2)), 400.0f - (250.0f * (speak % 2)), 0.0f));
	}
	
}

//========================================.
//		解放処理関数.
//========================================.
void CSpeakTutorial::Release()
{

}