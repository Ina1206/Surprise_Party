#ifndef CQUESTION_EFFECT_H
#define CQUESTION_EFFECT_H

#include "..\CSpriteEffectBase.h"

/************************************
*		疑問エフェクトクラス.
***************/
class CQuestionEffect
	: public CSpriteEffectBase
{
public:
	CQuestionEffect();
	~CQuestionEffect();

	//====================定数========================//.
	const unsigned int	FINISH_MOVE_HORIZONTAL	= (1 << 0);	//横移動終了フラグ.
	const unsigned int	FINISH_MOVE_VERTICAL	= (1 << 1);	//縦移動終了フラグ.

	const float			ACC_SPEAD				= 0.004f;	//加速度の減少速度.
	const float			GRAVITY					= 0.08f;	//重力.
	const float			MOVE_SPEED				= 0.025f;	//移動速度.
	const float			DISTANCE_MAX			= 1.5f;		//距離最大値.

	const float			SCALING_SPEED			= 0.1f;		//拡縮速度.
	const float			SCALING_MIN				= 0.2f;		//拡縮最小値.

	//====================関数========================//.
	void Update();							//更新処理関数.
	void PlayStartInit(const int& num);		//エフェクト開始処理化処理関数.

private:
	//====================関数========================//.
	void Init();							//初期化処理関数.
	void Release();							//解放処理関数.
	void AppeartJudgement(const int& num);	//表示判定処理関数.
	void Move(const int& num);				//移動処理関数.
	void Scaling(const int& num);			//拡縮処理関数.

	//====================変数========================//.
	float			m_fAcc;					//加速度.
	D3DXVECTOR3		m_vStartPos;			//移動開始時の座標.
	unsigned int	m_MoveFinishFlag;		//移動フラグ.

};

#endif	//#ifndef CQUESTION_EFFECT_H.