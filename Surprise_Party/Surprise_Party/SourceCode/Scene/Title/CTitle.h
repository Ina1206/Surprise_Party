#ifndef CTITLE_H
#define CTITLE_H

#include "..\SceneBase\CSceneBase.h"


/**********************************
*		�^�C�g���N���X.
******/
class CTitle
	: public CSceneBase
{
public:
	CTitle();
	~CTitle();

	//====================�֐�========================//.
	void UpDate();		//�X�V�����֐�.
	void Render();		//�`�揈���֐�.
protected:
	//====================�֐�========================//.
	void Init();		//�����������֐�.
	void Release();		//��������֐�.

};


#endif	//#ifndef CTITLE_H.