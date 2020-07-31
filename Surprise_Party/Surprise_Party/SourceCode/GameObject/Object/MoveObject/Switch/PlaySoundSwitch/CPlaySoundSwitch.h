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

	//=================�萔=================//.
	const float SCALE			= 0.2f;		//�傫��.
	const int	MOVE_NOTE_NUM	= 0;		//�����̔ԍ�.
	const int	SMOKE_NUM		= 1;		//���̔ԍ�.
	const float	MOVE_NOTE_ANGLE = 225.0f;	//�����ړ��p�x.

	//=================�֐�=================//.
	void Update();		//�X�V�����֐�.

private:
	//=================�֐�=================//.
	void Init();		//�����������֐�.
	void Release();		//��������֐�.

};

#endif	//#ifndef CPLAY_SOUND_SWITCH_H.