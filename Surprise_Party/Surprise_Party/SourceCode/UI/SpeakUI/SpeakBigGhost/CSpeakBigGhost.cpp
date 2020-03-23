#include "CSpeakBigGhost.h"

CSpeakBigGhost::CSpeakBigGhost()
	: m_pCSpriteUI		()
	, m_vPos			()
	, m_vRot			()
	, m_fAlpha			()
	, m_fScale			()
	, m_bSelectFlag		(false)
	, m_stSpeakString	()
	, m_SpeakNum		(0)
{
	//�����������֐�.
	Init();
}

CSpeakBigGhost::~CSpeakBigGhost()
{
	//��������֐�.
	Release();
}

//====================================.
//		�X�V�����֐�.
//====================================.
void CSpeakBigGhost::Update()
{
	if (GetAsyncKeyState(VK_RETURN) & 0x0001) {
		//�ǂݍ��ݏ����֐�.
		m_pCFontResource->Load(m_stSpeakString[m_SpeakNum]);
		m_SpeakNum++;
		if (static_cast<unsigned int>(m_SpeakNum) >= m_stSpeakString.size()) {
			m_SpeakNum = 0;
		}
	}

}

//====================================.
//		�`�揈���֐�.
//====================================.
void CSpeakBigGhost::Render()
{
	for (unsigned int ui = 0; ui < m_pCSpriteUI.size(); ui++) {
		m_pCSpriteUI[ui]->SetAlpha(m_fAlpha[ui]);
		m_pCSpriteUI[ui]->SetScale(m_fScale[ui]);
		m_pCSpriteUI[ui]->SetPosition(m_vPos[ui]);
		m_pCDepthStencil->SetDepth(false);
		m_pCSpriteUI[ui]->Render();
		m_pCDepthStencil->SetDepth(true);
	}

	//�����̕`��.
	m_pCFontResource->SetWidthMax(STRING_WIDTH_MAX);
	m_pCFontResource->String_Render();
}

//====================================.
//		�����������֐�.
//====================================.
void CSpeakBigGhost::Init()
{
	m_pCSpriteUI.resize(3);
	m_vPos.resize(m_pCSpriteUI.size());
	m_vRot.resize(m_pCSpriteUI.size());
	m_fAlpha.resize(m_pCSpriteUI.size());
	m_fScale.resize(m_pCSpriteUI.size());

	m_pCSpriteUI[0] = m_pCResourceManager->GetSpriteUI(enSpriteUI::TextBox);
	for (unsigned int ui = 1; ui < m_pCSpriteUI.size(); ui++) {
		m_pCSpriteUI[ui] = m_pCResourceManager->GetSpriteUI(enSpriteUI::TextBoxSmall);
	}

	m_vPos[0] = D3DXVECTOR3(50.0f, 450.0f, 0.0f);
	
	for (unsigned int ui = 0; ui < m_pCSpriteUI.size(); ui++) {
		m_fScale[ui] = 1.0f;
		m_fAlpha[ui] = 1.0f;
	}

	//��b���͓ǂݍ��ݏ����֐�.
	LoadSpeakString();
}

//====================================.
//		��������֐�.
//====================================.
void CSpeakBigGhost::Release()
{
	//�폜�����֐�.
	m_pCFontResource->Destroy();
}

//=====================================.
//		��b���͓ǂݍ��ݏ����֐�.
//=====================================.
void CSpeakBigGhost::LoadSpeakString()
{
	//�t�@�C���ǂݍ���.
	CFile* m_pCFile = new CFile();
	m_pCFile->FileInput("Data\\File\\Test.csv");

	//�t�@�C���̒��̑S���͐ݒ�.
	for (int splite = 0; splite < m_pCFile->GetColumnMax(); splite++) {
		m_stSpeakString.push_back(m_pCFile->GetLineData(splite));
	}
	m_pCFile->Close();
	SAFE_DELETE(m_pCFile);


	m_pCFontResource = CResourceManager::GetResourceManagerInstance()->GetFont();
	//�ǂݍ��ݏ����֐�.
	m_pCFontResource->Load(m_stSpeakString[m_SpeakNum]);
	//�ʒu�ݒ菈���֐�
	m_pCFontResource->SetStartPos(D3DXVECTOR3(90.0f, 480.0f, 0.0f));

	m_pCFontResource->SetFontScale(50.0f);
}