#include "CSpeakWorkGhost.h"

/*************************************
*		������������b�N���X.
************/
CSpeakWorkGhost::CSpeakWorkGhost()
	: m_pCSpriteUI	(nullptr)
	, m_vPos		(0.0f, 0.0f, 0.0f)
	, m_GhostTypeNum(0)
	, m_vPatternNum	()
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
	m_pCSpriteUI->SetPattern(m_vPatternNum[m_GhostTypeNum]);
	m_pCSpriteUI->SetPosition(m_vPos);
	m_pCDepthStencil->SetDepth(false);
	m_pCSpriteUI->Render();
	m_pCDepthStencil->SetDepth(true);
}

//==================================.
//		�����������֐�.
//==================================.
void CSpeakWorkGhost::Init()
{
	m_pCSpriteUI = m_pCResourceManager->GetSpriteUI(enSpriteUI::Balloon);

	m_vPos = D3DXVECTOR3(650.0f, 100.0f, 0.0f);

	m_vPatternNum.push_back(D3DXVECTOR2(0.0f, 0.0f));
	m_vPatternNum.push_back(D3DXVECTOR2(1.0f, 0.0f));
}

//==================================.
//		��������֐�.
//==================================.
void CSpeakWorkGhost::Release()
{
	m_pCSpriteUI = nullptr;
}