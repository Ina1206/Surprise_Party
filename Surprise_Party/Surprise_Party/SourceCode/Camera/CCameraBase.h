#ifndef CCAMERA_BASE_H
#define CCAMERA_BASE_H

#include "..\Drawing\Resource\CResourceManager.h"

/**************************************
*		カメラ基底クラス.
**************/
class CCameraBase
{
public:
	CCameraBase();
	virtual ~CCameraBase();

	//=======================関数==========================//.
	virtual void Update() = 0;		//更新処理関数.

	//=================情報取得処理関数====================//.
	//カメラ座標.
	D3DXVECTOR3 GetCameraPos() const { return m_Camera.vPos; }

protected:
	//=======================関数==========================//.
	virtual void Init() = 0;		//初期化処理関数.
	virtual void Release() = 0;		//解放処理関数.

	//=======================変数==========================//.
	CAMERA	m_Camera;	//カメラ情報.

};

#endif	//#ifndef CCAMERA_BASE_H.