#ifndef CTITLE_UI_H
#define CTITLE_UI_H

#include "..\CSceneUIBase.h"

/*************************************
*		タイトルUIクラス.
****************/
class CTitleUI
	: public CSceneUIBase
{
public:
	CTitleUI();
	~CTitleUI();

	
private:
	//======================関数=======================//.
	void Init();	//初期化処理関数.

};

#endif	//#ifndef CTITLE_UI_H.