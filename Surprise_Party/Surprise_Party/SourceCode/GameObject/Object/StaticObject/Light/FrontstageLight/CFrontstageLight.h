#ifndef CFRONTSTAGE_LIGHT_H
#define CFRONTSTAGE_LIGHT_H

#include "..\CLightBase.h"

/*********************************
*		表舞台のライトクラス.
*************/
class CFrontstageLight
	: public CLightBase
{
public:
	CFrontstageLight();
	~CFrontstageLight();

	//======================関数========================//.
	void Update();		//更新処理関数.

private:
	//======================関数========================//.
	void Init();		//初期化処理関数.
	void Release();		//解放処理関数.

};

#endif	//#ifndef CFRONTSTAGE_LIGHT_H.