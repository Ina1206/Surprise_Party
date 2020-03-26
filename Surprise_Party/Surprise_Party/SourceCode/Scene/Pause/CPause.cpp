#include "CPause.h"

/****************************************
*		一時停止クラス.
************/
CPause::CPause()
	: m_pCSpriteUI			()
	, m_vPos				(nullptr)
	, m_vRot				(nullptr)
	, m_vUV					(nullptr)
	, m_pCResourceManager	(nullptr)
	, m_pCDepthStenceil		(nullptr)
	, m_SelectNum			(0)
	, m_ChangeCnt			(0)
{
	//初期化処理関数.
	Init();
}

CPause::~CPause()
{
	//解放処理関数.
	Release();
}

//========================================.
//		更新処理関数.
//========================================.
void CPause::UpDate()
{
	if (GetAsyncKeyState(VK_UP) & 0x0001) {
		m_SelectNum--;
		if (m_SelectNum < 0) {
			m_SelectNum = 0;
			//SE.
		}
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x0001) {
		m_SelectNum++;	
		if (m_SelectNum >= SELECT_STRING_MAX) {
			m_SelectNum = SELECT_STRING_MAX - 1;
			//SE.
		}
	}

	if (GetAsyncKeyState(VK_RETURN) & 0x0001) {
		m_vUV[CURSOR_NUM] = D3DXVECTOR2(0.0f, 1.0f);
		//SE.
		m_ChangeCnt++;
	}

	if (m_ChangeCnt > 0) {
		m_ChangeCnt++;

		if (m_ChangeCnt >= 10) {
			m_bPauseFlag = false;
			m_vUV[CURSOR_NUM] = D3DXVECTOR2(0.0f, 0.0f);
			m_ChangeCnt = 0;
		}
		return;
	}

	m_vPos[CURSOR_NUM].y = 450.0f + (100.0f * m_SelectNum);
}

//========================================.
//		描画処理関数.
//========================================.
void CPause::Render()
{
	for (unsigned int sprite = 0; sprite < m_pCSpriteUI.size(); sprite++) {
		m_pCSpriteUI[sprite]->SetPattern(m_vUV[sprite]);
		m_pCSpriteUI[sprite]->SetRotation(m_vRot[sprite]);
		m_pCSpriteUI[sprite]->SetPosition(m_vPos[sprite]);
		m_pCDepthStenceil->SetDepth(false);
		m_pCSpriteUI[sprite]->Render();
		m_pCDepthStenceil->SetDepth(true);
	}
}

//========================================.
//		初期化処理関数.
//========================================.
void CPause::Init()
{
	m_pCResourceManager = CResourceManager::GetResourceManagerInstance();
	m_pCDepthStenceil	= CDepth_Stencil::GetDepthStencilInstance();

	m_pCSpriteUI.resize(UI_MAX);
	m_vPos.reset(new D3DXVECTOR3[m_pCSpriteUI.size()]);
	m_vRot.reset(new D3DXVECTOR3[m_pCSpriteUI.size()]);
	m_vUV.reset(new D3DXVECTOR2[m_pCSpriteUI.size()]);

	for (int sprite = 0; sprite < SELECT_STRING_MAX; sprite++) {
		int SpriteNum = static_cast<int>(enSpriteUI::Continue) + sprite;
		m_pCSpriteUI[sprite] = m_pCResourceManager->GetSpriteUI(static_cast<enSpriteUI>(SpriteNum));
	}
	m_pCSpriteUI[CURSOR_NUM] = m_pCResourceManager->GetSpriteUI(enSpriteUI::GhostCursor);
	m_pCSpriteUI[PAUSE_NUM] = m_pCResourceManager->GetSpriteUI(enSpriteUI::Pause);

	for (unsigned int sprite = 0; sprite < m_pCSpriteUI.size(); sprite++) {
		m_vUV[sprite] = D3DXVECTOR2(0.0f, 0.0f);
		m_vRot[sprite] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		if (static_cast<int>(sprite) < SELECT_STRING_MAX) {
			m_vPos[sprite] = D3DXVECTOR3(700.0f, 400.0f + (100.0f * sprite), 0.0f);
			continue;
		}
		m_vPos[sprite] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
	m_vPos[CURSOR_NUM] = D3DXVECTOR3(800.0f, 450.0f, 0.0f);
	m_vPos[PAUSE_NUM] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_vRot[CURSOR_NUM] = D3DXVECTOR3(0.0f, 3.0f, 0.0f);
}

//========================================.
//		解放処理関数.
//========================================.
void CPause::Release()
{
	m_pCDepthStenceil = nullptr;
	m_pCResourceManager = nullptr;
}