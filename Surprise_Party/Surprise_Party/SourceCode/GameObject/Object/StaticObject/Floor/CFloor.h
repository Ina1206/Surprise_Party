#ifndef CFLOOR_H
#define CFLOOR_H

#include "..\CStaticObjectBase.h"

/**************************************
*	���N���X.
************/
class CFloor
	: public CStaticObjectBase
{
public:
	CFloor();
	~CFloor();

	//=================�֐�====================//.
	void Update();		//�X�V�����֐�.
private:
	//=================�֐�====================//.
	void Init();		//�����������֐�.
	void Release();		//��������֐�.


};

#endif	//#ifndef CFLOOR_H