#include "CAutoUI.h"

/**********************************
*		自動再生時のUIクラス.
************/
CAutoUI::CAutoUI()
{
	//初期化処理関数.
	Init();
}

CAutoUI::~CAutoUI()
{
	//解放処理関数.
	Release();
}

//=================================.
//		更新処理関数.
//=================================.
void CAutoUI::Update()
{

}

//=================================.
//		描画処理関数.
//=================================.
void CAutoUI::Render()
{
	m_pCSpriteUI->SetAlpha(m_fAlpha);
	m_pCSpriteUI->SetPosition(m_vPos);
	m_pCSpriteUI->Render();
}

//=================================.
//		初期化処理関数.
//=================================.
void CAutoUI::Init()
{
	m_pCSpriteUI = m_pCResourceManager->GetSpriteUI(enSpriteUI::AutoString);
	m_vPos = D3DXVECTOR3(500.0f, 200.0f, 0.0f);
}

//=================================.
//		解放処理関数.
//=================================.
void CAutoUI::Release()
{

}