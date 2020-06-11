#ifndef CENDIGN_SWITCH_GHOST_H
#define CENDIGN_SWITCH_GHOST_H

#include "..\CEndingWorkGhostBase.h"

/*******************************************
*		エンディングスイッチお化けクラス.
******************/
class CEndingSwitchGhost
	: public CEndingWorkGhostBase
{
public:
	CEndingSwitchGhost();
	~CEndingSwitchGhost();

	//====================定数======================//.
	const float	SCALE		= 0.05f;	//大きさ.
	const float	PRE_POS_Y	= -10.0f;	//初期角度ｙ調整数値.
	
	const float	ACC_MAX		= 0.5f;		//加速度最大値.
	const float	ACC_SPEED	= 0.01f;	//加速度加算速度.
	const float	GRAVITY		= 0.25f;	//重力.

	const float	MOVE_SPEED	= 0.02f;	//移動速度.

	//====================関数======================//.
	void Update();				//更新処理関数.
	void Render();				//描画処理関数.

private:
	//====================関数======================//.
	void Init();				//初期化処理関数.
	void Release();				//解放処理関数.
	void ActRejoiceEmotion();	//喜び感情行動処理関数.
	void SettingInitDirect();	//初期方向設定処理関数.

	//====================変数======================//.
	int		m_MoveDirect;		//移動方向.
	bool	m_bSetDirect;		//方向を設定したフラグ.


};

#endif	//#ifndef CENDIGN_SWITCH_GHOST_H.