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
	const D3DXVECTOR3 PAUSE_POS	= D3DXVECTOR3(100.0f, 50.0f, 0.0f);	//�|�[�Y�^�C�g�����W.

	//=======================�֐�============================//.
	void Update();						//�X�V�����֐�.

private:
	//=======================�֐�============================//.
	void Init();						//�����������֐�.
	void RenderSceneTitle();			//�V�[���^�C�g���`�揈���֐�.

};

#endif	//#ifndef CPAUSE_UI_H.