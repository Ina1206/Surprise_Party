#include "CCameraBase.h"

/**************************************
*		ƒJƒƒ‰Šî’êƒNƒ‰ƒX.
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
//		·•ªæ“¾ˆ—ŠÖ”.
//===============================================.
void CCameraBase::AcquisitionDifference()
{
	m_OldCamera = m_Camera;
}
