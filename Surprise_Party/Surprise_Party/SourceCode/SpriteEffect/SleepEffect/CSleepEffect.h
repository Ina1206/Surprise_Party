#ifndef CSLEEP_EFFECT_H
#define CSLEEP_EFFECT_H

#include "..\CSpriteEffectBase.h"

/********************************************
*		寝ているエフェクトクラス.
****************/
class CSleepEffect
	: public CSpriteEffectBase
{
public:
	CSleepEffect();
	~CSleepEffect();

	//===============関数=================//.
	void Update();		//更新処理関数.

private:
	//===============関数=================//.
	void Init();		//初期化処理関数.
	void Release();		//解放処理関数.


};

#endif	//#ifndef CSLEEP_EFFECT_H.