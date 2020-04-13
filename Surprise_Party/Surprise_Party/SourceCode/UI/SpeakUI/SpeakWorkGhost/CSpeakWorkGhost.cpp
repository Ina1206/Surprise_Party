#include "CSpeakWorkGhost.h"

/*************************************
*		������������b�N���X.
************/
CSpeakWorkGhost::CSpeakWorkGhost()
	: m_pCBalloonSpriteUI	(nullptr)
	, m_pCCommentSpriteUI	()
	, m_GhostTypeNum		(0)
	, m_vPatternNum			()
{
	//�����������֐�.
	Init();
}

CSpeakWorkGhost::~CSpeakWorkGhost()
{
	//��������֐�.
	Release();
}

//==================================.
//		�X�V�����֐�.
//==================================.
void CSpeakWorkGhost::Update()
{

}

//==================================.
//		�`�揈���֐�.
//==================================.
void CSpeakWorkGhost::Render()
{
	//�����o���`�揈���֐�.
	RenderBalloon();

	//�R�����g�`�揈���֐�.
	RenderComment();
}

//==================================.
//		�����������֐�.
//==================================.
void CSpeakWorkGhost::Init()
{
	m_pCBalloonSpriteUI = m_pCResourceManager->GetSpriteUI(enSpriteUI::Balloon);
	m_pCCommentSpriteUI.push_back(m_pCResourceManager->GetSpriteUI(enSpriteUI::DispPaintGhostComment));
	m_pCCommentSpriteUI.push_back(m_pCResourceManager->GetSpriteUI(enSpriteUI::SwitchGhostComment));


	m_vPatternNum.push_back(D3DXVECTOR2(0.0f, 0.0f));
	m_vPatternNum.push_back(D3DXVECTOR2(1.0f, 0.0f));
}

//==================================.
//		��������֐�.
//==================================.
void CSpeakWorkGhost::Release()
{
	for (int comment = static_cast<int>(m_pCCommentSpriteUI.size()) - 1; comment >= 0; comment--) {
		m_pCCommentSpriteUI[comment] = nullptr;
	}
	m_pCBalloonSpriteUI = nullptr;
}

//==================================.
//		�����o���`�揈���֐�.
//==================================.
void CSpeakWorkGhost::RenderBalloon()
{
	m_pCBalloonSpriteUI->SetPattern(m_vPatternNum[m_GhostTypeNum]);
	m_pCBalloonSpriteUI->SetPosition(BALLOON_POS);
	m_pCDepthStencil->SetDepth(false);
	m_pCBalloonSpriteUI->Render();
	m_pCDepthStencil->SetDepth(true);
}

//==================================.
//		�R�����g�`�揈���֐�.
//==================================.
void CSpeakWorkGhost::RenderComment()
{
	m_pCCommentSpriteUI[m_GhostTypeNum]->SetPosition(COMMENT_POS);
	m_pCDepthStencil->SetDepth(false);
	m_pCCommentSpriteUI[m_GhostTypeNum]->Render();
	m_pCDepthStencil->SetDepth(true);
}