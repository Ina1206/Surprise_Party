#ifndef CSPEAK_TUTORIAL_H
#define CSPEAK_TUTORIAL_H

#include "..\CSpeakUI.h"

/******************************************
*		�`���[�g���A����b.
***************/
class CSpeakTutorial
	: public CSpeakUI
{
public:
	CSpeakTutorial();
	~CSpeakTutorial();

	//=================�֐�=======================//.
	void Update();		//�X�V�����֐�.
	void Render();		//�`�揈���֐�.

private:
	//==================�֐�=======================//.
	void Init();		//�����������֐�.
	void Release();		//��������֐�.


};

#endif	//#ifndef CSPEAK_TUTORIAL_H.