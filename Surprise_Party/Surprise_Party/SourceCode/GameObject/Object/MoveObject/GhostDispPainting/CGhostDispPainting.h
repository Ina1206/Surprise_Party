#ifndef CGHOST_DISP_PAINTING_H
#define CGHOST_DISP_PAINTING_H

#include "..\CMoveObjectBase.h"

/***********************************************
*		お化けが現れる絵画クラス.
***************/
class CGhostDispPainting
	: public CMoveObjectBase
{
public:
	CGhostDispPainting();
	~CGhostDispPainting();

	//================定数===================//.
	const float PAINTING_ALPHA_MIN	= 0.8f;		//絵画の透過値最小値.
	const float ALPHA_DISTANCE		= 3.0f;		//半透明になる距離.
	const float	PAINTING_UP_MAX		= 5.0f;		//絵画上がる上限.
	const float	SCALE				= 0.4f;		//大きさ.
	
	//================関数===================//.
	void Update();								//更新処理関数.

private:
	//================関数===================//.
	void Init();								//初期化処理関数.
	void Release();								//解放処理関数.
	void ObjAlpha();							//オブジェクト透過処理関数.


};

#endif	//#ifndef CGHOST_DISP_PAINTING_H.