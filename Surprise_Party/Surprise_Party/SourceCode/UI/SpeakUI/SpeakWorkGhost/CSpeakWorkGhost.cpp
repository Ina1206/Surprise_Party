#include "CSpeakWorkGhost.h"

/*************************************
*		働くお化け会話クラス.
************/
CSpeakWorkGhost::CSpeakWorkGhost()
	: m_pCSpriteUI	(nullptr)
	, m_vPos		(0.0f, 0.0f, 0.0f)
	, m_GhostTypeNum(0)
	, m_vPatternNum	()
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
	m_pCSpriteUI->SetPattern(m_vPatternNum[m_GhostTypeNum]);
	m_pCSpriteUI->SetPosition(m_vPos);
	m_pCDepthStencil->SetDepth(false);
	m_pCSpriteUI->Render();
	m_pCDepthStencil->SetDepth(true);
}

//==================================.
//		初期化処理関数.
//==================================.
void CSpeakWorkGhost::Init()
{
	m_pCSpriteUI = m_pCResourceManager->GetSpriteUI(enSpriteUI::Balloon);

	m_vPos = D3DXVECTOR3(650.0f, 100.0f, 0.0f);

	m_vPatternNum.push_back(D3DXVECTOR2(0.0f, 0.0f));
	m_vPatternNum.push_back(D3DXVECTOR2(1.0f, 0.0f));
}

//==================================.
//		解放処理関数.
//==================================.
void CSpeakWorkGhost::Release()
{
	m_pCSpriteUI = nullptr;
}