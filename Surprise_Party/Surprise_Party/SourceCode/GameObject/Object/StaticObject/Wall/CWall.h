#ifndef CWALL_H
#define CWALL_H

#include "..\CStaticObjectBase.h"

/*****************************************
*		壁オブジェクトクラス.
*******/
class CWall
	: public CStaticObjectBase
{
public:
	CWall();
	~CWall();

	//=====================定数====================//.
	const float		ALPHA_DIVISOR	= 80.0f;	//透過値割る値.
	const float		WALL_ALPHA_MIN	= 0.8f;		//

	//=====================関数====================//.
	void UpDate();		//更新処理関数.

private:
	//=====================関数======================//.
	void Init();		//初期化処理関数.
	void Release();		//解放処理関数.

};

#endif	//#ifndef CWALL_H.