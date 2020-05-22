#ifndef CPLAY_SOUND_SWITCH_H
#define CPLAY_SOUND_SWITCH_H

#include "..\CSwitchBase.h"
#include "..\..\SpriteEffect\MoveNoteEffect\CMoveNoteEffect.h"
#include "..\..\SpriteEffect\SmokeEffect\CSmokeEffect.h"

class CPlaySoundSwitch
	: public CSwitchBase
{
public:
	CPlaySoundSwitch();
	~CPlaySoundSwitch();

	//=================ŠÖ”=================//.
	void Update();		//XVˆ—ŠÖ”.

private:
	//=================ŠÖ”=================//.
	void Init();		//‰Šú‰»ˆ—ŠÖ”.
	void Release();		//‰ğ•úˆ—ŠÖ”.

};

#endif	//#ifndef CPLAY_SOUND_SWITCH_H.