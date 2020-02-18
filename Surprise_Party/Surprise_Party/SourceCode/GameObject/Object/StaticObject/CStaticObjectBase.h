#ifndef CSTATIC_OBJECT_BASE_H
#define CSTATIC_OBJECT_BASE_H

#include "..\CObjectBase.h"

/***********************************************
*		静的オブジェクトクラス.
***********/
class CStaticObjectBase
	: public CObjectBase
{
public:
	CStaticObjectBase();
	virtual ~CStaticObjectBase();

	//=================定数====================//.
	const float ALPHA_DISTANCE_MAX		= 3.0f;	//半透明にする距離最大数.
	const float STATIC_OBJ_ALPHA_MIN	= 0.6f;	//静的オブジェクト透過値最小.

	//=================関数====================//.
	void ObjectAlpha();		//オブジェクト透過値変更処理関数.
protected:


private:

};

#endif	//#ifndef CSTATIC_OBJECT_BASE_H.