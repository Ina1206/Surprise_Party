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
	, m_bChangeDirect			(false)
	, m_vChangeDirectBeforeRot	(0.0f, 0.0f, 0.0f)
	, m_MoveWaitCnt				(0)
	, m_bArrivalFlga			(false)
	, m_vCarryStartPos			(0.0f, 0.0f, 0.0f)
	, m_CarryFlag				(0)
	, m_FetchFlag				(0)
	, m_fCarryDisntace			(0.0f)
	, m_MoveType				(0)
	, m_OutSidePos				(false)
	, m_pCPlaySoundManager		(CPlaySoundManager::GetPlaySoundManager())
	, m_bPlayJumpSE				(false)
	, m_bPlayTurnSE				(false)
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
		Act();
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
	m_OutSidePos = -SpriteState.Disp.w / 2.0f;

	m_pCSpriteUI = m_pCResourceManager->GetSpriteUI(enSpriteUI::GhostCursor);
	//端っこに設定.
	m_vPos = D3DXVECTOR3(m_OutSidePos, SCREEN_CENTER_POS.y, 0.0f);
	m_vRot = RIGHT_CURSOR_ROT;
	m_vUV = NORMAL_UV_POS;

	m_vJumpBeforePos = m_vPos;

	//y軸回転時に回転軸を中央に持ってくる為.
	m_vPrePos = D3DXVECTOR3(m_OutSidePos, 0.0f, 0.0f);
}

//======================================.
//		解放処理関数.
//======================================.
void CChangeSceneCursorUI::Release()
{

}

//======================================.
//		行動処理関数.
//======================================.
void CChangeSceneCursorUI::Act()
{
	switch (static_cast<enMoveType>(m_MoveType)) {
	case enMoveType::StartMove:
		//開始時の移動処理関数.
		MoveStart();

		break;
	case enMoveType::Surprise:
		//驚き処理関数.
		Surprise();

		break;
	case enMoveType::LeftTitleFetch:
		//左タイトル文章取りに行く処理関数.
		LeftTitleFetch();

		break;
	case enMoveType::LeftTitleCarry:
		//左タイトル文章運ぶ処理関数.
		LeftTitleCarry();

		break;
	case enMoveType::RightTitleFetch:
		//右タイトル文章取りに行く処理関数.
		RightTitleFetch();

		break;
	case enMoveType::RightTitleCarry:
		//右タイトル文章取りに行く処理関数.
		RightTitleCarry();

		break;
	case enMoveType::Rejoice:
		//喜び処理関数.
		Rejoice();
		break;
	case enMoveType::SelectFetch:
		//選択肢を取りに行く処理関数.
		SelectFetch();

		break;
	case enMoveType::SelectCarry:
		//選択肢を運ぶ処理関数.
		SelectCarry();

		break;
	case enMoveType::BecomeCursor:
		//カーソルになる処理関数.
		BecomeCursor();

		break;
	}
}

//======================================.
//		操作処理関数.
//======================================.
void CChangeSceneCursorUI::Control()
{
	m_bSelectFinishFlag = false;
	m_vRot = RIGHT_CURSOR_ROT;

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

	m_vUV = NORMAL_UV_POS;

	if (GetAsyncKeyState(VK_UP) & 0x0001) {
		m_SelectNum--;
		if (m_SelectNum < 0) {
			m_SelectNum = 0;
			//SE.
			m_pCPlaySoundManager->SetPlaySE(enSEType::LimitMoveCursor);
			return;
		}
		m_pCPlaySoundManager->SetPlaySE(enSEType::MoveCursor);
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x0001) {
		m_SelectNum++;
		if (m_SelectNum >= SELECT_MAX) {
			m_SelectNum = SELECT_MAX - 1;
			//SE.
			m_pCPlaySoundManager->SetPlaySE(enSEType::LimitMoveCursor);
			return;
		}
		m_pCPlaySoundManager->SetPlaySE(enSEType::MoveCursor);
	}

	if (GetAsyncKeyState(VK_RETURN) & 0x0001) {
		m_vUV = ENTER_UV_POS;
		//SE.
		m_pCPlaySoundManager->SetPlaySE(enSEType::SelectDecide);
		m_ChangeCnt++;
	}

	//選択肢の文字の情報取得.
	SPRITE_STATE SpriteState = m_pCResourceManager->GetSpriteUIState(enSpriteUI::StartString);
	m_vPos.x = CONTROL_CURSOR_POS.x;
	m_vPos.y = CONTROL_CURSOR_POS.y + (SpriteState.Disp.h * m_SelectNum);

}

//======================================.
//		移動処理関数.
//======================================.
bool CChangeSceneCursorUI::Move(const float& MoveDistanceMax) 
{
	m_vPos.x += MOVE_SPEED * m_MoveDirect;
	
	//例外処理.
	if (MoveDistanceMax < m_OutSidePos) {
		return false;
	}

	//1フレームの移動速度内の距離が微調整.
	if (fabsf(MoveDistanceMax - m_vPos.x) <= MOVE_SPEED) {
		m_vPos.x = MoveDistanceMax;
		return true;
	}

	return false;
}

//======================================.
//		目的地への移動処理関数.
//======================================.
bool CChangeSceneCursorUI::MoveToDestination(const D3DXVECTOR3& vTargetPos)
{
	if (m_bArrivalFlga == true) {
		return true;
	}

	const D3DXVECTOR3	vTargetGhostPos = vTargetPos - m_vPos;		//2点間の距離.
	const float			fLength = D3DXVec3Length(&vTargetGhostPos);	//長さ.
	const D3DXVECTOR3	vUnit = vTargetGhostPos / fLength;			//割合.

	m_vPos += MOVE_SPEED * vUnit;

	//1フレームの移動速度内の距離が微調整.
	if (fabsf(vTargetPos.x - m_vPos.x) <= MOVE_SPEED) {
		m_bArrivalFlga = true;
		return true;
	}

	return false;
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
	//移動待機.
	if (m_MoveWaitCnt > 0) {
		
		m_MoveWaitCnt++;

		if (m_MoveWaitCnt > MOVE_WAIT_MAX) {
			m_MoveWaitCnt = 0;
			m_fAcc = 0.0f;
			m_JumpCnt = 0;
			return true;
		}
		return false;
	}

	if (m_bPlayJumpSE == false) {
		m_pCPlaySoundManager->SetPlaySE(enSEType::Jump);
		m_bPlayJumpSE = true;
	}

	m_fAcc += ADD_ACC_SPEED;

	m_vPos.y += m_fAcc - GRAVITY;

	if (m_vPos.y > m_vJumpBeforePos.y) {
		m_vPos.y = m_vJumpBeforePos.y;

		m_bPlayJumpSE = false;

		//ジャンプ最大数.
		m_JumpCnt++;
		if (m_JumpCnt >= m_MaxJump) {
			m_MaxJump++;
			//移動待機カウント加算.
			m_MoveWaitCnt++;
			return false;
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
	
	if (m_bPlayTurnSE == false) {
		m_pCPlaySoundManager->SetPlaySE(enSEType::Turn);
		m_bPlayTurnSE = true;
	}

	//右と左の方向の差分.
	const float DIFFERENCE_LEFT_RIGHT_ROT = fabsf(RIGHT_CURSOR_ROT.y - LEFT_CURSOR_ROT.y);

	if (fabsf(m_vRot.y - m_vChangeDirectBeforeRot.y) > DIFFERENCE_LEFT_RIGHT_ROT) {
		m_bPlayTurnSE = false;

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

//========================================.
//		運び移動処理関数.
//========================================.
void CChangeSceneCursorUI::CarryMove()
{
	//例外処理用数値.
	const float ExceptionHandlingNumber = -1000.0f;
	//移動処理関数.
	Move(ExceptionHandlingNumber);

	m_fCarryDisntace = m_vPos.x - m_vCarryStartPos.x;
}

//=========================================.
//		文章を取りに行く処理関数.
//=========================================.
bool CChangeSceneCursorUI::FetchString(const float& MoveDistanceMax)
{
	//上下浮遊処理関数.
	UpDownFloat();

	//移動処理関数.
	if (Move(MoveDistanceMax) == true) {
		if (ChangeMoveDirect() == true) {
			m_vPos = m_vCarryStartPos;
			m_fCarryDisntace = 0.0f;
			m_MoveType++;
			return true;
		}
	}

	return false;
}

//==========================================.
//		開始時の移動処理関数.
//==========================================.
void CChangeSceneCursorUI::MoveStart()
{
	//上下浮遊処理関数.
	UpDownFloat();
	//移動処理関数(画面中央まで).
	if (Move(SCREEN_CENTER_POS.x) == true) {
		m_vChangeDirectBeforeRot = m_vRot;
		m_vJumpBeforePos = m_vPos;
		m_MoveType++;
	}
}

//==========================================.
//		驚き処理関数.
//==========================================.
void CChangeSceneCursorUI::Surprise()
{
	if (m_bChangeDirect == false) {
		//移動方向変更処理関数.
		m_bChangeDirect = ChangeMoveDirect();
		return;
	}

	m_vUV = SURPRISE_UV_POS;
	
	//ジャンプ処理関数.
	if (Jump() == true) {
		m_vUV = HAVE_TROUBLE_UV_POS;
		m_bChangeDirect = false;
		m_FetchFlag = LEFT_TITLE_FETCH_FLAG;
		m_MoveType++;
	}

}

//==========================================.
//		左タイトル文章取りに行く処理関数.
//==========================================.
void CChangeSceneCursorUI::LeftTitleFetch()
{
	//文章を取りに行く処理関数.
	if (FetchString(m_OutSidePos) == true) {
		m_vPos.x += m_OutSidePos;
		m_CarryFlag = LEFT_TITLE_CARRY_FLAG;
	}

}

//==========================================.
//		左タイトル文章運ぶ処理関数.
//==========================================.
void CChangeSceneCursorUI::LeftTitleCarry()
{
	//運び移動処理関数.
	CarryMove();

	if (m_CarryFlag == 0) {
		m_MoveType++;
		m_FetchFlag = RIGHT_TITLE_FETCH_FLAG;
	}
}

//==========================================.
//		右タイトル文章取りに行く処理関数.
//==========================================.
void CChangeSceneCursorUI::RightTitleFetch()
{
	//文章を取りに行く処理関数.
	if (FetchString(WND_W - m_OutSidePos) == true) {
		m_vPos.x -= m_OutSidePos;
		m_CarryFlag = RIGHT_TITLE_CARRY_FLAG;
	}

}

//==========================================.
//		右タイトル文章取りに行く処理関数.
//==========================================.
void CChangeSceneCursorUI::RightTitleCarry()
{
	//運び移動処理関数.
	CarryMove();

	if (m_CarryFlag == 0) {
		m_MoveType++;
		m_FetchFlag = 0;
		m_vUV = NORMAL_UV_POS;
		m_bArrivalFlga = false;
	}
}

//==========================================.
//		喜び処理関数.
//==========================================.
void CChangeSceneCursorUI::Rejoice()
{
	if (m_bArrivalFlga == false) {
		m_vJumpBeforePos = m_vPos;
		//上下移動処理関数.
		UpDownFloat();
	}

	//目的地への移動処理関数.
	if (MoveToDestination(SCREEN_CENTER_POS) == true) {
		m_vUV = ENTER_UV_POS;
		//ジャンプ処理関数.
		if (Jump() == true) {
			m_MoveType++;
			m_FetchFlag = SELECT_FEATCH_FLAG;
			m_vUV = NORMAL_UV_POS;
			m_vChangeDirectBeforeRot = m_vRot;
		}
	}

}

//==========================================.
//		選択肢を取りに行く処理関数.
//==========================================.
void CChangeSceneCursorUI::SelectFetch()
{
	//移動変更処理関数.
	if (m_bChangeDirect == false) {
		m_bChangeDirect = ChangeMoveDirect();
		return;
	}

	//文章を取りに行く処理関数.
	if (FetchString(WND_W - m_OutSidePos) == true) {
		m_FetchFlag = 0;
		m_vPos.x -= m_OutSidePos;
		m_CarryFlag = SELECT_CARRY_FLAG;
	}


}

//==========================================.
//		選択肢を運ぶ処理関数.
//==========================================.
void CChangeSceneCursorUI::SelectCarry()
{
	//運び移動処理関数.
	CarryMove();

	if (m_CarryFlag == 0) {
		m_MoveType++;
		m_FetchFlag = 0;
		m_vUV = NORMAL_UV_POS;
		m_bArrivalFlga = false;
	}
}

//==========================================.
//		カーソルになる処理関数.
//==========================================.
void CChangeSceneCursorUI::BecomeCursor()
{
	if (m_bArrivalFlga == false) {
		//上下移動処理関数.
		UpDownFloat();
		m_vChangeDirectBeforeRot = m_vRot;
	}

	//目的地への移動処理関数.
	if (MoveToDestination(CONTROL_CURSOR_POS) == true) {
		//移動方向変更処理関数.
		if (ChangeMoveDirect() == true) {
			m_bControlFlag = true;
		}
	}


}