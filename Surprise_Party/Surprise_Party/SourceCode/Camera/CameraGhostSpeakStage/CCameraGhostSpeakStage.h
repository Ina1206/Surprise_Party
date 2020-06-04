#ifndef CCAMERA_GHOST_SPEAK_STAGE_H
#define CCAMERA_GHOST_SPEAK_STAGE_H

#include "..\CCameraBase.h"

/**********************************************
*		お化けが話すステージのカメラクラス.
**************/
class CCameraGhostSpeakStage
	: public CCameraBase
{
public:
	CCameraGhostSpeakStage();
	~CCameraGhostSpeakStage();

	//========================定数=============================//.
	const D3DXVECTOR3	INIT_CAMERA_POS				= D3DXVECTOR3(5.0f, 2.5f, -3.5f);		//カメラ初期位置.
	const D3DXVECTOR3	INIT_CAMERA_LOOK			= D3DXVECTOR3(5.0f, 2.5f, 5.0f);		//カメラ初期注視点.
	const D3DXVECTOR3	SPEAK_START_POS				= D3DXVECTOR3(6.0f, 2.7f, 1.3f);		//会話開始時のカメラ座標.
	const D3DXVECTOR3	SPEAK_START_LOOK			= D3DXVECTOR3(6.0f, 2.2f, 5.0f);		//会話開始時のカメラ注視点.
	const D3DXVECTOR3	CAMERA_POS_DISTANCE			= SPEAK_START_POS - INIT_CAMERA_POS;	//カメラの座標距離.
	const D3DXVECTOR3	CAMERA_LOOK_DISTANCE		= SPEAK_START_LOOK - INIT_CAMERA_LOOK;	//カメラの注視点距離.
	const float			CAMER_MOVE_SPEED			= 0.02f;								//カメラ移動速度.
	const int			GET_CLOSER_CAMERA_DIRECT	= 1;									//カメラが接近する方向.
	const int			FAR_AWAY_CAMERA_DIRECT		= -1;									//カメラが遠のく方向.

	//========================関数==========================//.
	void Update();				//更新処理関数.
private:
	//========================関数==========================//.
	void Init();				//初期化処理関数.
	void Release();				//解放処理関数.
	void Move();				//移動処理関数.
	void GetCloserUpperLimit();	//接近上限処理関数.
	void FarAwayUpperLimit();	//遠のく上限処理関数.

	//========================変数==========================//.
	int	m_MoveCameraDirection;	//カメラ移動方向.

};

#endif	//#ifndef CCAMERA_GHOST_SPEAK_STAGE_H.