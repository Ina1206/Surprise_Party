#ifndef CSMOKE_EFFECT_H
#define CSMOKE_EFFECT_H

#include "..\CSpriteEffectBase.h"

/*************************************
*		煙エフェクトクラス.
**********/
class CSmokeEffect
	: public CSpriteEffectBase
{
public:
	CSmokeEffect();
	~CSmokeEffect();

	//=====================関数=======================//.
	void Update();							//更新処理関数.
	void PlayStartInit(const int& num);		//エフェクト開始初期化処理関数.
	
private:
	//=====================関数=======================//.
	void Init();							//初期化処理関数.
	void Release();							//解放処理関数.
	void AppeartJudgement(const int& num);	//表示判定処理関数.
	void Move(const int& num);				//移動処理関数.
	void Rotation(const int& num);			//回転処理関数.

	//=====================変数=======================//.
	std::vector<int> m_MoveDirection;		//移動方向.
};

#endif	//#ifndef CSMOKE_EFFECT_H.