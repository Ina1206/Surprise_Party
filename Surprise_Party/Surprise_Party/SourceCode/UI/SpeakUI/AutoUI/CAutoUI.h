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

	//=======================関数==========================//.
	void Update();		//更新処理関数.
	void Render();		//描画処理関数.

private:
	//=======================関数==========================//.
	void Init();		//初期化処理関数.
	void Release();		//解放処理関数.

	//=======================変数==========================//.
	CSpriteUI*	m_pCSpriteUI;	//スプライトUI.


};

#endif	//#ifndef CAUTO_UI_H.