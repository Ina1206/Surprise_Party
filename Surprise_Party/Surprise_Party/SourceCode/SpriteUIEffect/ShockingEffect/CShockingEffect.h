#ifndef CSHOCKING_EFFECT_H
#define CSHOCKING_EFFECT_H

#include "..\CSpriteUIEffectBase.h"

/*************************************
*		衝撃エフェクトクラス.
****************/
class CShockingEffect
	: public CSpriteUIEffectBase
{
public:
	CShockingEffect();
	~CShockingEffect();

	//======================関数============================//.
	void Update();	//更新処理関数.
	void Render();	//描画処理関数.

private:
	//======================変数============================//.
	D3DXVECTOR3 m_vPos;		//座標.
	float		m_fAlpha;	//透過値.
	float		m_fScale;	//大きさ.

};

#endif	//#ifndef CSHOCKING_EFFECT_H.