#include "CGhostBase.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <float.h>

CGhostBase::CGhostBase()
	: m_fMoveAngle	(0.0f)
	, m_EmotionNum	(0)
	, m_mPoint		()
	, m_vLookAtPos	(5.0f, -0.8f, 5.0f)
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

//===================================.
//		移動角度処理関数.
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

	//回転行列からクォータニオンに変換処理関数.
	ConvertRotationMatrixToRadian(m_mPoint);
}

//====================================.
//	回転行列からクウォータニオンに変換処理関数.
//====================================.
void CGhostBase::ConvertRotationMatrixToRadian(const D3DXMATRIX& mMat)
{
	//オイラー角に変換するために回転行列からクォータニオンへ変換.
	D3DXQUATERNION Tmp;
	D3DXQuaternionRotationMatrix(&Tmp, &m_mPoint);

	//それぞれ2乗にする.
	const int Index = 2;
	const float Powx = pow(Tmp.x, Index); 
	const float Powy = pow(Tmp.y, Index);
	const float Powz = pow(Tmp.z, Index);

	//4つ全てそれぞれ組み合わせて掛ける.
	const float xy = Tmp.x * Tmp.y; 
	const float xz = Tmp.x * Tmp.z;
	const float yz = Tmp.y * Tmp.z;
	const float wx = Tmp.w * Tmp.x; 
	const float wy = Tmp.w * Tmp.y; 
	const float wz = Tmp.w * Tmp.z;


	const float m00 = 1.0f - (2.0f * Powy) - (2.0f * Powz);
	const float m01 = (2.0f * xy) + (2.0f * wz);
	const float m10 = (2.0f * xy) - (2.0f * wz);
	const float m11 = 1.0f - (2.0f * Powx) - (2.0f * Powz);
	const float m20 = (2.0f * xz) + (2.0f * wy);
	const float m21 = (2.0f * yz) - (2.0f * wx);
	const float m22 = 1.0f - (2.0f * Powx) - (2.0f * Powy);

	//クォータニオンからラジアンに変換用変数.
	D3DXVECTOR3 m_vQueToRot;
	//FLT_EPSILON:類似.
	if (fabsf(1.0f - m21) < FLT_EPSILON) {
		m_vQueToRot.x = static_cast<float>(M_PI) / 2.0f;
		m_vQueToRot.y = 0.0f;
		m_vQueToRot.z = std::atan2f(m10, m00);
	}
	else if (fabsf((-1.0f) - m21) < FLT_EPSILON) {
		m_vQueToRot.x = static_cast<float>(-M_PI) / 2.0f;
		m_vQueToRot.y = 0.0f;
		m_vQueToRot.z = std::atan2f(m10, m00);
	}
	else {
		m_vQueToRot.x = asinf(-m21);
		m_vQueToRot.y = atan2f(m20, m22);
		m_vQueToRot.z = atan2f(m01, m11);
	}

	m_vRot = m_vQueToRot;
}