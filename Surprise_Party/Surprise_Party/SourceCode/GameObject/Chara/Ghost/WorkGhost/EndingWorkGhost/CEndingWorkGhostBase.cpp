#include "CEndingWorkGhostBase.h"
#include "..\..\SpriteEffect\RejoiceEffect\CRejoiceEffect.h"

/**************************************************
*		エンディング働くお化け基底クラス.
********************/
CEndingWorkGhostBase::CEndingWorkGhostBase()
	: m_pCSpriteEffect			(nullptr)
	, m_fAcc					(0.0f)
	, m_fAccSpeed				(0.0f)
	, m_fAccMax					(0.0f)
	, m_fGravity				(0.0f)
	, m_OldEmotionNum			(static_cast<int>(enEmotionType::Nothing))
	, m_MoveToOuterFlag			(0)
	, m_vChangeBeforeRotation	(0.0f, 0.0f, 0.0f)
{

}

CEndingWorkGhostBase::~CEndingWorkGhostBase()
{

}

//==========================================.
//		ジャンプ処理関数.
//==========================================.
void CEndingWorkGhostBase::Jump()
{
	m_fAcc -= m_fAccSpeed;
	m_vPos.y += m_fAcc - m_fGravity;


	if (m_vPos.y < m_vChangeBeforePos.y) {
		m_vPos.y = m_vChangeBeforePos.y;
		m_fAcc = m_fAccMax;
	}
}

//===========================================.
//		エフェクト変更処理関数.
//===========================================.
void CEndingWorkGhostBase::ChangeEffect()
{
	if (m_OldEmotionNum == m_EmotionNum) {
		return;
	}

	m_OldEmotionNum = m_EmotionNum;

	if (m_EmotionNum == static_cast<int>(enEmotionType::Rejoice)) {
		m_pCSpriteEffect.reset(new CRejoiceEffect());
		return;
	}
}

//============================================.
//		ご機嫌時の行動処理関数.
//============================================.
void CEndingWorkGhostBase::ActGoodFeeling()
{
	//外側を向く処理関数.
	FaceOutside();

	if (m_MoveToOuterFlag & MOVE_OUTSIDE) {
		//外側に移動する処理関数.
		MoveToOutside();
	}
}

//============================================.
//		外側に移動する処理関数.
//============================================.
void CEndingWorkGhostBase::MoveToOutside()
{
	D3DXVECTOR3 vecAxisZ(VECTOR_AXIS_Z);
	D3DXMATRIX mYaw;
	D3DXMatrixRotationY(&mYaw, m_vRot.y);
	D3DXVec3TransformCoord(&vecAxisZ, &vecAxisZ, &mYaw);

	m_vPos -= vecAxisZ * MOVE_SPEED;
}

//============================================.
//		外側を向く処理関数.
//============================================.
void CEndingWorkGhostBase::FaceOutside()
{
	if (m_MoveToOuterFlag == 0) {
		//移動角度処理関数.
		MoveRotation(m_vPos, m_vLookAtPos);

		m_vChangeBeforeRotation = m_vRot;
		m_MoveToOuterFlag = FACE_OUTSIDE;
	}

	const float RADIAN_MAX = static_cast<float>(D3DXToRadian(LOOK_BACK_ROT_MAX));
	m_vRot.y += LOOK_BACK_SPEED;
	if (fabsf(m_vRot.y - m_vChangeBeforeRotation.y) > RADIAN_MAX) {
		m_vRot.y = m_vChangeBeforeRotation.y + RADIAN_MAX;
		m_MoveToOuterFlag = MOVE_OUTSIDE;
	}

}