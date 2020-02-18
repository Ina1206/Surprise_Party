#include "CStaticObjectBase.h"

CStaticObjectBase::CStaticObjectBase()
{

}

CStaticObjectBase::~CStaticObjectBase()
{

}

//==============================================.
//		オブジェクト透過値変更処理関数.
//==============================================.
void CStaticObjectBase::ObjectAlpha()
{
	if (fabsf(m_vCameraPos.x - m_vPos.x) <= ALPHA_DISTANCE_MAX) {
		m_fAlpha = STATIC_OBJ_ALPHA_MIN;
	}
	else {
		m_fAlpha = ALPHA_MAX;
	}
}