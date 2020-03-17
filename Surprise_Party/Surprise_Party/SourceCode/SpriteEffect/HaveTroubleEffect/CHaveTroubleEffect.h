#ifndef CHAVE_TROUBLE_EFFECT_H
#define CHAVE_TROUBLE_EFFECT_H

#include "..\CSpriteEffectBase.h"

/******************************************
*		困りエフェクトクラス.
************/
class CHaveTroubleEffect
	: public CSpriteEffectBase
{
public:
	CHaveTroubleEffect();
	~CHaveTroubleEffect();

	//=================関数===================//.
	void Update();		//更新処理関数.
	
private:
	//=================関数===================//.
	void Init();		//初期化処理関数.
	void Release();		//解放処理関数.


};

#endif	//#ifndef CHAVE_TROUBLE_EFFECT_H.