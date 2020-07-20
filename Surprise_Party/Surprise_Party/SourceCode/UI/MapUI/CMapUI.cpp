#include "CMapUI.h"

/******************************************
*		マップUIクラス.
**********/
CMapUI::CMapUI()
	: m_pCSpriteUI	(nullptr)
	, m_vColor		(1.0f, 1.0f, 1.0f)
	, m_vPattarn	(0.0f, 0.0f)
{

}

CMapUI::~CMapUI()
{

}

//============================================.
//		描画処理関数.
//============================================.
void CMapUI::Render()
{
	//座標.
	m_pCSpriteUI->SetPosition(m_vPos);
	//角度.
	m_pCSpriteUI->SetRotation(m_vRot);
	//大きさ.
	m_pCSpriteUI->SetScale(m_fScale);
	//透過値.
	m_pCSpriteUI->SetAlpha(m_fAlpha);
	//色.
	m_pCSpriteUI->SetColor(m_vColor);
	//パターン.
	m_pCSpriteUI->SetPattern(m_vPattarn);
	//描画.
	m_pCDepthStencil->SetDepth(false);
	m_pCSpriteUI->Render();
	m_pCDepthStencil->SetDepth(true);
}