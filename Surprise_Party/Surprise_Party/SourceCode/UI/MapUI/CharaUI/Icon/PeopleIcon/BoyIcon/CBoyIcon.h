#ifndef CBOY_ICON_H
#define CBOY_ICON_H

#include "..\CPeopleIcon.h"

/*************************************
*		男の子アイコンクラス.
******/
class CBoyIcon
	: public CPeopleIcon
{
public:
	CBoyIcon();
	~CBoyIcon();
	
private:
	//======================関数==========================//.
	void Init();		//初期化処理関数.
	void Release();		//解放処理関数.

};

#endif	//#ifndef CBOY_ICON_H.