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
		YellowEightPartNote = 0,	//黄色8部音符.
		BlueEightPartNote,			//青8部音符.
		PinkFlower,					//ピンクの花.
		RedFlower,					//青の花.

		Max,						//最大数.
		Start = YellowEightPartNote,//開始.
	};

	//====================定数========================//.
	const int	SPRITE_MAX			= 8;											//スプライト最大数.
	const int	SPRITE_TYPE_MAX		= static_cast<int>(enRejoiceSpriteType::Max);	//スプライトの種類最大数.
	const int	POP_MAX				= SPRITE_MAX / 2;								//出現最大数.

	const int	DISP_TIME_DELIMITER	= 30;											//表示区切り時間.
	const int	DISP_DELIMITER_MAX	= 2;											//表示区切り最大数.
	
	const float	MOVE_SPEED			= 0.04f;										//移動速度.
	const float	START_ANGLE			= 30.0f;										//開始角度.
	const float	ANGLE_WIDTH			= 250.0f;										//角度幅.

	const float	ALPHA_SPEED			= 0.02f;										//透過速度.
	const float	SCALING_SPEED		= 0.02f;										//拡縮速度.

	const D3DXVECTOR2	YELLOW_NOTE = D3DXVECTOR2(0.0f, 2.0f);						//黄色の音符位置.
	const D3DXVECTOR2	BLUE_NOTE	= D3DXVECTOR2(2.0f, 0.0f);						//青色の音符位置.
	const D3DXVECTOR2	PINK_FLOWER = D3DXVECTOR2(0.0f, 0.0f);						//ピンク色の花位置.
	const D3DXVECTOR2	RED_FLOWER	= D3DXVECTOR2(1.0f, 1.0f);						//赤色の花位置.

	//====================関数========================//.
	void Update();							//更新処理関数.

private:
	//====================関数========================//.
	void Init();							//初期化処理関数.
	void Release();							//解放処理関数.
	void AppeartJudgement(const int& num);	//表示判定処理関数.
	void Move(const int& num);				//移動処理関数.
	void LinkSprite(const int& num);		//スプライト紐づけ処理関数.

	//====================変数=========================//.
	int					m_DispCnt;			//表示カウント.
	int					m_PopCnt;			//出現カウント.
	std::vector<float>	m_fDistance;		//距離.
};

#endif	//#ifndef CREJICE_EFFECT_H.