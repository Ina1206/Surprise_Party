#include "CStageFade.h"

/******************************************
*		�X�e�[�W�t�F�[�h�N���X.
**************/
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
	, m_bPlayCurtainSE	(false)
	, m_bPlayOpneBell	(false)
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
		m_bPlayCurtainSE = false;
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

	SPRITE_STATE ss = m_pCResourceManager->GetSpriteUIState(enSpriteUI::BlackCurtain);

	for (unsigned int ui = 0; ui < m_pCUI.size(); ui++) {
		m_fUIScale[ui]	= SCALE_MAX;
		m_vUIRot[ui]	= D3DXVECTOR3(0.0f,0.0f, 0.0f);
		m_vPrePos[ui]	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_vUIPos[ui]	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
	m_vUIRot[LEFT_CURTAIN_NUM].y	= HALF_ROT_ANGLE;

	m_vUIPos[RIHGT_CURTAIN_NUM].x	= WND_W;
	m_vUIRot[RIHGT_CURTAIN_NUM].y	= -HALF_ROT_ANGLE;

	m_vPrePos[SIGN_BOARD_NUM]		= BOARD_PRE_POS;
	m_vUIPos[SIGN_BOARD_NUM]		= SIGN_BOARD_INIT_POS;

	m_vPrePos[STRING_NUM]			= STRING_PRE_POS;
	m_vUIPos[STRING_NUM]			= SIGN_BOARD_INIT_POS;
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
	//�����ύX.
	if (m_pCUI[STRING_NUM] == m_pCResourceManager->GetSpriteUI(enSpriteUI::CloseString)) {
		m_pCUI[STRING_NUM] = m_pCResourceManager->GetSpriteUI(enSpriteUI::PreparingString);
	}

	//�ŔƃJ�[�e���̈ړ������֐�.
	if (CurtainMove() == true) {
		return;
	}

	if (m_CurtainMoveFlag & OPEN_CHANG_FLAG) {
		//�Ŕ�]�����֐�.
		if (RotationSignBoard(m_pCResourceManager->GetSpriteUI(enSpriteUI::OpenString)) == true) {
			m_CurtainMoveFlag |= SIGN_BOARD_SWING_FLAG;
		}
		return;
	}

	if (m_CurtainMoveFlag & SIGN_BOARD_SWING_FLAG) {
		//�Ŕh��鏈���֐�.
		if (SwingSignBoard() == true) {
			m_CurtainMoveFlag |= OPEN_CURTAIN_FLAG;
			m_bPlayCurtainSE = false;
		}
		return;
	}

}

//=======================================.
//		�X���̃J�[�e���ړ������֐�.
//=======================================.
void CStageFade::CloseCurtainMove()
{
	//�ŔƃJ�[�e���̈ړ������֐�.
	if (CurtainMove() == true) {
		return;
	}

	if (m_CurtainMoveFlag & OPEN_CHANG_FLAG) {
		//�Ŕ�]�����֐�.
		if (RotationSignBoard(m_pCResourceManager->GetSpriteUI(enSpriteUI::CloseString)) == true) {
			m_CurtainMoveFlag |= SIGN_BOARD_SWING_FLAG;
		}
		return;
	}

	if (m_CurtainMoveFlag & SIGN_BOARD_SWING_FLAG) {
		//�Ŕ��h��鏈���֐�.
		if (SwingSignBoard() == true) {
			m_CurtainMoveFlag |= OPEN_CURTAIN_FLAG;
			m_bPlayCurtainSE = false;
		}
		return;
	}

}

//=======================================.
//		�J�[�e���ړ������֐�(���Ŕ��ړ�).
//=======================================.
bool CStageFade::CurtainMove()
{
	int MoveDirect = CLOSE_DIRECT;
	bool MoveFlag = false;

	if (m_bPlayCurtainSE == false) {
		m_pCPlaySoundManager->SetPlaySE(enSEType::MoveCurtain);
		m_bPlayCurtainSE = true;
	}

	//�����̊���.
	if (m_CurtainMoveFlag & CLOSE_CURTAIN_FLAG) {
		m_fDistanceRatio = fabsf(m_vUIRot[LEFT_CURTAIN_NUM].y - 0.0f) / HALF_ROT_ANGLE;
		if (m_vUIRot[LEFT_CURTAIN_NUM].y <= 0.0f) {
			m_vUIRot[LEFT_CURTAIN_NUM].y = 0.0f;
			m_vUIRot[RIHGT_CURTAIN_NUM].y = CURTAIN_ROT_MIN;
		}

		if (m_vUIPos[SIGN_BOARD_NUM].y >= SIGN_BOARD_HEIGHT_MAX) {
			m_pCOldSpriteUI = m_pCUI[STRING_NUM];

			m_CurtainMoveFlag &= ~CLOSE_CURTAIN_FLAG;
			m_CurtainMoveFlag |= CHANGE_STAGE_FLAG | OPEN_CHANG_FLAG;
		}

		MoveFlag = true;
	}

	if (m_CurtainMoveFlag & OPEN_CURTAIN_FLAG) {
		MoveDirect = OPEN_DIRECT;

		m_fDistanceRatio = 1.0f - fabsf(m_vUIRot[LEFT_CURTAIN_NUM].y - HALF_ROT_ANGLE) / HALF_ROT_ANGLE;

		if (m_vUIRot[LEFT_CURTAIN_NUM].y >= HALF_ROT_ANGLE) {
			m_vUIRot[LEFT_CURTAIN_NUM].y = HALF_ROT_ANGLE;
			m_vUIRot[RIHGT_CURTAIN_NUM].y = -HALF_ROT_ANGLE;
		}

		if (m_vUIPos[SIGN_BOARD_NUM].y <= SIGN_BOARD_INIT_POS.y) {
			m_CurtainMoveFlag = 0;

			for (int sprite = SIGN_BOARD_NUM; sprite <= STRING_NUM; sprite++) {
				m_vUIRot[sprite] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			}
		}

		MoveFlag = true;
	}

	//�ړ�.
	if (MoveFlag == true) {
		for (int curtainNum = 0; curtainNum <= RIHGT_CURTAIN_NUM; curtainNum++) {
			m_vUIRot[curtainNum].y -= CURTAIN_ROT_SPEED * MoveDirect;
		}
		for (int sign_board = SIGN_BOARD_NUM; sign_board <= STRING_NUM; sign_board++) {
			m_vUIPos[sign_board].y += SIGN_BOARD_MOVE_SPEED * MoveDirect;
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

	if (m_vUIRot[SIGN_BOARD_NUM].y > HALF_ROT_ANGLE) {
		if (m_pCUI[STRING_NUM] == m_pCOldSpriteUI) {
			m_vUIRot[STRING_NUM].y *= CHANGE_DIRECT;
			m_pCUI[STRING_NUM] = ChangeStirngSpriteUI;
		}
		//�k���ɕύX����.
		ScalingType = -1;
	}

	for (int sign_board = SIGN_BOARD_NUM; sign_board <= STRING_NUM; sign_board++) {
		m_vUIRot[sign_board].y += SIGN_BOARD_ROT_SPEED;
		m_fUIScale[sign_board] += SIGN_BOARD_SCALE_SPEED * ScalingType;
	}

	if (m_vUIRot[SIGN_BOARD_NUM].y > -CURTAIN_ROT_MIN) {
		m_CurtainMoveFlag &= ~OPEN_CHANG_FLAG;

		m_enSwingSignBoard = enSwingSignBoard::LeftSwing;

		m_pCPlaySoundManager->SetPlaySE(enSEType::OpenBell);

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
			m_SwingRotDirect *= CHANGE_DIRECT;
			m_enSwingSignBoard = enSwingSignBoard::RightSwing;
		}
		break;
	case enSwingSignBoard::RightSwing:
		if (m_vUIRot[SIGN_BOARD_NUM].z <= m_SwingRotMax * m_SwingRotDirect) {
			m_SwingRotDirect *= CHANGE_DIRECT;
			m_SwingRotMax -= SWING_ROT_MAX_SPEED;
			m_fSwingSpeed -= SWING_SPEED;
			m_enSwingSignBoard = enSwingSignBoard::LeftSwing;
		}
		break;
	}

	if (m_SwingRotMax <= SWING_ROT_LIMIT_MIN && fabsf(m_vUIRot[SIGN_BOARD_NUM].z) <= SWING_ROT_MIN) {
		m_CurtainMoveFlag &= ~SIGN_BOARD_SWING_FLAG;

		m_SwingRotDirect = 1;
		m_fSwingSpeed = SWING_SPEED_MAX;
		m_SwingRotMax = SWING_ROT_MAX;
		return true;
	}
	return false;
}