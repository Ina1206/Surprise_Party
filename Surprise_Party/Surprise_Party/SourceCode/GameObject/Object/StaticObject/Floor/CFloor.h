#ifndef CFLOOR_H
#define CFLOOR_H

#include "..\CStaticObjectBase.h"

/**************************************
*	床クラス.
************/
class CFloor
	: public CStaticObjectBase
{
public:
	CFloor();
	~CFloor();

	//=================関数====================//.
	void Update();		//更新処理関数.
private:
	//=================関数====================//.
	void Init();		//初期化処理関数.
	void Release();		//解放処理関数.


};

#endif	//#ifndef CFLOOR_H