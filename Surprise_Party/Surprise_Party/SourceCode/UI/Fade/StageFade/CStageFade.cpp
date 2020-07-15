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
	//�����������֐�.
	Init();
}

CStageFade::~CStageFade()
{
	//��������֐�.
	Release();
}

//=======================================.
//		�X�V�����֐�.
//=======================================.
void CStageFade::Update()
{
	if (m_CurtainMoveFlag == 0) {
		return;
	}

	if (m_CurtainMoveFlag & OPENING_FLAG) {
		//�J�X���̃J�[�e���ړ������֐�.
		OpeningCurtainMove();
		return;
	}

	//�X���̃J�[�e���ړ������֐�.
	CloseCurtainMove();
}

//=======================================.
//		�`�揈���֐�.
//=======================================.
void CStageFade::Render()
{
	for (unsigned int SpriteUI = 0; SpriteUI < m_pCUI.size(); SpriteUI++) {
		//�����p�x.
		m_pCUI[SpriteUI]->SetPrePos(m_vPrePos[SpriteUI]);
		//�p�x.
		m_pCUI[SpriteUI]->SetRotation(m_vUIRot[SpriteUI]);
		//�傫��.
		m_pCUI[SpriteUI]->SetScale(m_fUIScale[SpriteUI]);
		//���W.
		m_pCUI[SpriteUI]->SetPosition(m_vUIPos[SpriteUI]);
		//�`�揈���֐�.
		m_pCDepthStencil->SetDepth(false);
		m_pCUI[SpriteUI]->Render();
		m_pCDepthStencil->SetDepth(true);
	}

	
}

//=======================================.
//		�����������֐�.
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
//		��������֐�.
//=======================================.
void CStageFade::Release()
{

}

//=======================================.
//		�J�X���̃J�[�e���ړ������֐�.
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
//		�X���̃J�[�e���ړ������֐�.
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
//		�J�[�e���ړ������֐�(���Ŕ��ړ�).
//=======================================.
bool CStageFade::CurtainMove()
{
	int MoveDirect = 1;
	bool MoveFlag = false;

	//�����̊���.
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
//		�Ŕ�]�����֐�.
//=======================================.
bool CStageFade::RotationSignBoard(CSpriteUI*	ChangeStirngSpriteUI)
{
	m_CurtainMoveFlag &= ~CHANGE_STAGE_FLAG;

	int ScalingType = 1;	//�g�k�̎��(1:�g��, -1:�k��).

	if (m_vUIRot[SIGN_BOARD_NUM].y > 1.6f) {
		if (m_pCUI[STRING_NUM] == m_pCOldSpriteUI) {
			m_vUIRot[STRING_NUM].y *= -1.0f;
			m_pCUI[STRING_NUM] = ChangeStirngSpriteUI;
		}
		//�k���ɕύX����.
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
//		�Ŕh��鏈���֐�.
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