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

	//===============定数=================//.
	const int			BUBBLE_MAX			= 4;								//泡最大数.
	const int			Z_MAX				= 2;								//Z最大数.
	const int			ALL_SPRITE_MAX		= BUBBLE_MAX + Z_MAX;				//全てのスプライト最大数.
	const D3DXVECTOR3	INIT_LOCAL_POS		= D3DXVECTOR3(-2.3f, 2.0f, 0.0f);	//初期のローカル座標.

	const float			START_ANGLE			= 60.0f;							//開始角度.
	const float			ANGLE_WIDTH			= 20.0f;							//角度幅.
	const float			CIRCLE_HALF_ANGLE	= 180.0f;							//半円の角度.
	const float			MOVE_SPEED			= 0.01f;							//移動速度.
	const int			LINE_MAX			= 3;								//横の行最大数.
	const float			SLEEP_Z_NUM			= 1;								//眠りマークの番号.
	const float			ANGLE_MOVE_SPEED	= 5.0f;								//角度移動速度.
	const float			APPEAR_TIME			= 30;								//表示時間.



	//===============関数=================//.
	void Update();		//更新処理関数.

private:
	//===============関数=================//.
	void Init();								//初期化処理関数.
	void Release();								//解放処理関数.
	void AppeartJudgement(const int& num);		//表示判断処理関数.
	void Move(const int& num);					//移動処理関数.

};

#endif	//#ifndef CSLEEP_EFFECT_H.