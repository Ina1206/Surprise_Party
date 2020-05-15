#ifndef CPLAY_SOUND_SWITCH_H
#define CPLAY_SOUND_SWITCH_H

#include "..\CSwitchBase.h"
#include "..\..\SpriteEffect\MoveNoteEffect\CMoveNoteEffect.h"

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

	//=================�ϐ�=================//.
	std::unique_ptr<CMoveNoteEffect>	m_pCMoveNoteEffect;	//�����ړ��G�t�F�N�g�N���X.

};

#endif	//#ifndef CPLAY_SOUND_SWITCH_H.