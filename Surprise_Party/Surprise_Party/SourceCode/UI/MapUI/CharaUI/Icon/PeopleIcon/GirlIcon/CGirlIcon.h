#ifndef CGIRL_ICON_H
#define CGIRL_ICON_H

#include "..\CPeopleIcon.h"

/***************************************
*	女の子のアイコンクラス.
*******/
class CGirlIcon
	: public CPeopleIcon
{
public:
	CGirlIcon();
	~CGirlIcon();

private:
	//===================関数=====================//.
	void Init();		//初期化処理関数.
	void Release();		//解放処理関数.
};

#endif //#ifndef CGIRL_ICON_H.