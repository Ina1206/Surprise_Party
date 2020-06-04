#ifndef CSMART_PHONE_H
#define CSMART_PHONE_H

#include "..\CStaticObjectBase.h"

/********************************************
*		スマートフォンクラス
*************/
class CSmartPhone
	: public CStaticObjectBase
{
public:
	CSmartPhone();
	~CSmartPhone();

	//=========================関数==============================//.
	void Update();		//更新処理関数.
	void Render();		//描画処理関数.

private:
	//=========================関数==============================//.
	void Init();		//初期化処理関数.
	void Release();		//解放処理関数.


};

#endif	//#ifndef CSMART_PHONE_H.