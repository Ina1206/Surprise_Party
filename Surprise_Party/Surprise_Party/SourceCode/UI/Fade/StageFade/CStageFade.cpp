#include "CStageFade.h"

CStageFade::CStageFade()
	: m_pCUI			()
	, m_vUIPos			()
	, m_fUIScale		()
	, m_vUIRot			()
	, m_vPrePos			()
	, m_CurtainMoveFlag	(0)
	, m_enSwingSignBoard()
	, m_SwingRotDirect	(1)
	, m_SwingRotMax		(0.6f)
	, m_fSwingSpeed		(0.04f)
	, m_fDistanceRatio	(1.0f)
{
	//初期化処理関数.
	Init();
}

CStageFade::~CStageFade()
{
	//解放処理関数.
	Release();
}

//=======================================.
//		更新処理関数.
//=======================================.
void CStageFade::Update()
{
	if (m_CurtainMoveFlag == 0) {
		return;
	}

	if (m_CurtainMoveFlag & OPENING_FLAG) {
		//開店時のカーテン移動処理関数.
		OpeningCurtainMove();
		return;
	}

	//閉店時のカーテン移動処理関数.
	CloseCurtainMove();
}

//=======================================.
//		描画処理関数.
//=======================================.
void CStageFade::Render()
{
	for (unsigned int SpriteUI = 0; SpriteUI < m_pCUI.size(); SpriteUI++) {
		//準備角度.
		m_pCUI[SpriteUI]->SetPrePos(m_vPrePos[SpriteUI]);
		//角度.
		m_pCUI[SpriteUI]->SetRotation(m_vUIRot[SpriteUI]);
		//大きさ.
		m_pCUI[SpriteUI]->SetScale(m_fUIScale[SpriteUI]);
		//座標.
		m_pCUI[SpriteUI]->SetPosition(m_vUIPos[SpriteUI]);
		//描画処理関数.
		m_pCDepthStencil->SetDepth(false);
		m_pCUI[SpriteUI]->Render();
		m_pCDepthStencil->SetDepth(true);
	}

	
}

//=======================================.
//		初期化処理関数.
//=======================================.
void CStageFade::Init()
{
	m_pCUI.resize(UI_MAX);
	m_vUIPos.resize(m_pCUI.size());
	m_fUIScale.resize(m_pCUI.size());
	m_vUIRot.resize(m_pCUI.size());
	m_vPrePos.resize(m_pCUI.size());

	for (int curtainNum = 0; curtainNum <= RIHGT_CURTAIN_NUM; curtainNum++) {
		m_pCUI[curtainNum] = m_pCResourceManager->GetSpriteUI(enSpriteUI::BlackCurtain);
	}
	m_pCUI[SIGN_BOARD_NUM] = m_pCResourceManager->GetSpriteUI(enSpriteUI::SignBoard);
	m_pCUI[STRING_NUM] = m_pCResourceManager->GetSpriteUI(enSpriteUI::PreparingString);

	for (unsigned int ui = 0; ui < m_pCUI.size(); ui++) {
		m_fUIScale[ui] = 1.0f;
		m_vUIRot[ui] = D3DXVECTOR3(0.0f,0.0f, 0.0f);
		m_vPrePos[ui] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
	m_vUIPos[LEFT_CURTAIN_NUM] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vUIRot[LEFT_CURTAIN_NUM] = D3DXVECTOR3(0.0f, 1.6f, 0.0f);

	m_vUIPos[RIHGT_CURTAIN_NUM] = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
	m_vUIRot[RIHGT_CURTAIN_NUM] = D3DXVECTOR3(0.0f, -1.5f, 0.0f);

	m_vPrePos[SIGN_BOARD_NUM] = D3DXVECTOR3(-320.0f, -10.0f, 0.0f);
	m_vUIPos[SIGN_BOARD_NUM] = D3DXVECTOR3(650.0, -500.0f, 0.0f);

	m_vPrePos[STRING_NUM] = D3DXVECTOR3(-150.0f, 300.0f, 0.0f);
	m_vUIPos[STRING_NUM] = D3DXVECTOR3(650.0, -500.0f, 0.0f);
}

//=======================================.
//		解放処理関数.
//=======================================.
void CStageFade::Release()
{

}

//=======================================.
//		開店時のカーテン移動処理関数.
//=======================================.
void CStageFade::OpeningCurtainMove()
{
	if (m_pCUI[STRING_NUM] == m_pCResourceManager->GetSpriteUI(enSpriteUI::CloseString)) {
		m_pCUI[STRING_NUM] = m_pCResourceManager->GetSpriteUI(enSpriteUI::PreparingString);
	}

	if (CurtainMove() == true) {
		return;
	}

	if (m_CurtainMoveFlag & OPEN_CHANG_FLAG) {
		if (RotationSignBoard(m_pCResourceManager->GetSpriteUI(enSpriteUI::OpenString)) == true) {
			m_CurtainMoveFlag |= SIGN_BOARD_SWING_FLAG;
		}
		return;
	}

	if (m_CurtainMoveFlag & SIGN_BOARD_SWING_FLAG) {
		if (SwingSignBoard() == true) {
			m_CurtainMoveFlag |= OPEN_CURTAIN_FLAG;
		}
		return;
	}

}

//=======================================.
//		閉店時のカーテン移動処理関数.
//=======================================.
void CStageFade::CloseCurtainMove()
{
	if (CurtainMove() == true) {
		return;
	}

	if (m_CurtainMoveFlag & OPEN_CHANG_FLAG) {
		if (RotationSignBoard(m_pCResourceManager->GetSpriteUI(enSpriteUI::CloseString)) == true) {
			m_CurtainMoveFlag |= SIGN_BOARD_SWING_FLAG;
		}
		return;
	}

	if (m_CurtainMoveFlag & SIGN_BOARD_SWING_FLAG) {
		if (SwingSignBoard() == true) {
			m_CurtainMoveFlag |= OPEN_CURTAIN_FLAG;
		}
		return;
	}

}

//=======================================.
//		カーテン移動処理関数(※看板も移動).
//=======================================.
bool CStageFade::CurtainMove()
{
	int MoveDirect = 1;
	bool MoveFlag = false;

	//距離の割合.
	if (m_CurtainMoveFlag & CLOSE_CURTAIN_FLAG) {
		m_fDistanceRatio = fabsf(m_vUIRot[LEFT_CURTAIN_NUM].y - 0.0f) / 1.6f;
		if (m_vUIRot[LEFT_CURTAIN_NUM].y <= 0.0f) {
			m_vUIRot[LEFT_CURTAIN_NUM].y = 0.0f;
			m_vUIRot[RIHGT_CURTAIN_NUM].y = -3.1f;
		}

		if (m_vUIPos[SIGN_BOARD_NUM].y >= 80.0f) {
			m_pCOldSpriteUI = m_pCUI[STRING_NUM];

			m_CurtainMoveFlag &= ~CLOSE_CURTAIN_FLAG;
			m_CurtainMoveFlag |= CHANGE_STAGE_FLAG | OPEN_CHANG_FLAG;
		}

		MoveFlag = true;
	}

	if (m_CurtainMoveFlag & OPEN_CURTAIN_FLAG) {
		MoveDirect = -1;

		m_fDistanceRatio = 1.0f - fabsf(m_vUIRot[LEFT_CURTAIN_NUM].y - 1.6f) / 1.6f;

		if (m_vUIRot[LEFT_CURTAIN_NUM].y >= 1.6f) {
			m_vUIRot[LEFT_CURTAIN_NUM].y = 1.6f;
			m_vUIRot[RIHGT_CURTAIN_NUM].y = -1.6f;
		}

		if (m_vUIPos[SIGN_BOARD_NUM].y <= -500.0f) {
			m_CurtainMoveFlag = 0;

			for (int sprite = SIGN_BOARD_NUM; sprite <= STRING_NUM; sprite++) {
				m_vUIRot[sprite] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			}
		}

		MoveFlag = true;
	}

	if (MoveFlag == true) {
		for (int curtainNum = 0; curtainNum <= RIHGT_CURTAIN_NUM; curtainNum++) {
			m_vUIRot[curtainNum].y -= 0.03f * MoveDirect;
		}
		for (int sign_board = SIGN_BOARD_NUM; sign_board <= STRING_NUM; sign_board++) {
			m_vUIPos[sign_board].y += 6.0f * MoveDirect;
		}
		return true;
	}

	return false;
}

//=======================================.
//		看板回転処理関数.
//=======================================.
bool CStageFade::RotationSignBoard(CSpriteUI*	ChangeStirngSpriteUI)
{
	m_CurtainMoveFlag &= ~CHANGE_STAGE_FLAG;

	int ScalingType = 1;	//拡縮の種類(1:拡大, -1:縮小).

	if (m_vUIRot[SIGN_BOARD_NUM].y > 1.6f) {
		if (m_pCUI[STRING_NUM] == m_pCOldSpriteUI) {
			m_vUIRot[STRING_NUM].y *= -1.0f;
			m_pCUI[STRING_NUM] = ChangeStirngSpriteUI;
		}
		//縮小に変更処理.
		ScalingType = -1;
	}

	for (int sign_board = SIGN_BOARD_NUM; sign_board <= STRING_NUM; sign_board++) {
		m_vUIRot[sign_board].y += 0.1f;
		m_fUIScale[sign_board] += 0.02f * ScalingType;
	}

	if (m_vUIRot[SIGN_BOARD_NUM].y > 3.1f) {
		m_CurtainMoveFlag &= ~OPEN_CHANG_FLAG;

		m_enSwingSignBoard = enSwingSignBoard::LeftSwing;

		return true;
	}
	return false;
}

//=======================================.
//		看板揺れる処理関数.
//=======================================.
bool CStageFade::SwingSignBoard()
{
	for (int signboard = SIGN_BOARD_NUM; signboard <= STRING_NUM; signboard++) {
		m_vUIRot[signboard].z += m_fSwingSpeed * m_SwingRotDirect;
	}

	switch (m_enSwingSignBoard) {
	case enSwingSignBoard::LeftSwing:
		if (m_vUIRot[SIGN_BOARD_NUM].z >= m_SwingRotMax * m_SwingRotDirect) {
			m_SwingRotDirect *= -1;
			m_enSwingSignBoard = enSwingSignBoard::RightSwing;
		}
		break;
	case enSwingSignBoard::RightSwing:
		if (m_vUIRot[SIGN_BOARD_NUM].z <= m_SwingRotMax * m_SwingRotDirect) {
			m_SwingRotDirect *= -1;
			m_SwingRotMax -= 0.3f;
			m_fSwingSpeed -= 0.01f;
			m_enSwingSignBoard = enSwingSignBoard::LeftSwing;
		}
		break;
	}

	if (m_SwingRotMax <= 0.1f && fabsf(m_vUIRot[SIGN_BOARD_NUM].z) <= 0.05f) {
		m_CurtainMoveFlag &= ~SIGN_BOARD_SWING_FLAG;

		m_SwingRotDirect = 1;
		m_fSwingSpeed = 0.04f;
		m_SwingRotMax = 0.6f;
		return true;
	}
	return false;
}