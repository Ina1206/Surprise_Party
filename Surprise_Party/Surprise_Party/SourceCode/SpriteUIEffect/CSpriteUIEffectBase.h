#ifndef CSPRITEUI_EFFECT_BASE_H
#define CSPRITEUI_EFFECT_BASE_H

#include "..\Global.h"

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
	
};

#endif	//#ifndef CSPRITEUI_EFFECT_BASE_H.