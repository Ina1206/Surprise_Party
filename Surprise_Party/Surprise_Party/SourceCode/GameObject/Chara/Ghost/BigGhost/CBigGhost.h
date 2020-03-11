#ifndef CBIG_GHOST_H
#define CBIG_GHOST_H

#include "..\CGhostBase.h"

/******************************************
*		大きいお化けクラス.
**********/
class CBigGhost
	: public CGhostBase
{
public:
	CBigGhost();
	~CBigGhost();

	//=================関数====================//.
	void Update();		//更新処理関数.
	void Render();		//描画処理科数.

private:
	//=================関数====================//.
	void Init();		//初期化処理関数.
	void Release();		//初期化処理関数.


};


#endif	//#ifndef CBIG_GHOST_H.