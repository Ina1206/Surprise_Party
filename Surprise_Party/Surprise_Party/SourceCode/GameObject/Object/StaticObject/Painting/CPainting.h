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

	//============�萔==============//.
	const float	SCALE = 0.3f;	//�傫��.

	//============�֐�==============//.
	void Update();		//�X�V�����֐�.
private:
	//============�֐�==============//.
	void Init();		//�����������֐�.
	void Release();		//��������֐�.

	
};

#endif //#ifndef CPAINTING_H.