#ifndef CENDING_DISP_GHOST_H
#define CENDING_DISP_GHOST_H

#include "..\CEndingWorkGhostBase.h"

/******************************************
*		エンディングの現れるお化けクラス.
**************/
class CEndingDispGhost
	: public CEndingWorkGhostBase
{
public:
	CEndingDispGhost();
	~CEndingDispGhost();

	//======================定数=======================//.
	const float	SCALE			= 0.07f;	//大きさ.
	const float PRE_POS_Y		= -20.0f;	//最初の調整ｙ座標.

	const float	ACC_MAX			= 0.25f;	//加速最大値.
	const float	ACC_SPEED		= 0.005f;	//加速度加算速度.
	const float GRAVITY			= 0.1f;		//重力.
	const float	ROTATION_SPEED	= 0.02f;	//回転速度.

	//======================関数=======================//.
	void Update();				//更新処理関数.
	void Render();				//描画処理関数.

private:
	//======================関数=======================//.
	void Init();				//初期化処理関数.
	void Release();				//解放処理関数.
	void ActRejoiceEmotion();	//喜び感情行動処理関数.
	void Rotation();			//回転処理関数.
	void ActHaveTrouble();		//困った感情行動処理関数.

	//======================変数=======================//.
	int			m_RotationDirect;		//回転方向.
	bool		m_bChangeRotationDirect;//回転方向変更フラグ.
	bool		m_bStartHaveTrouble;	//困るの開始フラグ.
};

#endif	//#ifndef CENDING_DISP_GHOST_H.