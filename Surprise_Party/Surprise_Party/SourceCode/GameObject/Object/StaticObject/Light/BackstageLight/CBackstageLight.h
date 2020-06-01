#ifndef CBACKSTAGE_LIGHT_H
#define CBACKSTAGE_LIGHT_H

#include "..\CLightBase.h"

/*******************************************
*		舞台裏のライトクラス.
************/
class CBackstageLight
	: public CLightBase
{
public:
	CBackstageLight();
	~CBackstageLight();

	//=======================関数==========================//.
	void Update();		//更新処理関数.

private:
	//=======================関数==========================//.
	void Init();		//初期化処理関数.
	void Release();		//解放処理関数.


};

#endif	//#ifndef CBACKSTAGE_LIGHT_H.