#include "CSceneUIBase.h"

/*****************************************
*		シーンUIの基底クラス.
****************/
CSceneUIBase::CSceneUIBase()
	: m_pCSpriteUI			()
	, m_vUIPos				()
	, m_vUV					()
	, m_vUIRot				()
	, m_pCCursor			(nullptr)
{
	m_pCCursor.reset(new CChangeSceneCursorUI());
}

CSceneUIBase::~CSceneUIBase()
{
	//解放処理関数.
	Release();
}

//==========================================.
//		描画処理関数.
//==========================================.
void CSceneUIBase::Render()
{
	for (unsigned int sprite = 0; sprite < m_pCSpriteUI.size(); sprite++) {
		//UV座標設定.
		m_pCSpriteUI[sprite]->SetPattern(m_vUV[sprite]);
		//角度.
		m_pCSpriteUI[sprite]->SetRotation(m_vUIRot[sprite]);
		//座標.
		m_pCSpriteUI[sprite]->SetPosition(m_vUIPos[sprite]);
		//描画.
		CDepth_Stencil* m_pCDepthStenceil = CDepth_Stencil::GetDepthStencilInstance();
		m_pCDepthStenceil->SetDepth(false);
		m_pCSpriteUI[sprite]->Render();
		m_pCDepthStenceil->SetDepth(true);
	}

	//ほかのもの描画処理関数.
	RenderOther();
	//カーソルの描画.
	m_pCCursor->Render();

}

//==========================================.
//		要素数初期化処理関数.
//==========================================.
void CSceneUIBase::InitElementCounts()
{
	m_vUIPos.resize(m_pCSpriteUI.size());
	m_vUIRot.resize(m_pCSpriteUI.size());
	m_vUV.resize(m_pCSpriteUI.size());

	//初期値設定.
	for (unsigned int ui = 0; ui < m_pCSpriteUI.size(); ui++) {
		m_vUIPos[ui]	= INIT_POS;
		m_vUIRot[ui]	= INIT_ROT;
		m_vUV[ui]		= INIT_UV;
	}
}

//==========================================.
//		操作時選択文章座標設定処理関数.
//==========================================.
void CSceneUIBase::ControlSelectStringPos()
{
	//初期化.
	for (int sprite = 0; sprite < SELECT_STRING_MAX; sprite++) {
		m_vUIPos[sprite]	= SELECT_STRING_POS;
		SPRITE_STATE SpriteState = m_pCResourceManager->GetSpriteUIState(enSpriteUI::StartString);
		m_vUIPos[sprite].y += SpriteState.Disp.h * sprite;
	}

}

//===========================================.
//		解放処理関数.
//===========================================.
void CSceneUIBase::Release()
{

}