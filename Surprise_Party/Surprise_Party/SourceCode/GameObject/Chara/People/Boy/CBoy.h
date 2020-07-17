#ifndef CBOY_H
#define CBOY_H

#include "..\CPeopleBase.h"

/************************************
*	男の子クラス.
**********/
class CBoy
	: public CPeopleBase
{
public:
	CBoy();
	~CBoy();
	//================列挙体==================//.
	//アニメーション.
	enum class enBoyAnim {
		Walk,		//歩行.
		Stand,		//立つ.
		Surprise,	//驚く.
	};

	//=================定数===================//.
	const float	DEPTH_POS = -2.0f;	//奥行きの座標.

	//=================関数===================//.
	void Update();		//更新処理関数.
	
private:
	//=================関数===================//.
	void Init();		//初期化処理関数.
	void Release();		//解放処理関数.

};

#endif	//#ifndef CBOY_H.