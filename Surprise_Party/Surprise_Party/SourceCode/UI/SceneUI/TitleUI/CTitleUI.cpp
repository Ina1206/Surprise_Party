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

	if (m_ControlFlag & CONTROL_WAIT_FLAG) {
		if (GetAsyncKeyState(VK_RETURN) & 0x8000) {
			//���쎞�I�𕶏͍��W�ݒ菈���֐�.
			ControlSelectStringPos();

			m_ControlFlag = CONTROL_FLAG;
			
			m_pCCursor->SetControlFlag(true);

			//����t���O�ɕύX.
			m_pCTitleStringUI->SetMoveFlag(m_pCTitleStringUI->CONTROL_FLAG);
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
	//�I����.
	for (int spriteNum = 0; spriteNum < SELECT_STRING_MAX; spriteNum++) {
		const int StartString = static_cast<int>(enSpriteUI::StartString);
		const enSpriteUI m_enSpriteUI = static_cast<enSpriteUI>(StartString + spriteNum);

		m_pCSpriteUI.emplace_back(m_pCResourceManager->GetSpriteUI(m_enSpriteUI));
	}

	m_vBeforeMovePos.resize(m_pCSpriteUI.size());

	//�v�f�������������֐�.
	InitElementCounts();

	//�I�������������֐�.
	InitSelect();

	//����ҋ@�t���O�ɐݒ�.
	m_ControlFlag = CONTROL_WAIT_FLAG;

	//�^�C�g�����̓C���X�^���X��.
	m_pCTitleStringUI.reset(new CTitleStringUI());
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
	}

	int MoveStringNum = 0;
	if (m_pCCursor->GetCarryFlag() & m_pCCursor->LEFT_TITLE_CARRY_FLAG) {
	}
	else if(m_pCCursor->GetCarryFlag() & m_pCCursor->RIGHT_TITLE_CARRY_FLAG){
	}
	else{
		for (int string = MoveStringNum; string < SELECT_STRING_MAX; string++) {
			m_vUIPos[string].x = m_vBeforeMovePos[string].x + m_pCCursor->GetCarryDistance();
		}
	}

	if (MoveStringNum == 0)
	{
	}
	else {
		if (fabsf(m_vUIPos[MoveStringNum].x - m_vTitleLastPos[MoveStringNum - SELECT_STRING_MAX].x) < 1.0f) {
			m_vUIPos[MoveStringNum] = m_vTitleLastPos[MoveStringNum - SELECT_STRING_MAX];
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
	int FetchStringNum = 0;
	if (FetchFlag & m_pCCursor->LEFT_TITLE_FETCH_FLAG) {
	}
	else if(FetchFlag & m_pCCursor->RIGHT_TITLE_CARRY_FLAG){
	}
	else {
		GhostCursorCarryPos = m_vUIPos[FetchStringNum];
		SPRITE_STATE SpriteState = m_pCResourceManager->GetSpriteUIState(enSpriteUI::FinishString);
		GhostCursorCarryPos.y += SpriteState.Disp.h / 2.0f;
		GhostCursorCarryPos.x += SpriteState.Disp.w;
		
	}

	//�^�C�g���̈ړ���������.
	const unsigned int FETCH_TITLE_ALL_FLAG = m_pCCursor->LEFT_TITLE_FETCH_FLAG | m_pCCursor->RIGHT_TITLE_FETCH_FLAG;
	if (m_pCCursor->GetFetchFlag() & FETCH_TITLE_ALL_FLAG) {
		//���ɍs���t���O.
		m_pCTitleStringUI->SetMoveFlag(m_pCTitleStringUI->FETCH_FLAG);
		//���������s���ׂ����W��ݒ�.
		GhostCursorCarryPos = m_pCTitleStringUI->GetFetchGhostPos();
	}

	m_pCCursor->SetCarryStartPos(GhostCursorCarryPos);
}

//==========================================.
//		�I�������������֐�.
//==========================================.
void CTitleUI::InitSelect()
{
	SPRITE_STATE SpriteState = m_pCResourceManager->GetSpriteUIState(enSpriteUI::StartString);
	for (int select = 0; select < SELECT_STRING_MAX; select++) {
		m_vUIPos[select] = SELECT_STRING_POS;
		m_vUIPos[select].x = WND_W;
		m_vUIPos[select].y += select * SpriteState.Disp.h;
		m_vBeforeMovePos[select] = m_vUIPos[select];
	}
}

//=========================================.
//		���̕��`�揈���֐�.
//=========================================.
void CTitleUI::RenderOther()
{
	//�^�C�g���̕`��.
	m_pCTitleStringUI->Render();
}