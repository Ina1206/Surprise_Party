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
	if (m_bFinishedAllDispFlag == true) {
		return;
	}

	if (m_bDisplayAllAtOnce == true) {
		//一気に表示する処理関数.
		DisplayAllAtOnce();
		return;
	}

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
	m_stSpriteState = m_pCResourceManager->GetSpriteUIState(enSpriteUI::HightEvaluationString);
	for (int string = 0; string < m_stSpriteState.Frame.w; string++) {
		m_pCEvaluationUI.push_back(m_pCResourceManager->GetSpriteUI(enSpriteUI::HightEvaluationString));
	}

	//要素数の初期化処理関数.
	InitElementCount();

	for (unsigned int sprite = 0; sprite < m_pCEvaluationUI.size(); sprite++) {
		m_vEvaluationPos[sprite] = INIT_POS;
		m_vEvaluationUV[sprite].x = sprite;
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
	//x軸処理.
	m_vEvaluationScale[m_UpdateNum].x += DISP_SPEED;
	if (m_vEvaluationScale[m_UpdateNum].x >= EATCH_SCALE_MAX.x) {
		m_vEvaluationScale[m_UpdateNum].x = EATCH_SCALE_MAX.x;
		//x軸の処理が終了していたらy軸の処理は他の処理とバッティングしないために処理終了.
		return;
	}

	//y軸処理.
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
	//最終地点.
	const float	FINISH_POS = FINISH_BASE_POS.x + (m_stSpriteState.Disp.w * m_UpdateNum);
	//割合.
	const float RAITO = FINISH_POS / FINISH_BASE_POS.x;

	m_vEvaluationPos[m_UpdateNum].x += MOVE_SPEED * RAITO;

	//最終地点に移動終了.
	if (m_vEvaluationPos[m_UpdateNum].x >= FINISH_POS) {
		m_vEvaluationPos[m_UpdateNum].x = FINISH_POS;
	}
}

//=========================================.
//		ジャンプ処理関数.
//=========================================.
void CHightEvaluationString::Jump()
{
	//次の文字へ変更処理.
	if (m_JumpCnt >= JUMP_CNT_MAX) {
		//初期化処理.
		m_JumpCnt = 0;
		m_fAcc = 0.0f;
		m_vEvaluationPos[m_UpdateNum] = FINISH_BASE_POS;
		m_vEvaluationPos[m_UpdateNum].x += m_stSpriteState.Disp.w * m_UpdateNum;
		
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
	//下がる処理.
	if (m_BoundFlag & BOUND_DOWN_FLAG) {
		m_vEvaluationScale[m_UpdateNum].y -= BOUND_SPEED;
		m_vEvaluationPos[m_UpdateNum].y = FINISH_BASE_POS.y + (m_stSpriteState.Disp.h * (EATCH_SCALE_MAX.y - m_vEvaluationScale[m_UpdateNum].y));
		//上がる処理に変更する処理.
		if (m_vEvaluationScale[m_UpdateNum].y <= EATCH_SCALE_MIN.y) {
			m_vEvaluationScale[m_UpdateNum].y = EATCH_SCALE_MIN.y;
			m_BoundFlag = BOUND_UP_FALG;
			//高評価文字のSE.
			m_pCPlaySoundManager->SetPlaySE(enSEType::HightString);
		}
		return;
	}

	//上がる処理.
	m_vEvaluationScale[m_UpdateNum].y += BOUND_SPEED;
	m_vEvaluationPos[m_UpdateNum].y = FINISH_BASE_POS.y + (m_stSpriteState.Disp.h * (EATCH_SCALE_MAX.y - m_vEvaluationScale[m_UpdateNum].y));
	//バウンド処理終了.
	if (m_vEvaluationScale[m_UpdateNum].y >= EATCH_SCALE_MAX.y) {
		m_vEvaluationScale[m_UpdateNum].y = EATCH_SCALE_MAX.y;
		m_BoundFlag = 0;
	}

}

//===========================================.
//		一気に表示する処理関数.
//===========================================.
void CHightEvaluationString::DisplayAllAtOnce()
{
	//一気に最終地点まで移動する処理.
	for (unsigned int sprite = 0; sprite < m_pCEvaluationUI.size(); sprite++) {
		m_vEvaluationPos[sprite]	= FINISH_BASE_POS;
		m_vEvaluationPos[sprite].x += m_stSpriteState.Disp.w * sprite;
		m_vEvaluationScale[sprite]	= EATCH_SCALE_MAX;
	}
	m_bFinishedAllDispFlag = true;
}