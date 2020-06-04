#ifndef CCAMERA_GAMEMAIN_STAGE_H
#define CCAMERA_GAMEMAIN_STAGE_H

#include "..\CCameraBase.h"

/**********************************************
*		ゲームメインステージのカメラクラス.
**********************/
class CCameraGameMainStage
	: public CCameraBase
{
public:
	CCameraGameMainStage();
	~CCameraGameMainStage();

	//==========================定数=============================//.
	const D3DXVECTOR3	CAMERA_START_POS		= D3DXVECTOR3(11.9f, 7.5f, -19.9f);	//開始時の座標.
	const D3DXVECTOR3	CAMERA_START_LOOK		= D3DXVECTOR3(11.9f, 5.3f, 4.0f);	//開始時の注視点座標.
	const D3DXVECTOR3	CAMERA_PEOPLE_SEE_POS	= D3DXVECTOR3(8.8f, 2.0f, -7.0f);	//カメラが人を見る座標.
	const D3DXVECTOR3	CAMERA_PEOPLE_SEE_LOOK	= D3DXVECTOR3(-4.3f, 4.3f, 0.0f);	//カメラが人を見る注視点.

	//==========================関数=============================//.
	void Update();		//更新処理関数.

private:
	//==========================関数=============================//.
	void Init();		//初期化処理関数.
	void Release();		//解放処理関数.


};


#endif	//#ifndef CCAMERA_GAMEMAIN_STAGE_H.