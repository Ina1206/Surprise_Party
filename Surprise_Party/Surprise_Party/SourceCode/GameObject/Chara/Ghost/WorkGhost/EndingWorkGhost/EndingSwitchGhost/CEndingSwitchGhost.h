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

	//====================関数======================//.
	void Update();				//更新処理関数.
	void Render();				//描画処理関数.

private:
	//====================関数======================//.
	void Init();				//初期化処理関数.
	void Release();				//解放処理関数.
	void ActRejoiceEmotion();	//喜び感情行動処理関数.


};

#endif	//#ifndef CENDIGN_SWITCH_GHOST_H.