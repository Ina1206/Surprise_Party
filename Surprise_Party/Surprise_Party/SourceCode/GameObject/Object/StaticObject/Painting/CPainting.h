#ifndef CPAINTING_H
#define CPAINTING_H

#include "..\CStaticObjectBase.h"

/************************************
*	�G��N���X.
****************/
class CPainting
	: public CStaticObjectBase
{
public:
	CPainting();
	~CPainting();

	//============�֐�==============//.
	void UpDate();		//�X�V�����֐�.
private:
	//============�֐�==============//.
	void Init();		//�����������֐�.
	void Release();		//��������֐�.

	
};

#endif //#ifndef CPAINTING_H.