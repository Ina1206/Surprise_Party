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

	//=================関数====================//.
	void Update();							//更新処理関数.
	void PlayStartInit(const int& num);		//エフェクト開始初期化処理関数.

private:
	//=================関数====================//.
	void Init();							//初期化処理関数.
	void Release();							//解放処理関数.
	void AppeartJudgement(const int& num);	//表示判定処理関数.
	void Move(const int& num);				//移動処理関数.


};


#endif	//#ifndef CMOVE_NOTE_EFFECT_H.