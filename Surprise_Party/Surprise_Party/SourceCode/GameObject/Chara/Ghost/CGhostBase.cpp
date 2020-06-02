#include "CGhostBase.h"

CGhostBase::CGhostBase()
	: m_fMoveAngle	(0.0f)
	, m_EmotionNum(0)
{

}

CGhostBase::~CGhostBase()
{

}

//=======================================.
//		•‚—Vˆ—ŠÖ”.
//=======================================.
void CGhostBase::MoveUpDown()
{
	//ã‰ºˆÚ“®.
	m_fMoveAngle += ANGLE_SPEED;
	if (m_fMoveAngle >= ANGLE_MAX) {
		m_fMoveAngle = ANGLE_MIN;
	}
	m_vPos.y += (sin(m_fMoveAngle) * VERTICAL_WIDTH) * UP_DOWN_SPEED;

}