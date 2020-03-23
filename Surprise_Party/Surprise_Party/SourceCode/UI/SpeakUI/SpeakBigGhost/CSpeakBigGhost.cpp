#include "CSpeakBigGhost.h"

CSpeakBigGhost::CSpeakBigGhost()
	: m_pCSpriteUI			()
	, m_vPos				()
	, m_vRot				()
	, m_fAlpha				()
	, m_fScale				()
	, m_bSelectFlag			(false)
	, m_stSpeakString		()
	, m_SpeakNum			(0)
	, m_fFontAlpha			(0.0f)
	, m_ChangingFontNum		(0)
	, m_bChangeStringFlag	(false)
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
		if (m_ChangingFontNum >= m_pCFontResource->GetStrLength()) {
			//�ǂݍ��ݏ����֐�.
			m_pCFontResource->Load(m_stSpeakString[m_SpeakNum]);
			m_SpeakNum++;
			if (static_cast<unsigned int>(m_SpeakNum) >= m_stSpeakString.size()) {
				m_SpeakNum = 0;
			}
			m_ChangingFontNum = 0;
			m_fFontAlpha = 0.0f;
			m_bChangeStringFlag = false;
		}
		else {
			m_bChangeStringFlag = true;
		}
	}

	TransparentFont();
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
	if (m_ChangingFontNum < m_pCFontResource->GetStrLength()) {
		m_pCFontResource->SetAlpha(m_fFontAlpha, m_ChangingFontNum);
	}
	m_pCFontResource->SetFontScale(FONT_SCALE);
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
	CFileResource*	m_pCFileReosource = CFileResource::GetResourceInstance();

	//�t�@�C���̒��̑S���͐ݒ�.
	for (int splite = 0; splite < m_pCFileReosource->GetSringMax(0); splite++) {
		m_stSpeakString.push_back(m_pCFileReosource->GetSpeakString(0, splite, CFileString::enStringType::MainString));
		m_stSelectString.push_back(m_pCFileReosource->GetSpeakString(0, splite, CFileString::enStringType::SelectString));
	}

	m_pCFontResource = CResourceManager::GetResourceManagerInstance()->GetFont();
	//�ǂݍ��ݏ����֐�.
	m_pCFontResource->Load(m_stSpeakString[m_SpeakNum]);
	//�ʒu�ݒ菈���֐�
	m_pCFontResource->SetStartPos(D3DXVECTOR3(90.0f, 480.0f, 0.0f));
}

//======================================.
//		�������ߏ����֐�.
//======================================.
void CSpeakBigGhost::TransparentFont()
{
	//��O����.
	if (m_ChangingFontNum >= m_pCFontResource->GetStrLength()) {
		return;
	}

	//���̕����ɕύX.
	if (m_fFontAlpha == ALPHA_MAX) {
		m_ChangingFontNum++;
		m_fFontAlpha = ALPHA_MIN;
	}
	
	//��C�ɓ��ߒl�ő�l��.
	if (m_bChangeStringFlag == true) {
		m_fFontAlpha = ALPHA_MAX;
	}

	m_fFontAlpha += ALPHA_SPEED;

	//�������.
	if (m_fFontAlpha > ALPHA_MAX) {
		m_fFontAlpha = ALPHA_MAX;

		//������SE�����H.
	}
}