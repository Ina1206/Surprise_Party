#ifndef CTUTORIAL_H
#define CTUTORIAL_H

#include "..\SceneBase\CSceneBase.h"

/************************************
*	チュートリアルクラス.
*********/
class CTutorial
	: public CSceneBase
{
public:
	CTutorial();
	~CTutorial();

	//======================関数============================//.
	void UpDate();	//更新処理関数.
	void Render();	//描画処理関数.

private:
	//======================関数============================//.
	void Init();	//初期化処理関数.
	void Release();	//解放処理関数.

};

#endif	//#ifndef CTUTORIAL_H.