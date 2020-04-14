#ifndef CARROW_H
#define CARROW_H

#include "..\CPlayUI.h"

/**********************************************
*			矢印クラス.
*****************/
class CArrow
	: public CPlayUI
{
public:
	CArrow();
	~CArrow();

	//===================定数====================//.
	const D3DXVECTOR3	BASE_POS		= D3DXVECTOR3(100.0f, 400.0f, 0.0f);	//基本位置.
	const int			LEFT_ARROW_NUM	= 0;									//左矢印番号.

	//===================関数====================//.
	void Update();		//更新処理関数.

private:
	//===================関数====================//.
	void Init();		//初期化処理関数.
	void Release();		//解放処理関数.


};

#endif	//#ifndef CARROW_H.