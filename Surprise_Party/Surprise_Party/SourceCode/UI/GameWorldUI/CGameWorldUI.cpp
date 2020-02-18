#include "CGameWorldUI.h"

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
//		•`‰æÝ’èˆ—ŠÖ”.
//======================================.
void CGameWorldUI::RenderSetting(const D3DXMATRIX& mView, const D3DXMATRIX& mProj, const D3DXVECTOR3& vCameraPos) 
{
	m_mView = mView;
	m_mProj = mProj;
	m_vCameraPos = vCameraPos;
}

//======================================.
//		•`‰æˆ—ŠÖ”.
//======================================.
void CGameWorldUI::Render()
{
	//‘å‚«‚³.
	m_pCSprite->SetScale(D3DXVECTOR3(m_fScale, m_fScale, m_fScale));
	//“§‰ß’l.
	m_pCSprite->SetAlpha(m_fAlpha);
	//F.
	m_pCSprite->SetColor(m_vColor);
	//À•W.
	m_pCSprite->SetPosition(m_vPos);
	//Šp“x.
	m_pCSprite->SetRotation(m_vRot);
	//ƒpƒ^[ƒ“.
	m_pCSprite->SetPatternNo(m_vPattarn);
	//•`‰æˆ—.
	if (m_bDepth == true) {
		m_pCSprite->Render(m_mView, m_mProj, m_vCameraPos);
		return;
	}

	m_pCDepthStencil->SetDepth(false);
	m_pCSprite->Render(m_mView, m_mProj, m_vCameraPos);
	m_pCDepthStencil->SetDepth(true);


}