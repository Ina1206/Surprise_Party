#include "CSpriteEffectBase.h"

/*********************************************
*		スプライトのエフェクト基底クラス.
********/
CSpriteEffectBase::CSpriteEffectBase()
	: m_pCSprite			()
	, m_vPos				()
	, m_vRot				()
	, m_fScale				()
	, m_fAlpha				()
	, m_fAngle()
	, m_vCenterPos			(0.0f, 0.0f, 0.0f)
	, m_pCResourceManager	(nullptr)
	, m_pCDepthStencil		(nullptr)
	, m_bDispFlag			()
	, m_DispCnt				(0)
	, m_ChangeAddSub		()
{
	m_pCResourceManager = CResourceManager::GetResourceManagerInstance();
	m_pCDepthStencil = CDepth_Stencil::GetDepthStencilInstance();
}

CSpriteEffectBase::~CSpriteEffectBase()
{
	m_pCDepthStencil = nullptr;
	m_pCResourceManager = nullptr;
}

//============================================.
//		描画処理関数.
//============================================.
void CSpriteEffectBase::Render(const D3DXMATRIX& mView, const D3DXMATRIX& mProj, const D3DXVECTOR3& vCameraPos)
{
	//何もなければ処理終了.
	if (m_pCSprite.size() == 0) {
		_ASSERT_EXPR(nullptr, L"m_pCSprite.size() == 0");
		return;
	}

	//描画処理.
	for (unsigned int sprite = 0; sprite < m_pCSprite.size(); sprite++) {
		
		_ASSERT_EXPR(m_pCSprite[sprite] != nullptr, L"CSpriteEffectのm_pCSprite == nullptr");

		m_pCSprite[sprite]->SetScale(D3DXVECTOR3(m_fScale[sprite], m_fScale[sprite], m_fScale[sprite]));
		m_pCSprite[sprite]->SetRotation(m_vRot[sprite]);
		m_pCSprite[sprite]->SetPosition(m_vPos[sprite]);
		m_pCSprite[sprite]->SetAlpha(m_fAlpha[sprite]);
		m_pCDepthStencil->SetDepth(false);
		m_pCSprite[sprite]->Render(mView, mProj, vCameraPos);
		m_pCDepthStencil->SetDepth(true);
	}
}