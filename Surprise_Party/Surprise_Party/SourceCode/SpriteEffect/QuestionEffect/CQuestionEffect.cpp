#include "CQuestionEffect.h"

/************************************
*		�^��G�t�F�N�g�N���X.
***************/
CQuestionEffect::CQuestionEffect()
	: m_fAcc			(0.0f)
	, m_vStartPos		(0.0f, 0.0f, 0.0f)
	, m_MoveFinishFlag	(0)
{
	//����������.
	Init();
}

CQuestionEffect::~CQuestionEffect()
{
	//��������֐�.
	Release();
}

//========================================.
//		�X�V�����֐�.
//========================================.
void CQuestionEffect::Update()
{
	const int SPRITE_NUM = 0;

	//��O����.
	if (m_MoveFinishFlag & FINISH_MOVE_VERTICAL) {
		return;
	}

	//�ړ������֐�.
	Move(SPRITE_NUM);

	//�g�k�����֐�.
	Scaling(SPRITE_NUM);
}

//========================================.
//		�G�t�F�N�g�J�n�����������֐�.
//========================================.
void CQuestionEffect::PlayStartInit(const int& num)
{
	//�����l�ݒ菈���֐�.
	SettingDefaultValue(num);
	m_fAlpha[num] = ALPHA_MAX;
	m_vScale[num] = INIT_SCALE;

	m_fAcc = 0.0f;
	m_vPos[num] = m_vCenterPos;
	m_vStartPos = m_vPos[num];
	
	m_MoveFinishFlag = 0;
}

//========================================.
//		�����������֐�.
//========================================.
void CQuestionEffect::Init()
{
	m_pCSprite.push_back(m_pCResourceManager->GetSprite(enSprite::QuestionMark));
	SettingElementsCount();

	const int SpriteNum = 0;
	SettingDefaultValue(SpriteNum);
}

//========================================.
//		��������֐�.
//========================================.
void CQuestionEffect::Release()
{

}

//========================================.
//		�\�����菈���֐�.
//========================================.
void CQuestionEffect::AppeartJudgement(const int& num)
{

}

//========================================.
//		�ړ������֐�.
//========================================.
void CQuestionEffect::Move(const int& num)
{
	m_fAcc -= ACC_SPEAD;
	if (m_vPos[num].y < m_vStartPos.y) {
		m_fAcc = 0.0f;
		//�͂Ăȃ}�[�N����SE�Đ�.
		m_pCPlaySoundManager->SetPlaySE(enSEType::Question);

		if (m_MoveFinishFlag & FINISH_MOVE_HORIZONTAL) {
			m_MoveFinishFlag |= FINISH_MOVE_VERTICAL;
		}
	}
	m_vPos[num].y += m_fAcc + GRAVITY;

	//���ړ��I���̏ꍇ�����܂ŏ������Ȃ�.
	if (m_MoveFinishFlag & FINISH_MOVE_HORIZONTAL) {
		return;
	}

	m_fDistance[num] += MOVE_SPEED;
	if (m_fDistance[num] > DISTANCE_MAX) {
		m_fDistance[num] = DISTANCE_MAX;
		m_MoveFinishFlag |= FINISH_MOVE_HORIZONTAL;
	}
	m_vPos[num].x = m_vStartPos.x + m_fDistance[num];

}

//=======================================.
//		�g�k�����֐�.
//=======================================.
void CQuestionEffect::Scaling(const int& num)
{
	//�ړ��I����̊g�k.
	if (m_MoveFinishFlag & FINISH_MOVE_HORIZONTAL) {
		m_vScale[num].y += SCALING_SPEED;
		if (m_vScale[num].y >= SCALE_MAX.y) {
			m_vScale[num].y = SCALE_MAX.y;
		}
		return;
	}

	m_vScale[num].y = SCALE_MAX.y - fabsf((m_fAcc + GRAVITY) / GRAVITY);
	if (m_vScale[num].y < SCALING_MIN) {
		m_vScale[num].y = SCALING_MIN;
	}
}