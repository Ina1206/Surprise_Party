#ifndef CSHOCKING_EFFECT_H
#define CSHOCKING_EFFECT_H

#include "..\CSpriteEffectBase.h"

/************************************
*		衝撃エフェクトクラス.
**************/
class CShockingEffect
	: public CSpriteEffectBase
{
public:
	CShockingEffect();
	~CShockingEffect();

	//======================関数=========================//.
	void Update();			//更新処理関数.
	
private:
	//======================関数=========================//.
	void Init();							//初期化処理関数.
	void AppeartJudgement(const int& num);	//表示判定処理関数.
	void Move(const int& num);				//移動処理関数.
};

#endif //#ifndef CSHOCKING_EFFECT_H.