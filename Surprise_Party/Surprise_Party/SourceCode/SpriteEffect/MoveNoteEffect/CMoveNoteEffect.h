#ifndef CMOVE_NOTE_EFFECT_H
#define CMOVE_NOTE_EFFECT_H

#include "..\CSpriteEffectBase.h"

/*************************************
*	音符移動エフェクトクラス.
*************/
class CMoveNoteEffect
	: public CSpriteEffectBase
{
public:
	CMoveNoteEffect();
	~CMoveNoteEffect();

	//=================定数====================//.
	const unsigned int	SCALE_FLAG		= (1 << 0);					//拡大フラグ.
	const unsigned int	SCALE_DOWN_FLAG	= (1 << 1);					//縮小フラグ.
	const int			NOTE_NUM		= 0;						//音符番号.
	const D3DXVECTOR2	NOTE_UV_POS		= D3DXVECTOR2(0.0f, 1.0f);	//音符UV座標.
	const int			TIME_MAX		= 20;						//時間最大値.	
	const float			ALPHA_SPEED		= 0.02f;					//透過値速度.
	const float			SCALING_SPEED	= 0.02f;					//拡縮速度.
	const float			DISTANCE		= 0.06f;					//距離.

	//=================関数====================//.
	void Update();									//更新処理関数.
	void PlayStartInit(const int& num);				//エフェクト開始初期化処理関数.

private:
	//=================関数====================//.
	void Init();									//初期化処理関数.
	void Release();									//解放処理関数.
	void AppeartJudgement(const int& num);			//表示判定処理関数.
	void Move(const int& num);						//移動処理関数.

	//=================変数====================//.
	std::vector<unsigned int> m_ScalingFlag;		//拡大縮小フラグ.
};


#endif	//#ifndef CMOVE_NOTE_EFFECT_H.