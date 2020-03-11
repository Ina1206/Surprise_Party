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
	void Init();				//初期化処理関数.
	void Release();				//解放処理関数.
	void WakeUp();				//起床処理関数.
	void HaveTroubleEmotion();	//困る感情処理関数.
	void RejoiceEmotion();		//喜ぶ感情処理関数.
	void Sleep();				//寝る処理関数.

};


#endif	//#ifndef CBIG_GHOST_H.