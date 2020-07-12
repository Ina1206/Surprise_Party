#include "CShout.h"

/*****************************************
*		叫びクラス.
********************/
CShout::CShout()
	: m_fAcc		(0.0f)
	, m_JumpCnt		(0)
	, m_BoundFlag	(0)
{
	//初期化処理関数.
	Init();
}

CShout::~CShout()
{
	//解放処理関数.
	Release();
}

//=========================================.
//		更新処理関数.
//=========================================.
void CShout::Update()
{
	if (m_bDisplayAllAtOnce == true) {
		//一気に表示する処理関数.
		DisplayAllAtOnce();
		return;
	}

	//移動処理関数.
	Move();

	//表示処理関数.
	Disp();

	if (m_JumpCnt >= JUMP_MAX) {
		return;
	}

	if (m_BoundFlag != 0) {
		//スプライトのバウンド処理関数.
		BoundSprite();
		return;
	}

	//ジャンプ処理関数.
	Jump();
}

//=========================================.
//		初期化処理関数.
//=========================================.
void CShout::Init()
{
	m_pCSpriteUI = m_pCResourceManager->GetSpriteUI(enSpriteUI::Shout);
	m_vPos = INIT_POS;

	//重力と加速度の差分が0.0fになるように.
	m_fAcc = GRAVITY;
	
	m_JumpCnt = 0;
	m_vEatchSizeScale = EATCH_SCALE_MIN;
}

//==========================================.
//		解放処理関数.
//==========================================.
void CShout::Release()
{

}

//==========================================.
//		移動処理関数.
//==========================================.
void CShout::Move()
{
	//スプライト情報.
	const SPRITE_STATE SpriteState = m_pCResourceManager->GetSpriteUIState(enSpriteUI::Shout);
	//最終座標.
	const float	FINISH_POS = FINISH_BASE_POS.x + (SpriteState.Disp.w * (m_DipslayNum - 1));
	//割合.
	const float	RATIO = (FINISH_POS - INIT_POS.x) / (FINISH_BASE_POS.x - INIT_POS.x);

	m_vPos.x += MOVE_SPEED * RATIO;
	if (m_vPos.x > FINISH_POS) {
		m_vPos = FINISH_BASE_POS;
		m_vPos.x = FINISH_POS;
		m_bDispFlag = true;
	}
}

//===========================================.
//		スプライトのバウンド処理関数.
//===========================================.
void CShout::BoundSprite()
{
	SPRITE_STATE SpriteState = m_pCResourceManager->GetSpriteUIState(enSpriteUI::Shout);

	if (m_BoundFlag & BOUND_DOWN_FLAG) {
		m_vEatchSizeScale.y -= BOUND_SPEED;
		m_vPos.y = FINISH_BASE_POS.y + (SpriteState.Disp.h * ( EATCH_SCALE_MAX.y - m_vEatchSizeScale.y));
		if (m_vEatchSizeScale.y <= EATCH_SCALE_MIN.y) {
			m_vEatchSizeScale.y = EATCH_SCALE_MIN.y;
			m_BoundFlag = BOUND_UP_FALG;
		}
		return;
	}

	m_vEatchSizeScale.y += BOUND_SPEED;
	m_vPos.y = FINISH_BASE_POS.y + (SpriteState.Disp.h * ( EATCH_SCALE_MAX.y - m_vEatchSizeScale.y));
	if (m_vEatchSizeScale.y >= EATCH_SCALE_MAX.y) {
		m_vEatchSizeScale.y = EATCH_SCALE_MAX.y;
		m_BoundFlag = 0;
	}
}

//===========================================.
//		表示処理関数.
//===========================================.
void CShout::Disp()
{
	m_vEatchSizeScale.x += DISP_SPEED;
	if (m_vEatchSizeScale.x > EATCH_SCALE_MAX.x) {
		m_vEatchSizeScale.x = EATCH_SCALE_MAX.x;
		return;
	}

	m_vEatchSizeScale.y += DISP_SPEED;
	if (m_vEatchSizeScale.y > EATCH_SCALE_MAX.y) {
		m_vEatchSizeScale.y = EATCH_SCALE_MAX.y;
	}
}

//===========================================.
//		ジャンプ処理関数.
//===========================================.
void CShout::Jump()
{
	m_fAcc += ACC_ADD_SPEED;

	m_vPos.y += m_fAcc - GRAVITY;
	if (m_vPos.y > FINISH_BASE_POS.y) {
		m_vPos.y = FINISH_BASE_POS.y;
		m_fAcc = 0.0f;
		m_JumpCnt++;

		//バウンド準備.
		if (m_JumpCnt <= BOUND_MAX) {
			m_BoundFlag = BOUND_DOWN_FLAG;
		}
	}
}

//============================================.
//		一気に表示する処理関数.
//============================================.
void CShout::DisplayAllAtOnce()
{
	SPRITE_STATE SpriteState = m_pCResourceManager->GetSpriteUIState(enSpriteUI::Shout);
	m_vPos = FINISH_BASE_POS;
	m_vPos.x += SpriteState.Disp.w * (m_DipslayNum - 1);
	m_vEatchSizeScale = EATCH_SCALE_MAX;
	m_bDispFlag = true;
}