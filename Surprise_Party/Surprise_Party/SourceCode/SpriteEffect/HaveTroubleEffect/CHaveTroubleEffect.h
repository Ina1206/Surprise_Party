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
	const D3DXVECTOR3	INT_LOCAL_POS	= D3DXVECTOR3(0.0f, 1.5f, 0.0f);	//初期のローカル座標.

	//=================関数===================//.
	void Update();		//更新処理関数.
	
private:
	//=================関数===================//.
	void Init();							//初期化処理関数.
	void Release();							//解放処理関数.
	void AppeartJudgement(const int& num);	//表示判定処理関数.
	void Move(const int& num);				//移動処理関数.	

	//=================変数===================//.
	int	m_DispCnt;							//表示カウント.
};

#endif	//#ifndef CHAVE_TROUBLE_EFFECT_H.