#ifndef CPLAY_SOUND_SWITCH_H
#define CPLAY_SOUND_SWITCH_H

#include "..\CSwitchBase.h"
#include "..\..\SpriteEffect\MoveNoteEffect\CMoveNoteEffect.h"

/*********************************************
*		音再生スイッチクラス.
**************/
class CPlaySoundSwitch
	: public CSwitchBase
{
public:
	CPlaySoundSwitch();
	~CPlaySoundSwitch();

	//=================定数=================//.
	const float SCALE			= 0.2f;		//大きさ.
	const int	MOVE_NOTE_NUM	= 0;		//音符の番号.
	const int	SMOKE_NUM		= 1;		//煙の番号.
	const float	MOVE_NOTE_ANGLE = 225.0f;	//音符移動角度.

	//=================関数=================//.
	void Update();		//更新処理関数.

private:
	//=================関数=================//.
	void Init();		//初期化処理関数.
	void Release();		//解放処理関数.

};

#endif	//#ifndef CPLAY_SOUND_SWITCH_H.