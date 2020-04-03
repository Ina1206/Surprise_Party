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
	if (GetAsyncKeyState(VK_RETURN) & 0x0001) {
		m_SpeakNum++;
		if (m_SpeakNum >= m_stSpeakString.size()) {
			m_SpeakNum = 0;
		}
		m_pCFontResource->Load(m_stSpeakString[m_SpeakNum]);
	}
}

//=======================================.
//		�`�揈���֐�.
//=======================================.
void CSpeakTutorial::Render()
{
	for (int speak = 0; speak < 2; speak++) {
		if (m_pCSpriteUI[speak] == m_pCResourceManager->GetSpriteUI(enSpriteUI::Balloon)) {
			m_pCSpriteUI[speak]->SetPattern(D3DXVECTOR2(1.0f, 1.0f));
		}
		m_pCSpriteUI[speak]->SetPosition(m_vPos[speak]);
		m_pCDepthStencil->SetDepth(false);
		m_pCSpriteUI[speak]->Render();
		m_pCDepthStencil->SetDepth(true);
	}

	m_pCFontResource->SetFontScale(30.0f);
	m_pCFontResource->SetWidthMax(150.0f);
	m_pCFontResource->SetStartPos(m_vPos[2]);
	for (unsigned int font = 0; font < m_stSpeakString[1].size(); font++) {
		m_pCFontResource->SetAlpha(1.0f, font);
	}
	m_pCFontResource->String_Render();
}

//========================================.
//		�����������֐�.
//========================================.
void CSpeakTutorial::Init()
{
	m_pCSpriteUI.push_back(m_pCResourceManager->GetSpriteUI(enSpriteUI::BigGhostIcon));
	m_pCSpriteUI.push_back(m_pCResourceManager->GetSpriteUI(enSpriteUI::Balloon));
	
	for (unsigned int speak = 0; speak < 2; speak++) {
		m_vPos.push_back(D3DXVECTOR3(10.0f + (10.0f * speak), 400.0f - (250.0f * speak), 0.0f));
	}
	
	CFileResource*	m_pCFileResource = CFileResource::GetResourceInstance();
	for (int file = 0; file < m_pCFileResource->GetSringMax(1); file++) {
		m_stSpeakString.push_back(m_pCFileResource->GetSpeakString(1, file, CFileString::enStringType::MainString));
	}
	m_pCFontResource->Load(m_stSpeakString[m_SpeakNum]);
	m_vPos.push_back(D3DXVECTOR3(60.0f, 210.0f, 0.0f));
}

//========================================.
//		��������֐�.
//========================================.
void CSpeakTutorial::Release()
{

}

//========================================.
//		�`���[�g���A�����������֐�.
//========================================.
void CSpeakTutorial::SerchTutorial()
{
	//switch()
}