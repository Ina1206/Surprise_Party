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
}

//========================================.
//		エフェクト開始初期化処理関数.
//========================================.
void CQuestionEffect::PlayStartInit(const int& num)
{
	//初期値設定処理関数.
	SettingDefaultValue(num);
	m_fAlpha[num] = 1.0f;
	m_fScale[num] = 1.0f;

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
	m_fAlpha[SpriteNum] = 1.0f;
	m_fScale[SpriteNum] = 1.0f;
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