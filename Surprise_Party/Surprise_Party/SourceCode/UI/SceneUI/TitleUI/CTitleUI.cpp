#include "CTitleUI.h"

/*************************************
*		�^�C�g��UI�N���X.
****************/
CTitleUI::CTitleUI()
	: m_SelectTypeFlag	(0)
	, m_ControlFlag		(0)
{
	//�����������֐�.
	Init();
}

CTitleUI::~CTitleUI()
{

}

//=====================================.
//		�X�V�����֐�.
//=====================================.
void CTitleUI::Update()
{
	//���͈ړ������֐�.
	MoveString();

	//���쏈���֐�.
	m_pCCursor->SetChangeWaitFlag(false);
	m_pCCursor->Update();

	//�^�C�g���X�V�����֐�.
	m_pCTitleStringUI->Update();

	//�I����UI�X�V�����֐�.
	m_pCSelectStringUI->Update();

	if (m_ControlFlag & CONTROL_WAIT_FLAG) {
		if (GetAsyncKeyState(VK_RETURN) & 0x8000) {
			m_ControlFlag = CONTROL_FLAG;
			m_pCCursor->SetControlFlag(true);

			//����t���O�ɕύX.
			m_pCTitleStringUI->SetMoveFlag(m_pCTitleStringUI->CONTROL_FLAG);
			m_pCSelectStringUI->SetMoveFlag(m_pCSelectStringUI->CONTROL_FLAG);
			
		}
		return;
	}

}

//=====================================.
//		�I����ރt���O�擾�����֐�.
//=====================================.
unsigned int CTitleUI::GetSelectTypeFlag() const 
{
	if (m_pCCursor->GetSelectFinishFlag() == false) {
		return 0;
	}

	//�Q�[���J�n.
	if (m_pCCursor->GetSelectNum() == 0) {
		return GAME_START_FLAG;
	}

	//�Q�[���I��.
	return GAME_FINISH_FLAG;
}

//=====================================.
//		�����������֐�.
//=====================================.
void CTitleUI::Init()
{
	//����ҋ@�t���O�ɐݒ�.
	m_ControlFlag = CONTROL_WAIT_FLAG;

	//�^�C�g�����̓C���X�^���X��.
	m_pCTitleStringUI.reset(new CTitleStringUI());
	//�I�����̃C���X�^���X��.
	m_pCSelectStringUI.reset(new CSelectStringUI(true));
	
}

//========================================.
//		���͈ړ������֐�.
//========================================.
void CTitleUI::MoveString()
{

	if (m_pCCursor->GetCarryFlag() == 0) {
		//���͈ړ����������֐�.
		PreparingMoveString();
		return;
	}

	//�^�C�g�������̈ړ�����.
	const unsigned int CARRY_TITLE_ALL_FLAG = m_pCCursor->LEFT_TITLE_CARRY_FLAG | m_pCCursor->RIGHT_TITLE_CARRY_FLAG;
	if (m_pCCursor->GetCarryFlag() & CARRY_TITLE_ALL_FLAG) {
		//�덷�͈͂�ݒ�(1�t���[�����Ƃ�Player�̈ړ����x���).
		m_pCTitleStringUI->SetErrorRange(m_pCCursor->MOVE_SPEED);
		//�ړ��t���O��ݒ�.
		m_pCTitleStringUI->SetMoveFlag(m_pCTitleStringUI->MOVE_FLAG);
		//�ړ�������ݒ�.
		m_pCTitleStringUI->SetMoveDistance(m_pCCursor->GetCarryDistance());

		//�ړ���~����.
		if (m_pCTitleStringUI->GetStopMoveFlag() == true) {
			m_pCTitleStringUI->SetMoveFlag(0);
			//���̕��͔ԍ���.
			m_pCTitleStringUI->SetChangeNextStringNum();
			//�^�Ԃ̏I��.
			m_pCCursor->SetFinishCarry();
		}
		return;
	}

	//�I�����̈ړ�����.
	if (m_pCCursor->GetCarryFlag() & m_pCCursor->SELECT_CARRY_FLAG) {
		//�덷�͈͂�ݒ�(1�t���[�����Ƃ�Player�̈ړ����x���).
		m_pCSelectStringUI->SetErrorRange(m_pCCursor->MOVE_SPEED);
		//�ړ��t���O��ݒ�.
		m_pCSelectStringUI->SetMoveFlag(m_pCSelectStringUI->MOVE_FLAG);
		//�ړ�������ݒ�.
		m_pCSelectStringUI->SetMoveDistance(m_pCCursor->GetCarryDistance());

		//�ړ���~����.
		if (m_pCSelectStringUI->GetMoveStopFlag() == true) {
			m_pCSelectStringUI->SetMoveFlag(0);
			m_pCCursor->SetFinishCarry();
		}
	}
}

//=========================================.
//		���͈ړ����������֐�.
//=========================================.
void CTitleUI::PreparingMoveString() 
{
	const unsigned int FetchFlag = m_pCCursor->GetFetchFlag();
	if (m_pCCursor->GetFetchFlag() == 0) {
		return;
	}
	
	D3DXVECTOR3 GhostCursorCarryPos(0.0f, 0.0f, 0.0f);
	//�^�C�g���̈ړ���������.
	const unsigned int FETCH_TITLE_ALL_FLAG = m_pCCursor->LEFT_TITLE_FETCH_FLAG | m_pCCursor->RIGHT_TITLE_FETCH_FLAG;
	if (m_pCCursor->GetFetchFlag() & FETCH_TITLE_ALL_FLAG) {
		//���ɍs���t���O.
		m_pCTitleStringUI->SetMoveFlag(m_pCTitleStringUI->FETCH_FLAG);
		//���������s���ׂ����W��ݒ�.
		GhostCursorCarryPos = m_pCTitleStringUI->GetFetchGhostPos();
		
	}

	//�I�����̈ړ���������.
	if (m_pCCursor->GetFetchFlag() & m_pCCursor->SELECT_FEATCH_FLAG) {
		//���ɍs���t���O.
		m_pCSelectStringUI->SetMoveFlag(m_pCSelectStringUI->FETCH_FLAG);
		//���������s���ׂ����W��ݒ�.
		GhostCursorCarryPos = m_pCSelectStringUI->GetGhostCursorPos();
	}

	m_pCCursor->SetCarryStartPos(GhostCursorCarryPos);
}

//=========================================.
//		�V�[���^�C�g���`�揈���֐�.
//=========================================.
void CTitleUI::RenderSceneTitle()
{
	//�^�C�g���̕`��.
	m_pCTitleStringUI->Render();
}