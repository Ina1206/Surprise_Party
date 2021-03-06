#include "CSpriteEffectBase.h"

/*********************************************
*		スプライトのエフェクト基底クラス.
********/
CSpriteEffectBase::CSpriteEffectBase()
	: m_pCSprite			()
	, m_vPos				()
	, m_vRot				()
	, m_vScale				()
	, m_fAlpha				()
	, m_fAngle				()
	, m_vPart				()
	, m_vCenterPos			(0.0f, 0.0f, 0.0f)
	, m_fAlphaSpeed			(0.0f)
	, m_fScalingSpeed		(0.0f)
	, m_pCResourceManager	(nullptr)
	, m_pCDepthStencil		(nullptr)
	, m_bDispFlag			()
	, m_DispTime			(0)
	, m_ChangeAddSub		()
	, m_bPlayFlag			(false)
	, m_bRenderFlag			(false)
	, m_fStartAngle			(0.0f)
	, m_pCPlaySoundManager	(CPlaySoundManager::GetPlaySoundManager())
{
	m_pCResourceManager = CResourceManager::GetResourceManagerInstance();
	m_pCDepthStencil	= CDepth_Stencil::GetDepthStencilInstance();
}

CSpriteEffectBase::~CSpriteEffectBase()
{
	m_pCDepthStencil	= nullptr;
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

		m_pCSprite[sprite]->SetScale(m_vScale[sprite]);
		m_pCSprite[sprite]->SetRotation(m_vRot[sprite]);
		m_pCSprite[sprite]->SetPosition(m_vPos[sprite]);
		m_pCSprite[sprite]->SetAlpha(m_fAlpha[sprite]);
		m_pCSprite[sprite]->SetPatternNo(m_vPart[sprite]);
		m_pCDepthStencil->SetDepth(false);
		m_pCSprite[sprite]->Render(mView, mProj, vCameraPos);
		m_pCDepthStencil->SetDepth(true);
	}
}

//=============================================.
//		要素数設定処理関数.
//=============================================.
void CSpriteEffectBase::SettingElementsCount()
{
	//何もなければ終了.
	if (m_pCSprite.size() == 0) {
		_ASSERT_EXPR(nullptr, L"m_pCSprite.size() == 0");
		return;
	}

	m_vPos.resize(m_pCSprite.size());
	m_vScale.resize(m_pCSprite.size());
	m_vRot.resize(m_pCSprite.size());
	m_fAlpha.resize(m_pCSprite.size());
	m_fAngle.resize(m_pCSprite.size());
	m_fDistance.resize(m_pCSprite.size());
	m_vPart.resize(m_pCSprite.size());
	m_bDispFlag.resize(m_pCSprite.size());
	m_ChangeAddSub.resize(m_pCSprite.size());
}

//==========================================.
//		透過処理関数.
//==========================================.
bool CSpriteEffectBase::ScalingTransparent(const int& num)
{
	//透過処理.
	m_fAlpha[num] += m_fAlphaSpeed * m_ChangeAddSub[num];
	//拡縮処理.
	const float fScale	= m_vScale[num].x + m_fScalingSpeed * m_ChangeAddSub[num];
	m_vScale[num]		= D3DXVECTOR3(fScale, fScale, fScale);

	//加算減少変更処理.
	if (m_fAlpha[num] >= ALPHA_MAX) {
		m_ChangeAddSub[num] *= CHANGE_ADD_SUB;
		return false;
	}

	if (m_ChangeAddSub[num] > CHANGE_ADD_SUB) {
		return false;
	}

	//表示終了.
	if (m_fAlpha[m_fAlpha.size() - 1] <= ALPHA_MIN) {
		return true;
	}
	return false;
}

//===========================================.
//		初期値設定処理関数.
//===========================================.
void CSpriteEffectBase::SettingDefaultValue(const int& num)
{
	m_bDispFlag[num]	= false;
	m_vPos[num]			= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vRot[num]			= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vScale[num]		= SCALE_MIN;
	m_fAlpha[num]		= ALPHA_MIN;
	m_fDistance[num]	= 0.0f;
	m_ChangeAddSub[num] = ADDITION_NUM;
	m_vPart[num]		= D3DXVECTOR2(0.0f, 0.0f);
}

//=========================================.
//		情報置換処理関数(角度).
//=========================================.
void CSpriteEffectBase::SetAngle(const float& angle)
{
	for (unsigned int Num = 0; Num < m_pCSprite.size(); Num++) {
		m_fAngle[Num] = angle;
	}
}