#ifndef CTUTORIAL_BLACK_SCREEN_H
#define CTUTORIAL_BLACK_SCREEN_H

#include "..\CPlayUI.h"

/******************************************
*		�`���[�g���A�����̍����.
**************/
class CTutorialBlackScreen
	: public CPlayUI
{
public:
	CTutorialBlackScreen();
	~CTutorialBlackScreen();

	//====================�֐�======================//.
	void Update();		//�X�V�����֐�.

private:
	//====================�֐�======================//.
	void Init();		//�����������֐�.
	void Release();		//��������֐�.


};

#endif	//#ifndef CTUTORIAL_BLACK_SCREEN_H.