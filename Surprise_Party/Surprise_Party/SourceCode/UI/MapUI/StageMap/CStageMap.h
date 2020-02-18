#ifndef CSTAGE_MAP_H
#define CSTAGE_MAP_H

#include "..\CMapUI.h"

/**************************************
*		ステージマップクラス.
********/
class CStageMap
	: public CMapUI
{
public:
	CStageMap();
	~CStageMap();

	
private:
	//=================関数=====================//.
	void Init();		//初期化処理関数.
	void Release();		//解放処理関数.


};

#endif	//#ifndef CSTAGE_MAP_H.