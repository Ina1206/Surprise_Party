#ifndef CAUTO_UI_H
#define CAUTO_UI_H

#include "..\..\CUI.h"

/**********************************
*		自動再生時のUIクラス.
************/
class CAutoUI
	: public CUI
{
public:
	CAutoUI();
	~CAutoUI();

	//=======================定数==========================//.
	const D3DXVECTOR3	POS				= D3DXVECTOR3(900.0f, 665.0f, 0.0f);	//表示座標.
	const unsigned int	APPEAR_FLAG		= (1 << 0);								//現れるフラグ.
	const unsigned int	DISAPPEAR_FLAG	= (1 << 1);								//消えるフラグ.
	const float			ALPHA_SPEED		= 0.02f;								//透過速度.
	const int			CHANGE_DIRECT	= -1;									//方向変更.
	const float			ALPHA_MIN		= 0;									//透過値最小値.

	//=======================関数==========================//.
	void Update();		//更新処理関数.
	void Render();		//描画処理関数.

private:
	//=======================関数==========================//.
	void Init();		//初期化処理関数.
	void Release();		//解放処理関数.

	//=======================変数==========================//.
	CSpriteUI*		m_pCSpriteUI;			//スプライトUI.
	unsigned int	m_FlashingFlag;			//点滅フラグ.
	int				m_TransparentDirect;	//透過方向.

};

#endif	//#ifndef CAUTO_UI_H.