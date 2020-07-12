#include "CHightEvaluationString.h"

/**********************************************
*		高評価文字クラス.
*********************/
CHightEvaluationString::CHightEvaluationString()
	: m_fAcc		(0.0f)
	, m_JumpCnt		(0)
	, m_BoundCnt	(0)
	, m_BoundFlag	(0)
{
	//初期化処理関数.
	Init();
}

CHightEvaluationString::~CHightEvaluationString()
{
	//解放処理関数.
	Release();
}

//=========================================.
//		更新処理関数.
//=========================================.
void CHightEvaluationString::Update()
{
	//表示処理関数.
	Disp();

	//移動処理関数.
	Move();

	if (m_BoundFlag == 0) {
		//ジャンプ処理関数.
		Jump();
		return;
	}

	//バウンド処理関数.
	Bound();
}

//=========================================.
//		初期化処理関数.
//=========================================.
void CHightEvaluationString::Init()
{
	const SPRITE_STATE SpriteState = m_pCResourceManager->GetSpriteUIState(enSpriteUI::HightEvaluationString);
	for (int string = 0; string < SpriteState.Frame.w; string++) {
		m_pCEvaluationUI.push_back(m_pCResourceManager->GetSpriteUI(enSpriteUI::HightEvaluationString));
	}

	//要素数の初期化処理関数.
	InitElementCount();

	for (unsigned int sprite = 0; sprite < m_pCEvaluationUI.size(); sprite++) {
		m_vEvaluationPos[sprite] = INIT_POS;
		m_vEvaluationUV[sprite] = D3DXVECTOR2(1.0f * sprite, 0.0f);
		m_vEvaluationScale[sprite] = EATCH_SCALE_MIN;
	}

}

//=========================================.
//		解放処理関数.
//=========================================.
void CHightEvaluationString::Release()
{

}

//=========================================.
//		表示処理関数.
//=========================================.
void CHightEvaluationString::Disp()
{
	m_vEvaluationScale[m_UpdateNum].x += DISP_SPEED;
	if (m_vEvaluationScale[m_UpdateNum].x >= EATCH_SCALE_MAX.x) {
		m_vEvaluationScale[m_UpdateNum].x = EATCH_SCALE_MAX.x;
		return;
	}

	m_vEvaluationScale[m_UpdateNum].y += DISP_SPEED;
	if (m_vEvaluationScale[m_UpdateNum].y >= EATCH_SCALE_MAX.y) {
		m_vEvaluationScale[m_UpdateNum].y = EATCH_SCALE_MAX.y;
	}
}

//=========================================.
//		移動処理関数.
//=========================================.
void CHightEvaluationString::Move()
{
	const SPRITE_STATE SpriteState = m_pCResourceManager->GetSpriteUIState(enSpriteUI::HightEvaluationString);
	//最終地点.
	const float	FINISH_POS = FINISH_BASE_POS.x + (SpriteState.Disp.w * m_UpdateNum);
	//割合.
	const float RAITO = FINISH_POS / FINISH_BASE_POS.x;

	m_vEvaluationPos[m_UpdateNum].x += MOVE_SPEED * RAITO;

	if (m_vEvaluationPos[m_UpdateNum].x >= FINISH_POS) {
		m_vEvaluationPos[m_UpdateNum].x = FINISH_POS;
	}
}

//=========================================.
//		ジャンプ処理関数.
//=========================================.
void CHightEvaluationString::Jump()
{
	if (m_JumpCnt >= JUMP_CNT_MAX) {
		m_JumpCnt = 0;
		m_fAcc = 0.0f;
		SPRITE_STATE SpriteState = m_pCResourceManager->GetSpriteUIState(enSpriteUI::HightEvaluationString);
		m_vEvaluationPos[m_UpdateNum] = FINISH_BASE_POS;
		m_vEvaluationPos[m_UpdateNum].x += SpriteState.Disp.w * m_UpdateNum;
		//次の文字へ.
		m_UpdateNum++;
		if (m_UpdateNum >= static_cast<int>(m_pCEvaluationUI.size())) {
			m_bFinishedAllDispFlag = true;
		}
		return;
	}

	m_fAcc += ADD_ACC_SPEED;

	m_vEvaluationPos[m_UpdateNum].y += m_fAcc - GRAVITY;
	if (m_vEvaluationPos[m_UpdateNum].y > FINISH_BASE_POS.y) {
		//初回のみバウンドさせる.
		if (m_JumpCnt == 0) {
			m_BoundFlag = BOUND_DOWN_FLAG;
		}

		m_fAcc = 0.0f;
		m_vEvaluationPos[m_UpdateNum].y = FINISH_BASE_POS.y;
		m_JumpCnt++;
	}
}

//=========================================.
//		バウンド処理関数.
//=========================================.
void CHightEvaluationString::Bound()
{
	SPRITE_STATE SpriteState = m_pCResourceManager->GetSpriteUIState(enSpriteUI::HightEvaluationString);

	//下がる処理.
	if (m_BoundFlag & BOUND_DOWN_FLAG) {
		m_vEvaluationScale[m_UpdateNum].y -= BOUND_SPEED;
		m_vEvaluationPos[m_UpdateNum].y = FINISH_BASE_POS.y + (SpriteState.Disp.h * (EATCH_SCALE_MAX.y - m_vEvaluationScale[m_UpdateNum].y));
		if (m_vEvaluationScale[m_UpdateNum].y <= EATCH_SCALE_MIN.y) {
			m_vEvaluationScale[m_UpdateNum].y = EATCH_SCALE_MIN.y;
			m_BoundFlag = BOUND_UP_FALG;
		}
		return;
	}

	//上がる処理.
	m_vEvaluationScale[m_UpdateNum].y += BOUND_SPEED;
	m_vEvaluationPos[m_UpdateNum].y = FINISH_BASE_POS.y + (SpriteState.Disp.h * (EATCH_SCALE_MAX.y - m_vEvaluationScale[m_UpdateNum].y));
	if (m_vEvaluationScale[m_UpdateNum].y >= EATCH_SCALE_MAX.y) {
		m_vEvaluationScale[m_UpdateNum].y = EATCH_SCALE_MAX.y;
		m_BoundFlag = 0;
	}

}