#ifndef CPAUSE_UI_H
#define CPAUSE_UI_H

#include "..\CSceneUIBase.h"

/**************************************
*		�|�[�YUI�̃N���X.
****************/
class CPauseUI
	: public CSceneUIBase
{
public:
	CPauseUI();
	~CPauseUI();

	//=======================�萔============================//.
	const int PAUSE_TITLE_NUM	= 2;	//�|�[�Y�^�C�g���ԍ�.


	//=======================�֐�============================//.
	void Update();		//�X�V�����֐�.

private:
	//=======================�֐�============================//.
	void Init();		//�����������֐�.

};

#endif	//#ifndef CPAUSE_UI_H.