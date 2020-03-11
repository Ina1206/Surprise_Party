#ifndef CBOOK_SHELF_H
#define CBOOK_SHELF_H

#include "..\CStaticObjectBase.h"

/************************************
*		本棚クラス.
*****************/
class CBookShelf
	: public CStaticObjectBase
{
public:
	CBookShelf();
	~CBookShelf();

	//=============関数===============//.
	void Update();	//更新処理関数.
private:
	//=============関数===============//.
	void Init();	//初期化処理関数.
	void Release();	//解放処理関数.


};

#endif	//#ifndef CBOOK_SHELF_H.