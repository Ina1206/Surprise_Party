#include "CQuestionEffect.h"

/************************************
*		疑問エフェクトクラス.
***************/
CQuestionEffect::CQuestionEffect()
	: m_fAcc			(0.0f)
	, m_vStartPos		(0.0f, 0.0f, 0.0f)
	, m_MoveFinishFlag	(0)
{
	//初期化処理.
	Init();
}

CQuestionEffect::~CQuestionEffect()
{
	//解放処理関数.
	Release();
}

//========================================.
//		更新処理関数.
//========================================.
void CQuestionEffect::Update()
{
	const int SPRITE_NUM = 0;

	//例外処理.
	if (m_MoveFinishFlag & FINISH_MOVE_VERTICAL) {
		return;
	}

	//移動処理関数.
	Move(SPRITE_NUM);

	//拡縮処理関数.
	Scaling(SPRITE_NUM);
}

//========================================.
//		エフェクト開始初期化処理関数.
//========================================.
void CQuestionEffect::PlayStartInit(const int& num)
{
	//初期値設定処理関数.
	SettingDefaultValue(num);
	m_fAlpha[num] = ALPHA_MAX;
	m_vScale[num] = INIT_SCALE;

	m_fAcc = 0.0f;
	m_vPos[num] = m_vCenterPos;
	m_vStartPos = m_vPos[num];
	
	m_MoveFinishFlag = 0;
}

//========================================.
//		初期化処理関数.
//========================================.
void CQuestionEffect::Init()
{
	m_pCSprite.push_back(m_pCResourceManager->GetSprite(enSprite::QuestionMark));
	SettingElementsCount();

	const int SpriteNum = 0;
	SettingDefaultValue(SpriteNum);
}

//========================================.
//		解放処理関数.
//========================================.
void CQuestionEffect::Release()
{

}

//========================================.
//		表示判定処理関数.
//========================================.
void CQuestionEffect::AppeartJudgement(const int& num)
{

}

//========================================.
//		移動処理関数.
//========================================.
void CQuestionEffect::Move(const int& num)
{
	m_fAcc -= ACC_SPEAD;
	if (m_vPos[num].y < m_vStartPos.y) {
		m_fAcc = 0.0f;
		//はてなマーク時のSE再生.
		m_pCPlaySoundManager->SetPlaySE(enSEType::Question);

		if (m_MoveFinishFlag & FINISH_MOVE_HORIZONTAL) {
			m_MoveFinishFlag |= FINISH_MOVE_VERTICAL;
		}
	}
	m_vPos[num].y += m_fAcc + GRAVITY;

	//横移動終了の場合したまで処理しない.
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
//		拡縮処理関数.
//=======================================.
void CQuestionEffect::Scaling(const int& num)
{
	//移動終了後の拡縮.
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