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

	//=====================定数=======================//.
	const float	INIT_ANGLE		= 90.0f;	//初期角度.
	const float ALPHA_SPEED		= 0.015f;	//透過速度.
	const float	SCALING_SPEED	= 0.015f;	//拡縮速度.
	const float	ANGLE_SPEED		= 2.0f;		//角度加算速度.
	const float	ANGLE_MAX		= 360.0f;	//角度最大値.
	const float	HORIZON_SPEED	= 0.04f;	//横移動速度.
	const float	VERTICAL_SPEED	= 0.05f;	//縦移動速度.
	const float	ROT_SPEED		= 0.05f;	//回転速度.

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