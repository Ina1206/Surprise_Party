#ifndef CSPEAK_BIG_GHOST_H
#define CSPEAK_BIG_GHOST_H

#include "..\CSpeakUI.h"

/**********************************************
*		ビッグゴーストがしゃべるクラス.
*************/
class CSpeakBigGhost
	: public CSpeakUI
{
public:
	CSpeakBigGhost();
	~CSpeakBigGhost();

	//======================関数=======================//.
	void Update();	//更新処理関数.
	void Render();	//描画処理関数.

private:
	//======================関数========================//.
	void Init();	//初期化処理関数.
	void Release();	//解放処理関数.

	
};


#endif	//#ifndef CSPEAK_BIG_GHOST_H.