#ifndef CBOY_H
#define CBOY_H

#include "..\CPeopleBase.h"

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

	//=================関数===================//.
	void UpDate();		//更新処理関数.
	
private:
	//=================関数===================//.
	void Init();		//初期化処理関数.
	void Release();		//解放処理関数.

};

#endif	//#ifndef CBOY_H.