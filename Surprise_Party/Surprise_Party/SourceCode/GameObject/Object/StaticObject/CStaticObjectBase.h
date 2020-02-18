#ifndef CSTATIC_OBJECT_BASE_H
#define CSTATIC_OBJECT_BASE_H

#include "..\CObjectBase.h"

/***********************************************
*		�ÓI�I�u�W�F�N�g�N���X.
***********/
class CStaticObjectBase
	: public CObjectBase
{
public:
	CStaticObjectBase();
	virtual ~CStaticObjectBase();

	//=================�萔====================//.
	const float ALPHA_DISTANCE_MAX		= 3.0f;	//�������ɂ��鋗���ő吔.
	const float STATIC_OBJ_ALPHA_MIN	= 0.6f;	//�ÓI�I�u�W�F�N�g���ߒl�ŏ�.

	//=================�֐�====================//.
	void ObjectAlpha();		//�I�u�W�F�N�g���ߒl�ύX�����֐�.
protected:


private:

};

#endif	//#ifndef CSTATIC_OBJECT_BASE_H.