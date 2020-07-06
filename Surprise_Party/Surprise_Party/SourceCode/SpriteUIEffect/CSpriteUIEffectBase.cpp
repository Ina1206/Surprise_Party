#include "CSpriteUIEffectBase.h"

/*****************************************
*	スプライトUIエフェクト基底クラス.
******************/
CSpriteUIEffectBase::CSpriteUIEffectBase()
	: m_pCResourceManager	(CResourceManager::GetResourceManagerInstance())
	, m_pCDepthStencil		(CDepth_Stencil::GetDepthStencilInstance())
{

}

CSpriteUIEffectBase::~CSpriteUIEffectBase()
{

}

