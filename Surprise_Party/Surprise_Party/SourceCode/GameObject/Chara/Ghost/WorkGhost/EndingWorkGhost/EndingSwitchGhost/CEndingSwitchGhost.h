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

	//====================�萔======================//.
	const float	SCALE		= 0.05f;	//�傫��.
	const float	PRE_POS_Y	= -10.0f;	//�����p�x���������l.

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