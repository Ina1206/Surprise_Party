#include "CSpriteUIEffectBase.h"

/*****************************************
*	�X�v���C�gUI�G�t�F�N�g���N���X.
******************/
CSpriteUIEffectBase::CSpriteUIEffectBase()
	: m_pCResourceManager	(CResourceManager::GetResourceManagerInstance())
	, m_pCDepthStencil		(CDepth_Stencil::GetDepthStencilInstance())
{

}

CSpriteUIEffectBase::~CSpriteUIEffectBase()
{

}

