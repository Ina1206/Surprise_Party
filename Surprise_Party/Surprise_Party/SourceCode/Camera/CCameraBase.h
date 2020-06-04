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
	void Update();				//更新処理関数.
	void InitGameMainStage();	//ゲームメインステージの初期化処理関数.
	void InitGhostSpeakStage();	//お化けが話すステージの初期化処理関数.
	void InitEnding();			//エンディングの初期化処理関数.
	void MoveGameMainStage();
	void MoveGhostSpeakStage();
	void MoveEnding();

	//=================情報取得処理関数====================//.
	//カメラ座標.
	D3DXVECTOR3 GetCameraPos() const { return m_Camera.vPos; }

private:
	//=======================関数==========================//.
	void Init();		//初期化処理関数.
	void Release();		//解放処理関数.

	//=======================変数==========================//.
	CAMERA	m_Camera;	//カメラ情報.

};

#endif	//#ifndef CCAMERA_BASE_H.