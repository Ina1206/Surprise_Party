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

	//=================定数===================//.
	const int			SPRITE_MAX		= 6;								//スプライト最大数.
	const D3DXVECTOR3	INT_LOCAL_POS	= D3DXVECTOR3(1.5f, 1.5f, 0.0f);	//初期のローカル座標.
	const int			LINE_MAX		= 3;								//横の行最大数.
	const int			DISP_TIME_MAX	= 20;								//表示時間最大数.
	const float			ALPHA_SPEED		= 0.04f;							//透過速度.
	const float			SCALING_SPEED	= 0.04f;							//拡縮速度.
	const float			START_ANGLE		= 30.0f;							//開始角度.
	const float			ANGLE_WIDTH		= 30.0f;							//角度幅.

	const float			ROT_WIDTH		= 0.3f;								//スプライト角度幅.

	const float			MOVE_SPEED		= 0.05f;							//移動速度.

	const float			ADJUST_ANGLE	= 50.0f;							//微調整の角度

	//=================関数===================//.
	void Update();							//更新処理関数.
	void PlayStartInit(const int& num);		//エフェクト開始処理関数.

private:
	//=================関数===================//.
	void Init();							//初期化処理関数.
	void Release();							//解放処理関数.
	void AppeartJudgement(const int& num);	//表示判定処理関数.
	void Move(const int& num);				//移動処理関数.	

	//=================変数===================//.
	int					m_DispCnt;			//表示カウント.
};

#endif	//#ifndef CHAVE_TROUBLE_EFFECT_H.