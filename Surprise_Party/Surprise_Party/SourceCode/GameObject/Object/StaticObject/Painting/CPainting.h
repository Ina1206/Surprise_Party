#ifndef CPAINTING_H
#define CPAINTING_H

#include "..\CStaticObjectBase.h"

/************************************
*	絵画クラス.
****************/
class CPainting
	: public CStaticObjectBase
{
public:
	CPainting();
	~CPainting();

	//============定数==============//.
	const float	SCALE = 0.3f;	//大きさ.

	//============関数==============//.
	void Update();		//更新処理関数.
private:
	//============関数==============//.
	void Init();		//初期化処理関数.
	void Release();		//解放処理関数.

	
};

#endif //#ifndef CPAINTING_H.