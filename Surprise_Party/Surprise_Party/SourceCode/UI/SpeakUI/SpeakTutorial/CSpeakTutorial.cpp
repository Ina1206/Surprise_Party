#include "CSpeakTutorial.h"

CSpeakTutorial::CSpeakTutorial()
	: m_pCSpriteUI	()
	, m_vPos		()
{
	//�����������֐�.
	Init();
}

CSpeakTutorial::~CSpeakTutorial()
{
	//��������֐�.
	Release();
}

//======================================.
//		�X�V�����֐�.
//======================================.
void CSpeakTutorial::Update()
{

}

//=======================================.
//		�`�揈���֐�.
//=======================================.
void CSpeakTutorial::Render()
{
	m_pCSpriteUI[1]->SetPattern(D3DXVECTOR2(1.0f, 1.0f));
	for (int speak = 0; speak < 2; speak++) {
		m_pCSpriteUI[speak]->SetPosition(m_vPos[speak]);
		m_pCDepthStencil->SetDepth(false);
		m_pCSpriteUI[speak]->Render();
		m_pCDepthStencil->SetDepth(true);
	}
}

//========================================.
//		�����������֐�.
//========================================.
void CSpeakTutorial::Init()
{
	m_pCSpriteUI.push_back(m_pCResourceManager->GetSpriteUI(enSpriteUI::BigGhostIcon));
	m_pCSpriteUI.push_back(m_pCResourceManager->GetSpriteUI(enSpriteUI::Balloon));
	
	for (unsigned int speak = 0; speak < 2; speak++) {
		m_vPos.push_back(D3DXVECTOR3(10.0f + (10.0f * (speak * 2)), 400.0f - (250.0f * (speak % 2)), 0.0f));
	}
	
}

//========================================.
//		��������֐�.
//========================================.
void CSpeakTutorial::Release()
{

}