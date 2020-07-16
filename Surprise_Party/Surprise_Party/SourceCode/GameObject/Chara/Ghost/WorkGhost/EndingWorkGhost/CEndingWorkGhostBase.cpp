#include "CEndingWorkGhostBase.h"
#include "..\..\SpriteEffect\RejoiceEffect\CRejoiceEffect.h"
#include "..\..\SpriteEffect\MoveNoteEffect\CMoveNoteEffect.h"
#include "..\..\SpriteEffect\HaveTroubleEffect\CHaveTroubleEffect.h"

/**************************************************
*		エンディング働くお化け基底クラス.
********************/
CEndingWorkGhostBase::CEndingWorkGhostBase()
	: m_pCSpriteEffect			(nullptr)
	, m_fAcc					(0.0f)
	, m_fAccSpeed				(0.0f)
	, m_fAccMax					(0.0f)
	, m_fGravity				(0.0f)
	, m_vChangeBeforeRotation	(0.0f, 0.0f, 0.0f)
	, m_OldEmotionNum			(static_cast<int>(enEmotionType::Nothing))
	, m_MoveToOuterFlag			(0)
	, m_pCPlaySoundManager		(CPlaySoundManager::GetPlaySoundManager())
	, m_bPlayGoodHumorSound		(false)
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

	//ご機嫌時のエフェクト.
	if (m_EmotionNum == static_cast<int>(enEmotionType::GoodFeeling)) {
		m_pCSpriteEffect.reset(new CMoveNoteEffect());
		//いる座標によって音符の移動角度を変更.
		if (m_vPos.x < m_vLookAtPos.x) {
			m_pCSpriteEffect->SetAngle(MOVE_NOTE_ANGLE);
			return;
		}
		//基準の角度と逆の角度に移動.
		const float INVERSE_NOTE_ANGLE = 180.0f - MOVE_NOTE_ANGLE;
		m_pCSpriteEffect->SetAngle(INVERSE_NOTE_ANGLE);
		return;
	}

	if (m_EmotionNum == static_cast<int>(enEmotionType::HaveTrounble)) {
		m_pCSpriteEffect.reset(new CHaveTroubleEffect());
		//いる座標によって汗の移動角度を変更.
		if (m_vPos.x < m_vLookAtPos.x) {
			m_pCSpriteEffect->SetStartAngle(BASIC_SWAT_ANGLE);
			return;
		}
		//基準の角度と逆の角度に移動.
		m_pCSpriteEffect->SetStartAngle(INVERSE_SWAT_ANGLE);
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
//		エフェクト再生管理処理関数.
//============================================.
void CEndingWorkGhostBase::PlayEffectManager()
{
	//距離計算時の指数.
	const int Index = 2;
	//中央と自分の座標の距離.
	const float m_Length = sqrtf(powf(m_vPos.x - m_vLookAtPos.x, Index) + powf(m_vPos.z - m_vLookAtPos.z, Index));
	if (m_Length > PLAY_DISTANCE_MAX) {
		m_pCSpriteEffect->SetPlayFlag(false);
		m_bPlayGoodHumorSound = false;
		return;
	}

	//再生フラグ設定.
	if (m_pCSpriteEffect->GetRenderFlag() == true) {
		m_pCSpriteEffect->SetPlayFlag(false);
		m_bPlayGoodHumorSound = false;
		return;
	}

	m_pCSpriteEffect->SetPlayFlag(true);

	if (m_bPlayGoodHumorSound == false) {
		m_pCPlaySoundManager->SetPlaySE(enSEType::GoodHumor);
		m_bPlayGoodHumorSound = true;
	}
}

//============================================.
//		外側に移動する処理関数.
//============================================.
void CEndingWorkGhostBase::MoveToOutside()
{
	//距離計算時の指数.
	const int Index = 2;
	//中央と自分の座標の距離.
	const float m_Length = sqrtf(powf(m_vPos.x - m_vLookAtPos.x, Index) + powf(m_vPos.z - m_vLookAtPos.z, Index));
	//見えないところまで来たら移動処理しない.
	if (m_Length > MOVE_DISTANCE_MAX) {
		return;
	}

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
		m_MoveToOuterFlag		= FACE_OUTSIDE;
	}

	//外側を向く処理.
	const float RADIAN_MAX = static_cast<float>(D3DXToRadian(LOOK_BACK_ROT_MAX));
	m_vRot.y += LOOK_BACK_SPEED;
	if (fabsf(m_vRot.y - m_vChangeBeforeRotation.y) > RADIAN_MAX) {
		m_vRot.y = m_vChangeBeforeRotation.y + RADIAN_MAX;
		m_MoveToOuterFlag = MOVE_OUTSIDE;
	}

}