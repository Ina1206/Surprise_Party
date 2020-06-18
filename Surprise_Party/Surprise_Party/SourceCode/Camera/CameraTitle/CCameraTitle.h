#ifndef CCAMERA_TITLE_H
#define CCAMERA_TITLE_H

#include "..\CCameraBase.h"

/*******************************************
*		タイトルカメラクラス.
*************/
class CCameraTitle
	: public CCameraBase
{
public:
	CCameraTitle();
	~CCameraTitle();

	//=======================定数==========================//.
	const unsigned int	MOVE_FROM_FRONT_FLAG	= (1 << 0);							//正面移動フラグ.
	const unsigned int	MOVE_FROM_OBLIQUE_FLAG	= (1 << 1);							//斜めカメラ移動フラグ.
	
	const D3DXVECTOR3	POS_FROM_FRONT			= D3DXVECTOR3(11.9f, 3.3f, -14.3f);	//正面から見るカメラ座標.
	const D3DXVECTOR3	LOOK_FROM_FRONT			= D3DXVECTOR3(11.9f, 3.3f, 4.0f);	//正面から見るカメラの注視点座標.
	
	const D3DXVECTOR3	POS_FROM_OBLIQUE		= D3DXVECTOR3(1.3f, 5.4f, -5.5f);	//斜めから見るカメラ座標.
	const D3DXVECTOR3	LOOK_FROM_OBLIQUE		= D3DXVECTOR3(6.4f, 4.6f, 4.0f);	//斜めから見るカメラの注視点.

	const float			MOVE_SPEED_FROM_FRONT	= 0.05f;							//正面から見るカメラ移動速度.
	const float			MOVE_SPEED_FROM_OBLIQUE = 0.02f;							//斜めから見るカメラ移動速度.

	const float			MOVE_DISTANCE_MAX		= 70.0f;							//移動距離最大値.

	const int			MOVE_TYPE_MAX			= 2;								//移動タイプ最大値.

	//=======================関数==========================//.
	void Update();		//更新処理関数.
	
private:
	//=======================関数==========================//.
	void Init();		//初期化処理関数.
	void Release();		//解放処理関数.

	//=======================変数==========================//.
	unsigned int	m_MoveTypeFlag;		//移動種類フラグ.
	float			m_fMoveDistance;	//移動距離.
	float			m_fMoveSpeed;		//移動速度.
};

#endif	//#ifndef CCAMERA_TITLE_H.