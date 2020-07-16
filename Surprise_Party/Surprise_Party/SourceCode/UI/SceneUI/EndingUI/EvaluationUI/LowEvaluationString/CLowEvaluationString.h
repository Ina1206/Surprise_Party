#ifndef CLOW_EVALUATION_STRING_H
#define CLOW_EVALUATION_STRING_H

#include "..\EvaluationUIBase\CEvaluationUIBase.h"

/********************************************
*		低評価時のUI文字クラス.
*****************/
class CLowEvaluationString
	: public CEvaluationUIBase
{
public:
	CLowEvaluationString();
	~CLowEvaluationString();

	//=========================定数===============================//.
	const unsigned int	DISP_FLAG				= (1 << 0);							//表示フラグ.
	const unsigned int	MOVE_FLAG				= (1 << 1);							//移動フラグ.
	const unsigned int	TRANSPARENT_FLAG		= (1 << 2);							//透過フラグ.

	const float			VERTICAL_MOVE_SPEED		= 0.5f;								//縦移動速度.
	const float			ANGLE_SPEED				= 5.0f;								//角度の速度.
	const float			MOVE_HORIZON_WIDTH		= 3.0f;								//移動横幅.
	const float			ANGLE_MAX				= 360.0f;							//角度最大値.

	const float			PLAY_SOUND_RANGE_MIN	= 90.0f;							//音が流れる範囲の最小値.
	const float			PLAY_SOUND_RANGE_IN		= 180.0f;							//音が流れる範囲の中間地点.
	const float			PLAY_SOUND_RANGE_MAX	= 270.0f;							//音が流れる範囲の最大値.
	const D3DXVECTOR3	FINSH_BASE_POS			= D3DXVECTOR3(50.0f, 27.5f, 0.0f);	//最終基準座標.
	const int			FLOAT_SOUND_VOLUME_MAX	= 500;								//浮遊音の音量最大値.

	//=========================関数===============================//.
	void Update();		//更新処理.

private:
	//=========================関数===============================//.
	void Init();							//初期化処理関数.
	void Release();							//解放処理関数.
	void MoveBeforePos();					//移動前の座標設定処理関数.
	void Transparent();						//透過処理関数.
	void Move();							//移動処理関数.
	void DisplayAllAtOnce();				//一気に表示する処理関数.

	//=========================変数===============================//.
	unsigned int	m_ActFlag;				//行動フラグ.
	float			m_fAngle;				//角度.
	bool			m_bPlayFloatingSound;	//浮遊音再生フラグ.
};

#endif	//#ifndef CLOW_EVALUATION_STRING_H.