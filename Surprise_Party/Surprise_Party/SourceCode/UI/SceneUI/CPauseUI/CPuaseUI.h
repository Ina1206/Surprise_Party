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


private:
	//=======================関数============================//.
	void Init();		//初期化処理関数.

};

#endif	//#ifndef CPAUSE_UI_H.