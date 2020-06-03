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
	ConvertRotationMatrixToQuaternion();
}

//====================================.
//	回転行列からクウォータニオンに変換処理関数.
//====================================.
void CGhostBase::ConvertRotationMatrixToQuaternion()
{
	//一時クウォータニオンに変換するように.
	D3DXQUATERNION Tmp;
	D3DXQuaternionRotationMatrix(&Tmp, &m_mPoint);


	//float sinr_cosp = 2 * ((Tmp.w * Tmp.x) + (Tmp.y * Tmp.z));
	//float cosr_cosp = powf(Tmp.w, 2.0f) - powf(Tmp.x, 2.0f) - powf(Tmp.y, 2.0f) + powf(Tmp.z, 2.0f);
	////float cosr_cosp = 1 - (2 * ((Tmp.x * Tmp.x) + (Tmp.y * Tmp.y)));
	//const float Roll = std::atan2f(sinr_cosp , cosr_cosp);

	//float sinp = 2 * ((Tmp.w * Tmp.y) - (Tmp.z * Tmp.x));
	//float Pitch;
	//if (std::fabsf(sinp) >= 1) {
	//	Pitch = static_cast<float>(std::copysign( M_PI / 2, sinp));
	//}
	//else {
	//	Pitch = std::asinf(sinp);
	//}
	//
	//float siny_cosp = 2 * ((Tmp.w * Tmp.z) + (Tmp.x * Tmp.y));
	//float cosy_cosp = powf(Tmp.w, 2.0f) + powf(Tmp.x, 2.0f) - powf(Tmp.y, 2.0f) - powf(Tmp.z, 2.0f);
	////float cosy_cosp = 1 - (2 * ((Tmp.y * Tmp.y) + (Tmp.z * Tmp.z)));
	//
	//const float Yaw = std::atan2f(siny_cosp , cosy_cosp);

	////m_vRot.x = static_cast<float>(D3DXToRadian(Roll));
	////m_vRot.y = static_cast<float>(D3DXToRadian(Pitch));
	////m_vRot.z = static_cast<float>(D3DXToRadian(Yaw));

	float x = Tmp.x; float y = Tmp.y; float z = Tmp.z; float w = Tmp.w;

	float x2 = x * x; float y2 = y * y; float z2 = z * z;

	float xy = x * y; float xz = x * z; 
	float yz = y * z;
	float wx = w * x; float wy = w * y; float wz = w * z;

	float m00 = 1.0f - (2.0f * y2) - (2.0f * z2);
	float m01 = (2.0f * xy) + (2.0f * wz);
	float m10 = (2.0f * xy) - (2.0f * wz);
	float m11 = 1.0f - (2.0f * x2) - (2.0f * z2);
	float m20 = (2.0f * xz) + (2.0f * wy);
	float m21 = (2.0f * yz) - (2.0f * wx);
	float m22 = 1.0f - (2.0f * x2) - (2.0f * y2);

	float tx, ty, tz;
	if (fabsf(1.0f - m21) < FLT_EPSILON) {
		tx = static_cast<float>(M_PI) / 2.0f;
		ty = 0.0f;
		tz = std::atan2f(m10, m00);
	}
	else if (fabsf((-1.0f) - m21) < FLT_EPSILON) {
		tx = static_cast<float>(-M_PI) / 2.0f;
		ty = 0.0f;
		tz = std::atan2f(m10, m00);
	}
	else {
		tx = asinf(-m21);
		ty = atan2f(m20, m22);
		tz = atan2f(m01, m11);
	}

	//tx *= static_cast<float>(360.0f / (M_PI * 2));
	//ty *= static_cast<float>(360.0f / (M_PI * 2));
	//tz *= static_cast<float>(360.0f / (M_PI * 2));


	m_vRot = D3DXVECTOR3(tx, ty, tz);
	//m_vRot = D3DXVECTOR3(Roll, Pitch, Yaw);

	D3DXQUATERNION a;
	D3DXQuaternionRotationYawPitchRoll(&a, m_vRot.z, m_vRot.y, m_vRot.x);

	//角度のD3DXVECTOR3に置換.
	//m_vRot = D3DXVECTOR3(Tmp.x, Tmp.y, Tmp.z) / Tmp.w ;
	//D3DXQuaternionToAxisAngle

	
}