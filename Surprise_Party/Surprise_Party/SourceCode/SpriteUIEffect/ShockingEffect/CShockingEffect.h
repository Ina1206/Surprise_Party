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

	//======================定数============================//.
	const float	SIGN_DISP_HIGHT = 20.0f;

	//======================関数============================//.
	void Update();	//更新処理関数.
	void Render();	//描画処理関数.

	//================情報置換処理関数======================//.
	void SetCenterPos(const D3DXVECTOR3& vPos) { m_vCenterPos = vPos; }

private:
	//======================関数============================//.
	void Init();	//初期化処理関数.

	//======================変数============================//.
	CSpriteUI*		m_pCSpriteUI;	//スプライトUI.
	D3DXVECTOR3		m_vPos;			//座標.
	D3DXVECTOR3		m_vCenterPos;	//中央の座標.
	float			m_fScale;		//大きさ.
	bool			m_bDispFlag;	//表示フラグ.
};

#endif	//#ifndef CSHOCKING_EFFECT_H.