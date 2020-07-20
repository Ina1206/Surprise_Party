#include "CSurpriseDegreeBase.h"

/****************************************
*		驚かし度の基底クラス.
**********************/
CSurpriseDegreeBase::CSurpriseDegreeBase()
	: m_pCSpriteUI			(nullptr)
	, m_vEatchSizeScale		(EATCH_SCALE_MAX)
	, m_bDispFlag			(false)
	, m_bDisplayAllAtOnce	(false)
	, m_DipslayNum			(0)
	, m_pCPlaySoundManager	(CPlaySoundManager::GetPlaySoundManager())
{

}

CSurpriseDegreeBase::~CSurpriseDegreeBase()
{

}

//========================================.
//		描画処理関数.
//========================================.
void CSurpriseDegreeBase::Render()
{
	//透過値.
	m_pCSpriteUI->SetAlpha(m_fAlpha);
	//それぞれの大きさ.
	m_pCSpriteUI->SetEachSizeScale(m_vEatchSizeScale);
	//座標設定.
	m_pCSpriteUI->SetPosition(m_vPos);
	//描画.
	m_pCDepthStencil->SetDepth(false);
	m_pCSpriteUI->Render();
	m_pCDepthStencil->SetDepth(true);
}
