#include "CStaticObjectBase.h"

/***********************************************
*		�ÓI�I�u�W�F�N�g�N���X.
***********/
CStaticObjectBase::CStaticObjectBase()
{

}

CStaticObjectBase::~CStaticObjectBase()
{

}

//==============================================.
//		�I�u�W�F�N�g���ߒl�ύX�����֐�.
//==============================================.
void CStaticObjectBase::ObjectAlpha()
{
	if (fabsf(m_vCameraPos.x - m_vPos.x) <= ALPHA_DISTANCE_MAX) {
 		m_fAlpha = STATIC_OBJ_ALPHA_MIN;
		return;
	}
	m_fAlpha = ALPHA_MAX;
	
}