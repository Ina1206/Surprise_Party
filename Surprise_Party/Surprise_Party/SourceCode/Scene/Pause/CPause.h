#ifndef CPAUSE_H
#define CPAUSE_H

#include "..\SceneBase\CSceneBase.h"

/****************************************
*		�ꎞ��~�N���X.
************/
class CPause
	: public CSceneBase
{
public:
	CPause();
	~CPause();

	//=====================�֐�=====================//.
	void UpDate();		//�X�V�����֐�.
	void Render();		//�`�揈���֐�.

private:
	//=====================�֐�=====================//.
	void Init();		//�����������֐�.
	void Release();		//��������֐�.

};

#endif	//#ifndef CPAUSE_H.