#include "CCameraBase.h"

/**************************************
*		�J�������N���X.
**************/
CCameraBase::CCameraBase()
	: m_Camera		()
	, m_MoveFlag	(0)
	, m_vTargetPos	(0.0f, 0.0f, 0.0f)
	, m_OldCamera	()
	, m_bCanSkip	(true)
{

}

CCameraBase::~CCameraBase()
{

}

//===============================================.
//		�����擾�����֐�.
//===============================================.
void CCameraBase::AcquisitionDifference()
{
	m_OldCamera = m_Camera;
}
