#ifndef CTUTORIAL_H
#define CTUTORIAL_H

#include "..\SceneBase\CSceneBase.h"

/************************************
*	�`���[�g���A���N���X.
*********/
class CTutorial
	: public CSceneBase
{
public:
	CTutorial();
	~CTutorial();

	//======================�֐�============================//.
	void UpDate();	//�X�V�����֐�.
	void Render();	//�`�揈���֐�.

private:
	//======================�֐�============================//.
	void Init();	//�����������֐�.
	void Release();	//��������֐�.

};

#endif	//#ifndef CTUTORIAL_H.