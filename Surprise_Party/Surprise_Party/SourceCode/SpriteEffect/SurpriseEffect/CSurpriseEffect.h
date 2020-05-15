#ifndef CSURPRIES_EFFECT_H
#define CSURPRIES_EFFECT_H

#include "..\CSpriteEffectBase.h"

/*****************************************
*		驚きエフェクト.
*******************/
class CSurpriseEffect
	: public CSpriteEffectBase
{
public:
	CSurpriseEffect();
	~CSurpriseEffect();

	//======================定数===========================//.
	const int	SPRITE_MAX	= 3;		//スプライト最大数.
	const float SCALE_SPEED = 0.05f;	//大きさ速度.
	const float ALPHA_SPEED = 0.05f;	//透過速度.
	const float ROT_Y		= 3.1f;		//y軸の角度.
	const float BASE_ANGLE	= 120.0f;	//基本の角度.
	const float ANGLE_WIDTH = 30.0f;	//角度幅.
	const float MOVE_SPEED	= 0.003f;	//移動速度.

	//======================関数===========================//.
	void Update();							//更新処理関数.
	void PlayStartInit(const int& num);		//再生開始初期化処理関数.

	//================情報置換処理関数=====================//.
	void SetDispFlag(const bool& flag) { m_bAllDispFlag = flag; }

private:
	//======================関数===========================//.
	void Init();							//初期化処理関数.
	void Release();							//解放処理関数.
	void AppeartJudgement(const int& num);	//表示判定処理関数.
	void Move(const int& num);				//移動処理関数.

	//======================変数===========================//.
	int					m_DispCnt;		//表示カウント.
	bool				m_bAllDispFlag;	//全体表示フラグ.

};

#endif	//#ifndef CSURPRIES_EFFECT_H.