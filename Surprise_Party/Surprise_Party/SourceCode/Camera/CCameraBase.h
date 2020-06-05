#ifndef CCAMERA_BASE_H
#define CCAMERA_BASE_H

#include"..\Global.h"

/**************************************
*		カメラ基底クラス.
**************/
class CCameraBase
{
public:
	CCameraBase();
	virtual ~CCameraBase();

	//=======================定数==========================//.
	const unsigned int MOVE_FLAG		= (1 << 0);		//移動フラグ.
	const unsigned int STOP_FLAG		= (1 << 1);		//停止フラグ.
	const unsigned int MOVE_FINISH_FLAG = (1 << 2);		//移動終了フラグ.
	const unsigned int PEOPLE_LOOK_FLAG = (1 << 3);		//人を見るフラグ.
	const unsigned int GHOST_LOOK_FLAG	= (1 << 4);		//お化けを見るフラグ.

	//=======================関数==========================//.
	virtual void Update() = 0;		//更新処理関数.
	void AcquisitionDifference();	//差分取得処理関数.

	//=================情報取得処理関数====================//.
	//カメラ座標.
	D3DXVECTOR3 GetPos() const { return m_Camera.vPos; }
	//カメラ注視点.
	D3DXVECTOR3 GetLook() const { return m_Camera.vLook; }
	//移動フラグ.
	unsigned int GetMoveFlag() const { return m_MoveFlag; }


	//=================情報置換処理関数====================//.
	//移動フラグ.
	void SetMoveFlag(const unsigned int& Flag) { m_MoveFlag = Flag; }
	//相手の座標.
	void SetTargetPos(const D3DXVECTOR3& vPos) { m_vTargetPos = vPos; }

protected:
	//=======================関数==========================//.
	virtual void Init() = 0;		//初期化処理関数.
	virtual void Release() = 0;		//解放処理関数.

	//======================構造体=========================//.
	struct CAMERA
	{
		D3DXVECTOR3	vPos;	//位置.
		D3DXVECTOR3 vLook;	//注視位置.
		float		fYaw;	//Y軸回転.
		D3DXMATRIX	mRot;	//回転行列.
		
		CAMERA()
			: vPos	(0.0f, 0.0f, 0.0f)
			, vLook	(0.0f, 0.0f, 0.0f)
			, fYaw	(0.0f)
			, mRot	()
		{}
	};

	//=======================変数==========================//.
	CAMERA			m_Camera;		//カメラ情報.
	unsigned int	m_MoveFlag;		//移動フラグ.
	D3DXVECTOR3		m_vTargetPos;	//相手の座標.
	CAMERA			m_OldCamera;	//差分用変数.
};

#endif	//#ifndef CCAMERA_BASE_H.