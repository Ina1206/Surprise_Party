#ifndef CTUTORIAL_H
#define CTUTORIAL_H

#include "..\SceneBase\CSceneBase.h"
#include "..\GameMain\StageBase\CStageBase.h"

/************************************
*	チュートリアルクラス.
*********/
class CTutorial
	: public CStageBase
{
public:
	CTutorial();
	~CTutorial();

	//======================関数============================//.
	void UpDate(const bool& ControlFlag);	//更新処理関数.
	void Render();							//描画処理関数.

private:
	//======================関数============================//.
	void Init();	//初期化処理関数.
	void Release();	//解放処理関数.
	void Control();	//操作処理関数.

};

#endif	//#ifndef CTUTORIAL_H.