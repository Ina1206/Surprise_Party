#ifndef CSPEAK_TUTORIAL_H
#define CSPEAK_TUTORIAL_H

#include "..\CSpeakUI.h"

/******************************************
*		チュートリアル会話.
***************/
class CSpeakTutorial
	: public CSpeakUI
{
public:
	CSpeakTutorial();
	~CSpeakTutorial();

	//=================関数=======================//.
	void Update();		//更新処理関数.
	void Render();		//描画処理関数.

private:
	//==================関数=======================//.
	void Init();		//初期化処理関数.
	void Release();		//解放処理関数.


};

#endif	//#ifndef CSPEAK_TUTORIAL_H.