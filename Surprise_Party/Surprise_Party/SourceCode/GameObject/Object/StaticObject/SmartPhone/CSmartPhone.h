#ifndef CSMART_PHONE_H
#define CSMART_PHONE_H

#include "..\CStaticObjectBase.h"

/********************************************
*		�X�}�[�g�t�H���N���X
*************/
class CSmartPhone
	: public CStaticObjectBase
{
public:
	CSmartPhone();
	~CSmartPhone();

	//=========================�֐�==============================//.
	void Update();		//�X�V�����֐�.
	void Render();		//�`�揈���֐�.

private:
	//=========================�֐�==============================//.
	void Init();		//�����������֐�.
	void Release();		//��������֐�.


};

#endif	//#ifndef CSMART_PHONE_H.