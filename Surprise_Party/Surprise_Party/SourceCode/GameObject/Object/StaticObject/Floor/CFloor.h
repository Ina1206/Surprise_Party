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

	//=============定数================//.
	const float	SCALE = 0.1f;	//大きさ.

	//=================関数====================//.
	void Update();		//更新処理関数.

	//=============情報置換処理関数============//.
	void SetScale(const float& scale) { m_fScale = scale; }	//大きさ.

private:
	//=================関数====================//.
	void Init();		//初期化処理関数.
	void Release();		//解放処理関数.


};

#endif	//#ifndef CFLOOR_H