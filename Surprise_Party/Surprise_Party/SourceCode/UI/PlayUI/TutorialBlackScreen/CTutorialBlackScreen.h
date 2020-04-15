#ifndef CTUTORIAL_BLACK_SCREEN_H
#define CTUTORIAL_BLACK_SCREEN_H

#include "..\CPlayUI.h"

/******************************************
*		チュートリアル時の黒画面.
**************/
class CTutorialBlackScreen
	: public CPlayUI
{
public:
	CTutorialBlackScreen();
	~CTutorialBlackScreen();

	//====================関数======================//.
	void Update();		//更新処理関数.

private:
	//====================関数======================//.
	void Init();		//初期化処理関数.
	void Release();		//解放処理関数.


};

#endif	//#ifndef CTUTORIAL_BLACK_SCREEN_H.