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
	const int PAUSE_TITLE_NUM	= 2;	//ポーズタイトル番号.


	//=======================関数============================//.
	void Update();		//更新処理関数.

private:
	//=======================関数============================//.
	void Init();		//初期化処理関数.

};

#endif	//#ifndef CPAUSE_UI_H.