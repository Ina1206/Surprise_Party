#ifndef CREJICE_EFFECT_H
#define CREJICE_EFFECT_H

#include "..\CSpriteEffectBase.h"

/*********************************************
*		喜びエフェクト.
*********/
class CRejoiceEffect
	: public CSpriteEffectBase
{
public:
	CRejoiceEffect();
	~CRejoiceEffect();

	//===================列挙体=======================//.
	//スプライトの種類.
	enum class enRejoiceSpriteType {
		EightPartNote	= 0,	//8部音符.
		Flower,					//花.

		Max,					//最大数.
		Start = EightPartNote,	//開始.
	};

	//====================定数========================//.
	const int	SPRITE_MAX		= 10;											//スプライト最大数.
	const int	SPRITE_TYPE_MAX = static_cast<int>(enRejoiceSpriteType::Max);	//スプライトの種類最大数.


	//====================関数========================//.
	void Update();							//更新処理関数.

private:
	//====================関数========================//.
	void Init();							//初期化処理関数.
	void Release();							//解放処理関数.
	void AppeartJudgement(const int& num);	//表示判定処理関数.
	void Move(const int& num);				//移動処理関数.
	void LinkSprite(const int& num);		//スプライト紐づけ処理関数.


};

#endif	//#ifndef CREJICE_EFFECT_H.