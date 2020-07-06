#ifndef CSPRITEUI_EFFECT_BASE_H
#define CSPRITEUI_EFFECT_BASE_H

#include "..\Global.h"
#include "..\Drawing\Resource\CResourceManager.h"
#include "..\Drawing\Sprite\CDepth_Stencil.h"

/*****************************************
*	スプライトUIエフェクト基底クラス.
******************/
class CSpriteUIEffectBase
{
public:
	CSpriteUIEffectBase();
	virtual ~CSpriteUIEffectBase();

	//====================定数========================//.
	const float	SCALE_MAX = 1.0f;	//大きさ最大値.
	const float SCALE_MIN = 0.0f;	//大きさ最小値.
	const float	ALPHA_MAX = 1.0f;	//透過値最大値.
	const float ALPHA_MIN = 0.0f;	//透過値最小値.

	//====================関数========================//.
	virtual void Update() = 0;
	virtual void Render() = 0;

protected:
	//====================変数========================//.
	CResourceManager*	m_pCResourceManager;	//読み込み管理クラス.
	CDepth_Stencil*		m_pCDepthStencil;		//デプスステンシル.
};

#endif	//#ifndef CSPRITEUI_EFFECT_BASE_H.