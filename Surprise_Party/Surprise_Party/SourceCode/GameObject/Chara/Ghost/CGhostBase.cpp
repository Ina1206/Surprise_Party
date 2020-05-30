#include "CGhostBase.h"

CGhostBase::CGhostBase()
	: m_fMoveAngle	(0.0f)
{

}

CGhostBase::~CGhostBase()
{

}

//=======================================.
//		浮遊処理関数.
//=======================================.
void CGhostBase::MoveUpDown()
{
	//上下移動.
	m_fMoveAngle += ANGLE_SPEED;
	if (m_fMoveAngle >= ANGLE_MAX) {
		m_fMoveAngle = ANGLE_MIN;
	}
	m_vPos.y += (sin(m_fMoveAngle) * VERTICAL_WIDTH) * UP_DOWN_SPEED;

}