#ifndef CPLAY_SOUND_SWITCH_H
#define CPLAY_SOUND_SWITCH_H

#include "..\CSwitchBase.h"
#include "..\..\SpriteEffect\MoveNoteEffect\CMoveNoteEffect.h"

/*********************************************
*		���Đ��X�C�b�`�N���X.
**************/
class CPlaySoundSwitch
	: public CSwitchBase
{
public:
	CPlaySoundSwitch();
	~CPlaySoundSwitch();

	//=================�֐�=================//.
	void Update();		//�X�V�����֐�.

private:
	//=================�֐�=================//.
	void Init();		//�����������֐�.
	void Release();		//��������֐�.

};

#endif	//#ifndef CPLAY_SOUND_SWITCH_H.