#ifndef CENDIGN_SWITCH_GHOST_H
#define CENDIGN_SWITCH_GHOST_H

#include "..\CEndingWorkGhostBase.h"

/*******************************************
*		�G���f�B���O�X�C�b�`�������N���X.
******************/
class CEndingSwitchGhost
	: public CEndingWorkGhostBase
{
public:
	CEndingSwitchGhost();
	~CEndingSwitchGhost();

	//====================�֐�======================//.
	void Update();				//�X�V�����֐�.
	void Render();				//�`�揈���֐�.

private:
	//====================�֐�======================//.
	void Init();				//�����������֐�.
	void Release();				//��������֐�.
	void ActRejoiceEmotion();	//��ъ���s�������֐�.


};

#endif	//#ifndef CENDIGN_SWITCH_GHOST_H.