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

	//=================関数=================//.
	void Update();		//更新処理関数.

private:
	//=================関数=================//.
	void Init();		//初期化処理関数.
	void Release();		//解放処理関数.

};

#endif	//#ifndef CPLAY_SOUND_SWITCH_H.