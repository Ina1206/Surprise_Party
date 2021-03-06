#include "CGameWorldUI.h"

/***************************************
*		ゲーム内でのUIクラス.
************/
CGameWorldUI::CGameWorldUI()
	: m_pCSprite	(nullptr)
	, m_mView		()
	, m_mProj		()
	, m_vCameraPos	(0.0f, 0.0f, 0.0f)
	, m_vColor		(1.0f, 1.0f, 1.0f)
	, m_vPattarn	(0.0f, 0.0f)
	, m_bDepth		(false)
{

}

CGameWorldUI::~CGameWorldUI()
{

}

//======================================.
//		描画設定処理関数.
//======================================.
void CGameWorldUI::RenderSetting(const D3DXMATRIX& mView, const D3DXMATRIX& mProj, const D3DXVECTOR3& vCameraPos) 
{
	m_mView = mView;
	m_mProj = mProj;
	m_vCameraPos = vCameraPos;
}

//======================================.
//		描画処理関数.
//======================================.
void CGameWorldUI::Render()
{
	//大きさ.
	m_pCSprite->SetScale(D3DXVECTOR3(m_fScale, m_fScale, m_fScale));
	//透過値.
	m_pCSprite->SetAlpha(m_fAlpha);
	//色.
	m_pCSprite->SetColor(m_vColor);
	//座標.
	m_pCSprite->SetPosition(m_vPos);
	//角度.
	m_pCSprite->SetRotation(m_vRot);
	//パターン.
	m_pCSprite->SetPatternNo(m_vPattarn);
	//描画処理.
	if (m_bDepth == true) {
		m_pCSprite->Render(m_mView, m_mProj, m_vCameraPos);
		return;
	}

	m_pCDepthStencil->SetDepth(false);
	m_pCSprite->Render(m_mView, m_mProj, m_vCameraPos);
	m_pCDepthStencil->SetDepth(true);


}