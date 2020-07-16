#include "CEndingWorkGhostBase.h"
#include "..\..\SpriteEffect\RejoiceEffect\CRejoiceEffect.h"
#include "..\..\SpriteEffect\MoveNoteEffect\CMoveNoteEffect.h"
#include "..\..\SpriteEffect\HaveTroubleEffect\CHaveTroubleEffect.h"

/**************************************************
*		�G���f�B���O�������������N���X.
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
//		�W�����v�����֐�.
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
//		�G�t�F�N�g�ύX�����֐�.
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

	//���@�����̃G�t�F�N�g.
	if (m_EmotionNum == static_cast<int>(enEmotionType::GoodFeeling)) {
		m_pCSpriteEffect.reset(new CMoveNoteEffect());
		//������W�ɂ���ĉ����̈ړ��p�x��ύX.
		if (m_vPos.x < m_vLookAtPos.x) {
			m_pCSpriteEffect->SetAngle(MOVE_NOTE_ANGLE);
			return;
		}
		//��̊p�x�Ƌt�̊p�x�Ɉړ�.
		const float INVERSE_NOTE_ANGLE = 180.0f - MOVE_NOTE_ANGLE;
		m_pCSpriteEffect->SetAngle(INVERSE_NOTE_ANGLE);
		return;
	}

	if (m_EmotionNum == static_cast<int>(enEmotionType::HaveTrounble)) {
		m_pCSpriteEffect.reset(new CHaveTroubleEffect());
		//������W�ɂ���Ċ��̈ړ��p�x��ύX.
		if (m_vPos.x < m_vLookAtPos.x) {
			m_pCSpriteEffect->SetStartAngle(BASIC_SWAT_ANGLE);
			return;
		}
		//��̊p�x�Ƌt�̊p�x�Ɉړ�.
		m_pCSpriteEffect->SetStartAngle(INVERSE_SWAT_ANGLE);
	}
}

//============================================.
//		���@�����̍s�������֐�.
//============================================.
void CEndingWorkGhostBase::ActGoodFeeling()
{
	//�O�������������֐�.
	FaceOutside();

	if (m_MoveToOuterFlag & MOVE_OUTSIDE) {
		//�O���Ɉړ����鏈���֐�.
		MoveToOutside();
	}
}

//============================================.
//		�G�t�F�N�g�Đ��Ǘ������֐�.
//============================================.
void CEndingWorkGhostBase::PlayEffectManager()
{
	//�����v�Z���̎w��.
	const int Index = 2;
	//�����Ǝ����̍��W�̋���.
	const float m_Length = sqrtf(powf(m_vPos.x - m_vLookAtPos.x, Index) + powf(m_vPos.z - m_vLookAtPos.z, Index));
	if (m_Length > PLAY_DISTANCE_MAX) {
		m_pCSpriteEffect->SetPlayFlag(false);
		m_bPlayGoodHumorSound = false;
		return;
	}

	//�Đ��t���O�ݒ�.
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
//		�O���Ɉړ����鏈���֐�.
//============================================.
void CEndingWorkGhostBase::MoveToOutside()
{
	//�����v�Z���̎w��.
	const int Index = 2;
	//�����Ǝ����̍��W�̋���.
	const float m_Length = sqrtf(powf(m_vPos.x - m_vLookAtPos.x, Index) + powf(m_vPos.z - m_vLookAtPos.z, Index));
	//�����Ȃ��Ƃ���܂ŗ�����ړ��������Ȃ�.
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
//		�O�������������֐�.
//============================================.
void CEndingWorkGhostBase::FaceOutside()
{
	if (m_MoveToOuterFlag == 0) {
		//�ړ��p�x�����֐�.
		MoveRotation(m_vPos, m_vLookAtPos);

		m_vChangeBeforeRotation = m_vRot;
		m_MoveToOuterFlag		= FACE_OUTSIDE;
	}

	//�O������������.
	const float RADIAN_MAX = static_cast<float>(D3DXToRadian(LOOK_BACK_ROT_MAX));
	m_vRot.y += LOOK_BACK_SPEED;
	if (fabsf(m_vRot.y - m_vChangeBeforeRotation.y) > RADIAN_MAX) {
		m_vRot.y = m_vChangeBeforeRotation.y + RADIAN_MAX;
		m_MoveToOuterFlag = MOVE_OUTSIDE;
	}

}