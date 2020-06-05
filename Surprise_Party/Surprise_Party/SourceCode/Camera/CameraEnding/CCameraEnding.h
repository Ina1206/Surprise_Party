#ifndef CCAMERA_ENDING_H
#define CCAMERA_ENDING_H

#include "..\CCameraBase.h"

/******************************************
*		エンディングカメラクラス.
***************/
class CCameraEnding
	: public CCameraBase
{
public:
	CCameraEnding();
	~CCameraEnding();

	//===========================定数===============================//.
	const unsigned int	APPROCH_GHOST_HEAD_FLAG	= (1 << 0);							//お化けの頭に接近フラグ.
	const unsigned int	APPROCH_SMARTPHONE_FLAG = (1 << 1);							//スマートフォンの接近フラグ.
	
	const D3DXVECTOR3	INIT_CAMERA_POS			= D3DXVECTOR3(23.9f, 5.0f, -3.5f);	//カメラ初期座標.
	const D3DXVECTOR3	INIT_CAMERA_LOOK		= D3DXVECTOR3(5.0f, 2.5f, 5.0f);	//カメラ初期注視点.
	const D3DXVECTOR3	INTERMEDIATE_POINT_POS	= D3DXVECTOR3(5.1f, 21.8f, 3.9f);	//中間地点座標.
	const D3DXVECTOR3	INTERMEDIATE_POINT_LOOK	= D3DXVECTOR3(5.7f, -5.0, 5.0f);	//中間地点注視点.

	const float			MOVE_SPEED				= 0.15f;								//移動速度.
	const float			ANGLE_MIN				= -123.0f;							//角度最小値.
	const float			ANGLE_MAX				= -18.0f;							//角度最大値.
	//===========================関数===============================//.
	void Update();	//更新処理関数.

private:
	//===========================関数===============================//.
	void Init();											//初期化処理関数.
	void Release();											//解放処理関数.
	void MoveToIntermediatePoint();							//中間地点まで移動処理関数.
	void MoveUp();											//上昇移動処理関数.
	void MoveApproching();									//接近移動処理関数.
	void RotateSurrunding(	const float& fCriteriaRange,
							const float& fCenterRange);		//周辺を回る処理関数.
	void MoveLook();										//注視点移動処理関数.
	void MoveDown();										//下降移動処理関数.

	//===========================変数===============================//.
	float			m_fAngle;				//角度.
	float			m_fApprochDistance;		//近づく距離.
	unsigned int	m_ApprochFlag;			//接近フラグ.

};

#endif	//#ifndef CCAMERA_ENDING_H.