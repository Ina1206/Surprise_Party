#ifndef CENDING_H
#define CENDING_H

#include "..\SceneBase\CSceneBase.h"

/************************************************
*		�G���f�B���O�N���X.
***********/
class CEnding
	: public CSceneBase
{
public:
	CEnding();
	~CEnding();

	//========================�֐�===========================//.
	void UpDate();		//�X�V�����֐�.
	void Render();		//�`�揈���֐�.
private:
	//========================�֐�===========================//.
	void Init();		//�����������֐�.
	void Release();		//��������֐�.



};

#endif	//#ifndef CENDING_H.