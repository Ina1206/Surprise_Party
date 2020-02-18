#include "CAct_Selection.h"

CAct_Selection::CAct_Selection()
	: m_pCSprite		()
	, m_vSpritePos		()
	, m_vSpriteRot		()
	, m_fSpriteAlpha	()
	, m_fSpriteScale	()
	, m_fMoveDistance	()
	, m_Direction		()
	, m_bSelectFlag		(false)
	, m_MoveFlag		(0)
	, m_SelectNum		(0)
	, m_GhostActFlag	(0)
{
	//初期化処理関数.
	Init();
}

CAct_Selection::~CAct_Selection()
{
	//解放処理関数.
	Release();
}

//========================================.
//			更新処理関数.
//========================================.
void CAct_Selection::UpDate()
{
	//操作処理関数.
	Control();

	if (m_bSelectFlag == false) {
		//動く前の処理関数.
		BeforeMove();
		m_bSelectFlag = true;
		m_MoveFlag = OPEN_MOVE;
		m_GhostActFlag = 0;
	}

	if (m_MoveFlag & OPEN_MOVE) {
		//開く移動処理関数.
		OpenMove();
	}

	if (m_MoveFlag & CLOSE_MOVE) {
		//閉じる移動処理関数.
		CloseMove();
	}


	//大きさと透過値.
	for (unsigned int sprite = 0; sprite < m_pCSprite.size(); sprite++) {
		//選択中.
		if (sprite % 2 == m_SelectNum) {
			m_fSpriteAlpha[sprite] = SELECT_ALPHA;
			m_fSpriteScale[sprite] = SELECT_SCALE;
			continue;
		}
		//通常時.
		m_fSpriteAlpha[sprite] = NORMAL_ALPHA;
		m_fSpriteScale[sprite] = NORMAL_SCALE;
	}	
}

//========================================.
//			描画処理関数.
//========================================.
void CAct_Selection::Render()
{
	for (unsigned int choice = 0; choice < m_pCSprite.size(); choice++) {
		//透過値.
		m_pCSprite[choice]->SetAlpha(m_fSpriteAlpha[choice]);
		//大きさ.
		m_pCSprite[choice]->SetScale(D3DXVECTOR3( m_fSpriteScale[choice], m_fSpriteScale[choice], m_fSpriteScale[choice]));
		//角度.
		m_pCSprite[choice]->SetRotation(m_vSpriteRot[choice]);
		//座標.
		m_pCSprite[choice]->SetPosition(m_vSpritePos[choice]);
		//描画.
		m_pCDepthStencil->SetDepth(false);
		m_pCSprite[choice]->Render(m_mView, m_mProj, m_vCameraPos);
		m_pCDepthStencil->SetDepth(true);
	}
}

//========================================.
//			初期化処理関数.
//========================================.
void CAct_Selection::Init()
{
	m_pCSprite.resize(CHOICE_MAX * 2);
	m_vSpritePos.resize(m_pCSprite.size());
	m_vSpriteRot.resize(m_pCSprite.size());
	m_fSpriteAlpha.resize(m_pCSprite.size());
	m_fSpriteScale.resize(m_pCSprite.size());
	m_fMoveDistance.resize(m_pCSprite.size());
	m_Direction.resize(m_pCSprite.size());

	for (unsigned int choice = 0; choice < m_pCSprite.size(); choice++) {
		m_pCSprite[choice]		= m_pCResourceManager->GetSprite(enSprite::ActSelection);
		m_vSpritePos[choice]	= m_vPos;
		m_vSpriteRot[choice]	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_fSpriteAlpha[choice]	= 1.0f;
		m_fSpriteScale[choice]	= 1.0f;

		//偶数、奇数で動く方向を変える.
		if (choice % 2 == 0) {
			m_Direction[choice] = LEFT_DIRECTION;
			continue;
		}
		m_Direction[choice] = RIGHT_DIRECTION;
	}

	//m_pCSprite[0]->SetPatternNo(D3DXVECTOR2(2, 1));
	//m_pCSprite[1]->SetPatternNo(D3DXVECTOR2(2, 1));

	m_pCSprite[2] = m_pCResourceManager->GetSprite(enSprite::ActMoveString);
	m_pCSprite[3] = m_pCResourceManager->GetSprite(enSprite::ActRestString);
}

//========================================.
//			解放処理関数.
//========================================.
void CAct_Selection::Release()
{
	for (int choice = static_cast<int>(m_pCSprite.size()) - 1; choice >= 0; choice--) {
		m_pCSprite[choice] = nullptr;
	}
}

//========================================.
//			動く前の処理関数.
//========================================.
void CAct_Selection::BeforeMove()
{
	m_vPos = m_vCharacterPos;
	m_vPos.y += 2.0f;
	m_vPos.z -= 5.0f;

	m_GhostActFlag = 0;

	for (unsigned int pos = 0; pos < m_vSpritePos.size(); pos++) {
		m_vSpritePos[pos] = m_vPos;
	}
}

//========================================.
//			移動処理関数.
//========================================.
void CAct_Selection::OpenMove()
{
	for (unsigned int pos = 0; pos < m_vSpritePos.size(); pos++) {
		//移動距離計算.
		m_fMoveDistance[pos] += MOVE_SPEED;
		if (m_fMoveDistance[pos] >= M0VE_DISTANCE_MAX) {
			m_fMoveDistance[pos] = M0VE_DISTANCE_MAX;
			continue;
		}

		//座標計算.
		m_vSpritePos[pos].x = m_vPos.x + (m_fMoveDistance[pos] * m_Direction[pos]);
		//角度計算.
		m_vSpriteRot[pos].z -= ROTATION_SPEED * m_Direction[pos];
	}

}

//========================================.
//			閉じる移動処理関数.
//========================================.
void CAct_Selection::CloseMove()
{
	for (unsigned int pos = 0; pos < m_vSpritePos.size(); pos++) {
		//移動距離計算.
		m_fMoveDistance[pos] -= MOVE_SPEED;
		if (m_fMoveDistance[pos] <= MOVE_DISTANCE_MIN) {
			m_fMoveDistance[pos] = MOVE_DISTANCE_MIN;
			m_bSelectFlag = false;
			//m_GhostActFlag = false;

			continue;
		}

		//座標計算.
		m_vSpritePos[pos].x = m_vPos.x + (m_fMoveDistance[pos] * m_Direction[pos]);
		//角度計算.
		m_vSpriteRot[pos].z += ROTATION_SPEED * m_Direction[pos];
	}
}

//=======================================.
//		操作処理関数.
//=======================================.
void CAct_Selection::Control()
{
	if (GetAsyncKeyState(VK_BACK) & 0x0001) {
		m_MoveFlag = CLOSE_MOVE;
	}

	if (GetAsyncKeyState(VK_RIGHT) & 0x0001) {
		m_SelectNum++;
		if (m_SelectNum >= static_cast<int>(enGhostActType::Max)) {
			m_SelectNum = static_cast<int>(enGhostActType::Max) - 1;
		}
	}

	if (GetAsyncKeyState(VK_LEFT) & 0x0001) {
		m_SelectNum--;
		if (m_SelectNum < static_cast<int>(enGhostActType::Start)) {
			m_SelectNum = static_cast<int>(enGhostActType::Start);
		}
	}

	if (GetAsyncKeyState(VK_RETURN) & 0x0001) {
		//選択肢閉じる.
		m_MoveFlag = CLOSE_MOVE;

		if (m_SelectNum == static_cast<int>(enGhostActType::Move)) {
			m_GhostActFlag = MOVE_FLAG;
			return;
		}

		m_GhostActFlag = REST_FLAG;
	}
}