#include "CGhostBase.h"

CGhostBase::CGhostBase()
	: m_fMoveAngle	(0.0f)
	, m_EmotionNum	(0)
	, m_bUseRotFlag	(true)
	, m_mPoint()
{

}

CGhostBase::~CGhostBase()
{

}

//=======================================.
//		ïÇóVèàóùä÷êî.
//=======================================.
void CGhostBase::MoveUpDown()
{
	//è„â∫à⁄ìÆ.
	m_fMoveAngle += ANGLE_SPEED;
	if (m_fMoveAngle >= ANGLE_MAX) {
		m_fMoveAngle = ANGLE_MIN;
	}
	m_vPos.y += (sin(m_fMoveAngle) * VERTICAL_WIDTH) * UP_DOWN_SPEED;

}

//===================================.
//		à⁄ìÆäpìxèàóùä÷êî.
//===================================.
void CGhostBase::MoveRotation(const D3DXVECTOR3& vSalfPos, const D3DXVECTOR3& vTargetPos)
{
	D3DXVECTOR3 Z = vSalfPos - vTargetPos;
	D3DXVECTOR3 X, Y;

	D3DXVec3Normalize(&Z, &Z);
	D3DXVec3Cross(&X, D3DXVec3Normalize(&Y, &SKY_DIRECT), &Z);
	D3DXVec3Normalize(&X, &X);
	D3DXVec3Normalize(&Y, D3DXVec3Cross(&Y, &Z, &X));

	m_mPoint._11 = X.x;  m_mPoint._12 = X.y;  m_mPoint._13 = X.z;   m_mPoint._14 = 0;
	m_mPoint._21 = Y.x;  m_mPoint._22 = Y.y;  m_mPoint._23 = Y.z;   m_mPoint._24 = 0;
	m_mPoint._31 = Z.x;  m_mPoint._32 = Z.y;  m_mPoint._33 = Z.z;   m_mPoint._34 = 0;
	m_mPoint._41 = 0.0f; m_mPoint._42 = 0.0f; m_mPoint._43 = 0.0f;  m_mPoint._44 = 1.0f;

	m_bUseRotFlag = false;
}