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

	//=============�萔================//.
	const float	SCALE = 0.1f;	//�傫��.

	//=================�֐�====================//.
	void Update();		//�X�V�����֐�.

	//=============���u�������֐�============//.
	void SetScale(const float& scale) { m_fScale = scale; }	//�傫��.

private:
	//=================�֐�====================//.
	void Init();		//�����������֐�.
	void Release();		//��������֐�.


};

#endif	//#ifndef CFLOOR_H