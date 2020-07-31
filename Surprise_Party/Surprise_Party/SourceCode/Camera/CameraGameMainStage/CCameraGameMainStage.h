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

	const float			SEE_PEOPLE_POS			= 11.0f;							//人を見るカメラ座標.
	const float			SEE_PEOPLE_MOVE_SPEED	= 0.6f;								//人を見る移動速度.

	const float			LOOK_UP_SPEED			= 0.2f;								//見上げる速度.

	//==========================関数=============================//.
	void Update();			//更新処理関数.

private:
	//==========================関数=============================//.
	void Init();			//初期化処理関数.
	void Release();			//解放処理関数.
	void LookAtPeople();	//人を見る処理関数.
	void LookAtGhost();		//お化けを見る処理関数.
	void MovePosLookUp();	//見上げるために座標移動.
	void MoveLookLookUp();	//見上げるために注視点移動.
};


#endif	//#ifndef CCAMERA_GAMEMAIN_STAGE_H.