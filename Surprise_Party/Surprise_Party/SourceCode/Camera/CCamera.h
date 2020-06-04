#ifndef CCAMERA_BASE_H
#define CCAMERA_BASE_H

#include "..\Drawing\Resource\CResourceManager.h"

/**************************************
*		カメラクラス.
**************/
class CCamera
{
public:
	CCamera();
	~CCamera();

	//=======================関数==========================//.
	void Update();		//更新処理関数.

private:
	//=======================関数==========================//.
	void Init();		//初期化処理関数.
	void Release();		//解放処理関数.

	//=======================変数==========================//.
	CAMERA	m_Camera;	//カメラ情報.

};

#endif	//#ifndef CCAMERA_BASE_H.