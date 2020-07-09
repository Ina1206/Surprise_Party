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

	if (m_ControlFlag & CONTROL_WAIT_FLAG) {
		if (GetAsyncKeyState(VK_RETURN) & 0x8000) {
			//���쎞�^�C�g�����W�ݒ菈���֐�.
			ControlTitlePos();

			//���쎞�I�𕶏͍��W�ݒ菈���֐�.
			ControlSelectStringPos();

			m_ControlFlag = CONTROL_FLAG;
			
			m_pCCursor->SetControlFlag(true);
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

	//�^�C�g��.
	for (int title = 0; title < TITLE_MAX; title++) {
		m_pCSpriteUI.emplace_back(m_pCResourceManager->GetSpriteUI(enSpriteUI::Title));
	}

	m_vBeforeMovePos.resize(m_pCSpriteUI.size());

	//�v�f�������������֐�.
	InitElementCounts();

	//�I�������������֐�.
	InitSelect();

	//���쎞�^�C�g�����W�ݒ菈���֐�.
	ControlTitlePos();

	//�^�C�g�����������֐�.
	InitTitle();

	//����ҋ@�t���O�ɐݒ�.
	m_ControlFlag = CONTROL_WAIT_FLAG;
}

//=======================================.
//		�^�C�g�������������֐�.
//=======================================.
void CTitleUI::InitTitle()
{
	//�^�C�g���ԍ��J�n�ԍ�.
	const int TitleStartNum = SELECT_STRING_MAX;

	for (int title = 0; title < TITLE_MAX; title++) {
		const int TitleNum = title + TitleStartNum;

		D3DXVECTOR2 TitleUV = INIT_UV;
		TitleUV.y += 1.0f * title;
		m_vUV[TitleNum] = TitleUV;

		m_vUIPos[TitleNum] = TITLE_POS;
		m_vUIPos[TitleNum].x = WND_W;
		
		if (title == 0) {
			SPRITE_STATE ss = m_pCResourceManager->GetSpriteUIState(enSpriteUI::Title);
			m_vUIPos[TitleNum].x = -ss.Stride.w;
		}

		m_vBeforeMovePos[TitleNum] = m_vUIPos[TitleNum];
	}
}

//=======================================.
//		���쎞�^�C�g�����W�ݒ菈���֐�.
//=======================================.
void CTitleUI::ControlTitlePos()
{
	//�^�C�g���ԍ�.
	const int TitleStartNum = SELECT_STRING_MAX;
	
	if (m_ControlFlag == 0) {

		//�^�C�g���̍ŏI���W��ݒ�.
		for (int title = 0; title < TITLE_MAX; title++) {
			SPRITE_STATE ss = m_pCResourceManager->GetSpriteUIState(enSpriteUI::Title);
			m_vTitleLastPos.push_back(TITLE_POS);
			m_vTitleLastPos[title].x += (ss.Stride.w ) * title;
		}

		return;
	}

	//�^�C�g���̈ʒu�ɐݒ�.
	for (int title = 0; title < TITLE_MAX; title++) {
		const int TitleNum = title + TitleStartNum;
		m_vUIPos[TitleNum] = m_vTitleLastPos[title];
	}

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

	int MoveStringNum = 0;
	if (m_pCCursor->GetCarryFlag() & m_pCCursor->LEFT_TITLE_CARRY_FLAG) {
		MoveStringNum = 2;
		m_vUIPos[MoveStringNum].x = m_vBeforeMovePos[MoveStringNum].x + m_pCCursor->GetCarryDistance();
	}
	else if(m_pCCursor->GetCarryFlag() & m_pCCursor->RIGHT_TITLE_CARRY_FLAG){
		MoveStringNum = 3;
		m_vUIPos[MoveStringNum].x = m_vBeforeMovePos[MoveStringNum].x + m_pCCursor->GetCarryDistance();
	}
	else{
		for (int string = MoveStringNum; string < SELECT_STRING_MAX; string++) {
			m_vUIPos[string].x = m_vBeforeMovePos[string].x + m_pCCursor->GetCarryDistance();
		}
	}

	if (MoveStringNum == 0)
	{
		if (m_vUIPos[MoveStringNum].x < SELECT_STRING_POS.x) {
			for (int string = MoveStringNum; string < SELECT_STRING_MAX; string++) {
				m_vUIPos[MoveStringNum].x = SELECT_STRING_POS.x;
				m_pCCursor->SetFinishCarry();
			}
		}
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
		FetchStringNum = 2;
		GhostCursorCarryPos = m_vUIPos[FetchStringNum];
	}
	else if(FetchFlag & m_pCCursor->RIGHT_TITLE_CARRY_FLAG){
		FetchStringNum = 3;
		GhostCursorCarryPos = m_vUIPos[FetchStringNum];
		//�ǉ����W.
		const float Add_Pos = (m_pCResourceManager->GetSpriteUIState(enSpriteUI::Title).Disp.w / 3) * 2;
		GhostCursorCarryPos.x += Add_Pos;
	}
	else {
		GhostCursorCarryPos = m_vUIPos[FetchStringNum];
		SPRITE_STATE SpriteState = m_pCResourceManager->GetSpriteUIState(enSpriteUI::FinishString);
		GhostCursorCarryPos.y += SpriteState.Disp.h / 2.0f;
		GhostCursorCarryPos.x += SpriteState.Disp.w;
		
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