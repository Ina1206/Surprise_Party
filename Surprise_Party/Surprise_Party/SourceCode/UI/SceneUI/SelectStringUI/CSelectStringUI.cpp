#include "CSelectStringUI.h"

/***************************************
*		�I����UI�N���X.
********************/
CSelectStringUI::CSelectStringUI()
	: CSelectStringUI(false)
{

}

CSelectStringUI::CSelectStringUI(const bool& bStartFlag)
	: m_pCSpriteUI		()
	, m_vStringPos		()
	, m_vBeforeMovePos	()
	, m_vLastPos		()
	, m_vGhostCursorPos	(0.0f, 0.0f, 0.0f)
	, m_bStartFlag		(bStartFlag)
	, m_bMoveStopFlag	(false)
	, m_MoveFlag		(0)
{
	//�����������֐�.
	Init();
}

CSelectStringUI::~CSelectStringUI()
{
	//��������֐�.
	Release();
}

//======================================.
//		�X�V�����֐�.
//======================================.
void CSelectStringUI::Update()
{
	if (m_MoveFlag & CONTROL_FLAG) {
		//���쎞�̍��W�ݒ菈���֐�.
		ControlPos();
		return;
	}

	if (m_MoveFlag & MOVE_FLAG) {
		//�ړ������֐�.
		Move();
		return;
	}

	if (m_MoveFlag & FETCH_FLAG) {
		//���ɍs�������֐�.
		Fetch();
	}

}

//======================================.
//		�`�揈���֐�.
//======================================.
void CSelectStringUI::Render()
{
	for (int select = 0; select < SELECT_STRING_MAX; select++) {
		m_pCSpriteUI[select]->SetPosition(m_vStringPos[select]);
		m_pCDepthStencil->SetDepth(false);
		m_pCSpriteUI[select]->Render();
		m_pCDepthStencil->SetDepth(true);
	}
}

//======================================.
//		�����������֐�.
//======================================.
void CSelectStringUI::Init()
{
	SPRITE_STATE SpriteState = m_pCResourceManager->GetSpriteUIState(enSpriteUI::StartString);

	//�J�n�e�N�X�`���ԍ�.
	int StartString = static_cast<int>(enSpriteUI::StartString);
	if (m_bStartFlag == false) {
		StartString = static_cast<int>(enSpriteUI::Continue);
	}

	for (int select = 0; select < SELECT_STRING_MAX; select++) {
		//�e�N�X�`��.
		const enSpriteUI m_enSpriteUI = static_cast<enSpriteUI>(StartString + select);
		m_pCSpriteUI.emplace_back(m_pCResourceManager->GetSpriteUI(m_enSpriteUI));

		m_vStringPos.push_back(SELECT_STRING_POS);
		//���݂̗v�f��.
		const int Num = m_vStringPos.size() - 1;
		m_vStringPos[Num].y += SpriteState.Disp.h * Num;

		//�ŏI���W�̐ݒ�.
		m_vLastPos.push_back(m_vStringPos[Num]);

		//��ʊO�ɐݒ�.
		m_vStringPos[Num].x = WND_W;
		//�ړ��O�̍��W�ݒ�.
		m_vBeforeMovePos.push_back(m_vStringPos[Num]);

	}

	m_bStartFlag = false;
}

//======================================.
//		��������֐�.
//======================================.
void CSelectStringUI::Release()
{

}

//======================================.
//		���ɍs�������֐�.
//======================================.
void CSelectStringUI::Fetch()
{
	m_vGhostCursorPos = m_vStringPos[m_pCSpriteUI.size() - 1];
	const SPRITE_STATE SpriteState = m_pCResourceManager->GetSpriteUIState(enSpriteUI::StartString);
	m_vGhostCursorPos.x += SpriteState.Disp.w;
	m_vGhostCursorPos.y -= SpriteState.Disp.h / 2.0f;
}

//======================================.
//		�ړ������֐�.
//======================================.
void CSelectStringUI::Move()
{
	for (int select = 0; select < SELECT_STRING_MAX; select++) {
		m_vStringPos[select].x = m_vBeforeMovePos[select].x + m_fMoveDistance;

		if (fabsf(m_vStringPos[select].x - m_vLastPos[select].x) <= m_fErrorRange) {
			m_vStringPos[select].x = m_vLastPos[select].x;
			m_bMoveStopFlag = true;
		}
	}
}

//======================================.
//		���쎞�̍��W�����֐�.
//======================================.
void CSelectStringUI::ControlPos()
{
	for (int select = 0; select < SELECT_STRING_MAX; select++) {
		m_vStringPos[select] = m_vLastPos[select];
	}
}