#ifndef CSPRITEUI_EFFECT_BASE_H
#define CSPRITEUI_EFFECT_BASE_H

#include "..\Global.h"
#include "..\..\Drawing\Resource\CResourceManager.h"

/*****************************************
*	スプライトUIエフェクト基底クラス.
******************/
class CSpriteUIEffectBase
{
public:
	CSpriteUIEffectBase();
	virtual ~CSpriteUIEffectBase();

	//====================関数========================//.
	virtual void Update() = 0;
	virtual void Render() = 0;

protected:
	//====================変数========================//.
	CResourceManager*	m_pCResourceManager;	//読み込み管理クラス.
};

#endif	//#ifndef CSPRITEUI_EFFECT_BASE_H.