#include "CCameraBase.h"

/**************************************
*		カメラ基底クラス.
**************/
CCameraBase::CCameraBase()
	: m_Camera			()
	, m_MoveFlag		(0)
	, m_vTargetPos		(0.0f, 0.0f, 0.0f)
	, m_OldCamera		()
	, m_bCanSkip		(true)
	, m_bNotRenderMap	(false)
{

}

CCameraBase::~CCameraBase()
{

}

//===============================================.
//		差分取得処理関数.
//===============================================.
void CCameraBase::AcquisitionDifference()
{
	m_OldCamera = m_Camera;
}
