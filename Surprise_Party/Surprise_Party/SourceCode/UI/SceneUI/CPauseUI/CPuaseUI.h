#ifndef CPAUSE_UI_H
#define CPAUSE_UI_H

#include "..\CSceneUIBase.h"

/**************************************
*		ポーズUIのクラス.
****************/
class CPauseUI
	: public CSceneUIBase
{
public:
	CPauseUI();
	~CPauseUI();

	//=======================定数============================//.
	const D3DXVECTOR3 PAUSE_POS	= D3DXVECTOR3(100.0f, 50.0f, 0.0f);	//ポーズタイトル座標.

	//=======================関数============================//.
	void Update();						//更新処理関数.

private:
	//=======================関数============================//.
	void Init();						//初期化処理関数.
	void RenderSceneTitle();			//シーンタイトル描画処理関数.

};

#endif	//#ifndef CPAUSE_UI_H.