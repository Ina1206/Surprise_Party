#include "CTitleStringUI.h"

/*********************************************
*		�^�C�g������UI�N���X.
*******************/
CTitleStringUI::CTitleStringUI()
	: m_pCSpriteUI			()
	, m_vTitlePos			()
	, m_vTitleUV			()
	, m_vBeforeMovePos		()
	, m_vLastPos			()
	, m_vFetchGhostPos		(0.0f, 0.0f, 0.0f)
	, m_FetchStringNum		(0)
	, m_fMoveDistance		(0.0f)
	, m_bStopFlag			()
	, m_fErrorRange			(0.0f)
	, m_MoveFlag			(0)
{
	//�����������֐�.
	Init();
}

CTitleStringUI::~CTitleStringUI()
{
	//��������֐�.
	Release();
}

//=========================================.
//		�X�V�����֐�.
//=========================================.
void CTitleStringUI::Update()
{
	if (m_MoveFlag & CONTROL_FLAG) {
		//���쎞�̍��W�ݒ�.
		ControlPos();
		return;
	}

	if (m_MoveFlag & FETCH_FLAG) {
		//���ɍs�����W�����֐�.
		FetchPos();
		return;
	}

	if (m_MoveFlag & MOVE_FLAG) {
		//�ړ������֐�.
		Move();
	}
}

//=========================================.
//		�`�揈���֐�.
//=========================================.
void CTitleStringUI::Render()
{
	for (int title = 0; title < TITLE_STRING_MAX; title++) {
		m_pCSpriteUI[title]->SetPosition(m_vTitlePos[title]);
		m_pCSpriteUI[title]->SetPattern(m_vTitleUV[title]);
		m_pCDepthStencil->SetDepth(false);
		m_pCSpriteUI[title]->Render();
		m_pCDepthStencil->SetDepth(true);
	}
}

//==========================================.
//		�����������֐�.
//==========================================.
void CTitleStringUI::Init()
{
	SPRITE_STATE SpriteState = m_pCResourceManager->GetSpriteUIState(enSpriteUI::Title);

	for (int title = 0; title < TITLE_STRING_MAX; title++) {
		m_pCSpriteUI.push_back(m_pCResourceManager->GetSpriteUI(enSpriteUI::Title));
		m_vTitleUV.push_back(D3DXVECTOR2(0.0f, 1.0f * title));
		m_vTitlePos.push_back(TITLE_POS);

		m_vTitlePos[title].x = WND_W;
		if (title == 0) {
			m_vTitlePos[title].x = -SpriteState.Disp.w;
		}

		m_vBeforeMovePos.push_back(m_vTitlePos[title]);

		m_vLastPos.push_back(TITLE_POS);
		m_vLastPos[title].x += SpriteState.Disp.w * title;

		m_bStopFlag.push_back(false);
	}
}

//==========================================.
//		��������֐�.
//==========================================.
void CTitleStringUI::Release()
{

}

//==========================================.
//		���쎞�̍��W�����֐�.
//==========================================.
void CTitleStringUI::ControlPos()
{
	for (int title = 0; title < TITLE_STRING_MAX; title++) {
		m_vTitlePos[title] = m_vLastPos[title];
	}
}

//==========================================.
//		���ɍs�����W�����֐�.
//==========================================.
void CTitleStringUI::FetchPos()
{
	m_vFetchGhostPos = m_vTitlePos[m_FetchStringNum];

	if (m_FetchStringNum == m_vTitlePos.size() - 1) {
		SPRITE_STATE SpriteState = m_pCResourceManager->GetSpriteUIState(enSpriteUI::Title);
		m_vFetchGhostPos.x += (SpriteState.Disp.w / 3.0f) * 2.0f;
	}
}

//==========================================.
//		�ړ������֐�.
//==========================================.
void CTitleStringUI::Move()
{
	m_vTitlePos[m_FetchStringNum].x = m_vBeforeMovePos[m_FetchStringNum].x + m_fMoveDistance;

	if (fabsf(m_vTitlePos[m_FetchStringNum].x - m_vLastPos[m_FetchStringNum].x) < m_fErrorRange) {
		m_vTitlePos[m_FetchStringNum] = m_vLastPos[m_FetchStringNum];
		m_bStopFlag[m_FetchStringNum] = true;
	}
}