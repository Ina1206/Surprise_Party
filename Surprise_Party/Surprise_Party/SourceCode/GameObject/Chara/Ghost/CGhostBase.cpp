#include "CGhostBase.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <float.h>

/******************************************************
*				���������N���X.
*******************/
CGhostBase::CGhostBase()
	: m_EmotionNum		(0)
	, m_vLookAtPos		(5.0f, -0.8f, 5.0f)
	, m_vPrePos			(0.0f, 0.0f, 0.0f)
	, m_vChangeBeforePos(-1.0f, -1.0f, -1.0f)
	, m_fMoveAngle		(0.0f)
	, m_bPauseFlag		(false)
{

}

CGhostBase::~CGhostBase()
{

}

//=======================================.
//		���V�����֐�.
//=======================================.
void CGhostBase::MoveUpDown()
{
	//�㉺�ړ�.
	m_fMoveAngle += ANGLE_SPEED;
	if (m_fMoveAngle >= ANGLE_MAX) {
		m_fMoveAngle = ANGLE_MIN;
	}
	m_vPos.y += (sin(m_fMoveAngle) * VERTICAL_WIDTH) * UP_DOWN_SPEED;

}

//===================================.
//		�ړ��p�x�����֐�.
//===================================.
void CGhostBase::MoveRotation(const D3DXVECTOR3& vSalfPos, const D3DXVECTOR3& vTargetPos)
{
	D3DXMATRIX MATRIX_POINT;
	D3DXVECTOR3 Z = vSalfPos - vTargetPos;
	D3DXVECTOR3 X, Y;

	D3DXVec3Normalize(&Z, &Z);
	D3DXVec3Cross(&X, D3DXVec3Normalize(&Y, &SKY_DIRECT), &Z);
	D3DXVec3Normalize(&X, &X);
	D3DXVec3Normalize(&Y, D3DXVec3Cross(&Y, &Z, &X));

	MATRIX_POINT._11 = X.x;  MATRIX_POINT._12 = X.y;  MATRIX_POINT._13 = X.z;   MATRIX_POINT._14 = 0;
	MATRIX_POINT._21 = Y.x;  MATRIX_POINT._22 = Y.y;  MATRIX_POINT._23 = Y.z;   MATRIX_POINT._24 = 0;
	MATRIX_POINT._31 = Z.x;  MATRIX_POINT._32 = Z.y;  MATRIX_POINT._33 = Z.z;   MATRIX_POINT._34 = 0;
	MATRIX_POINT._41 = 0.0f; MATRIX_POINT._42 = 0.0f; MATRIX_POINT._43 = 0.0f;  MATRIX_POINT._44 = 1.0f;

	//��]�s�񂩂�N�H�[�^�j�I���ɕϊ������֐�.
	ConvertRotationMatrixToRadian(MATRIX_POINT);
}

//====================================.
//	��]�s�񂩂�N�E�H�[�^�j�I���ɕϊ������֐�.
//====================================.
void CGhostBase::ConvertRotationMatrixToRadian(const D3DXMATRIX& mMat)
{
	//�I�C���[�p�ɕϊ����邽�߂ɉ�]�s�񂩂�N�H�[�^�j�I���֕ϊ�.
	D3DXQUATERNION Tmp;
	D3DXQuaternionRotationMatrix(&Tmp, &mMat);

	//���ꂼ��2��ɂ���.
	const int Index = 2;
	const float Powx = pow(Tmp.x, Index); 
	const float Powy = pow(Tmp.y, Index);
	const float Powz = pow(Tmp.z, Index);

	//4�S�Ă��ꂼ��g�ݍ��킹�Ċ|����.
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

	//�N�H�[�^�j�I�����烉�W�A���ɕϊ��p�ϐ�.
	D3DXVECTOR3 m_vQueToRot;
	//FLT_EPSILON:�ގ�.
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