#include "CChangeSceneCursorUI.h"

/****************************************
*		シーン変更用カーソルUIクラス.
*****************/
CChangeSceneCursorUI::CChangeSceneCursorUI()
	: m_pCSpriteUI				(nullptr)
	, m_vUV						(0.0f, 0.0f)
	, m_vPrePos					(0.0f, 0.0f, 0.0f)
	, m_bSelectFinishFlag		(false)
	, m_bControlFlag			(false)
	, m_ChangeCnt				(0)
	, m_SelectNum				(0)
	, m_fAngle					(0)
	, m_fAcc					(0.0f)
	, m_vJumpBeforePos			(0.0f, 0.0f, 0.0f)
	, m_MaxJump					(1)
	, m_JumpCnt					(0)
	, m_MoveDirect				(RIGHT_DIRECT_NUM)
	, m_vChangeDirectBeforeRot	(0.0f, 0.0f, 0.0f)
	, m_MoveType				(0)
{
	//初期化処理関数.
	Init();
}

CChangeSceneCursorUI::~CChangeSceneCursorUI()
{
	//解放処理関数.
	Release();
}

//======================================.
//		更新処理関数.
//======================================.
void CChangeSceneCursorUI::Update()
{
	if (m_bControlFlag == false) {
		//移動処理関数.
		Move();
		return;
	}

	//操作処理関数.
	Control();
}

//======================================.
//		描画処理関数.
//======================================.
void CChangeSceneCursorUI::Render()
{
	//事前座標.
	m_pCSpriteUI->SetPrePos(m_vPrePos);
	//座標.
	m_pCSpriteUI->SetPosition(m_vPos);
	//角度.
	m_pCSpriteUI->SetRotation(m_vRot);
	//UV座標.
	m_pCSpriteUI->SetPattern(m_vUV);
	//描画.
	m_pCDepthStencil->SetDepth(false);
	m_pCSpriteUI->Render();
	m_pCDepthStencil->SetDepth(true);
}

//======================================.
//		初期化処理関数.
//======================================.
void CChangeSceneCursorUI::Init()
{
	//スプライトUIの情報取得.
	SPRITE_STATE SpriteState = m_pCResourceManager->GetSpriteUIState(enSpriteUI::GhostCursor);

	m_pCSpriteUI = m_pCResourceManager->GetSpriteUI(enSpriteUI::GhostCursor);
	//端っこに設定.
	m_vPos = D3DXVECTOR3(-SpriteState.Disp.w / 2.0f, WND_H / 2.0f, 0.0f);
	m_vRot = RIGHT_CURSOR_ROT;
	m_vUV = NORMAL_UV_POS;

	m_vJumpBeforePos = m_vPos;

	//y軸回転時に回転軸を中央に持ってくる為.
	m_vPrePos = D3DXVECTOR3(-SpriteState.Disp.w / 2.0f, 0.0f, 0.0f);
}

//======================================.
//		解放処理関数.
//======================================.
void CChangeSceneCursorUI::Release()
{

}

//======================================.
//		移動処理関数.
//======================================.
void CChangeSceneCursorUI::Move()
{
	switch (static_cast<enMoveType>(m_MoveType)) {
	case enMoveType::StartMove:

		break;
	case enMoveType::Surprise:

		break;
	case enMoveType::LeftTitleFetch:

		break;
	case enMoveType::LeftTitleCarry:

		break;
	case enMoveType::RightTitleFetch:

		break;
	case enMoveType::RightTitleCarry:

		break;
	case enMoveType::Rejoice:

		break;
	case enMoveType::SelectFetch:

		break;
	case enMoveType::SelectCarry:

		break;
	case enMoveType::BecomeCursor:

		break;
	}
}

//======================================.
//		操作処理関数.
//======================================.
void CChangeSceneCursorUI::Control()
{
	m_bSelectFinishFlag = false;

	//決定後の処理.
	if (m_ChangeCnt > 0) {
		if (m_bChangeWaitFlag == true) {
			m_ChangeCnt++;

			//選択終了.
			if (m_ChangeCnt >= CHANGE_CNT_MAX) {
				m_bSelectFinishFlag = true;
				m_vUV = NORMAL_UV_POS;
				m_ChangeCnt = 0;
			}
			return;
		}

		m_bSelectFinishFlag = true;
		return;
	}

	if (GetAsyncKeyState(VK_UP) & 0x0001) {
		m_SelectNum--;
		if (m_SelectNum < 0) {
			m_SelectNum = 0;
			//SE.

			return;
		}
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x0001) {
		m_SelectNum++;
		if (m_SelectNum >= SELECT_MAX) {
			m_SelectNum = SELECT_MAX - 1;
			//SE.

			return;
		}
	}

	if (GetAsyncKeyState(VK_RETURN) & 0x0001) {
		m_vUV = ENTER_UV_POS;
		//SE.
		m_ChangeCnt++;
	}

	//選択肢の文字の情報取得.
	SPRITE_STATE SpriteState = m_pCResourceManager->GetSpriteUIState(enSpriteUI::StartString);
	m_vPos.x = CONTROL_CURSOR_POS.x;
	m_vPos.y = CONTROL_CURSOR_POS.y + (SpriteState.Disp.h * m_SelectNum);

}

//======================================.
//		上下浮遊処理関数.
//======================================.
void CChangeSceneCursorUI::UpDownFloat()
{
	m_fAngle+= FLOATING_SPEED;
	if (m_fAngle > static_cast<float>(D3DXToRadian(ANGLE_MAX))) {
		m_fAngle = 0.0f;
	}
	m_vPos.y += sin(m_fAngle) * FLOATING_DISTANCE;
}

//=======================================.
//		ジャンプ処理関数.
//=======================================.
bool CChangeSceneCursorUI::Jump()
{
	m_fAcc += ADD_ACC_SPEED;

	m_vPos.y += m_fAcc - GRAVITY;
	if (m_vPos.y > m_vJumpBeforePos.y) {
		m_vPos.y = m_vJumpBeforePos.y;

		//ジャンプ最大数.
		m_JumpCnt++;
		if (m_JumpCnt > m_MaxJump) {
			m_MaxJump++;
			return true;
		}

		m_fAcc = 0.0f;
	}

	return false;
}

//=======================================.
//		移動方向変更処理関数.
//=======================================.
bool CChangeSceneCursorUI::ChangeMoveDirect()
{
	m_vRot.y -= ROTATION_SPEED * m_MoveDirect;
	
	//右と左の方向の差分.
	const float DIFFERENCE_LEFT_RIGHT_ROT = fabsf(RIGHT_CURSOR_ROT.y - LEFT_CURSOR_ROT.y);

	if (fabsf(m_vRot.y - m_vChangeDirectBeforeRot.y) > DIFFERENCE_LEFT_RIGHT_ROT) {
		//移動方向変更.
		m_MoveDirect *= CHANGE_DIRECT;
		
		//右方向.
		if (m_MoveDirect == RIGHT_DIRECT_NUM) {
			m_vRot = RIGHT_CURSOR_ROT;
			return true;
		}

		//左方向.
		m_vRot = LEFT_CURSOR_ROT;
		return true;
	}

	return false;
}