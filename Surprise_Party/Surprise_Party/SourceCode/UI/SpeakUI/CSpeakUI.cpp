#include "CSpeakUI.h"

CSpeakUI::CSpeakUI()
	: m_pCFileResource				(CFileResource::GetResourceInstance())
	, m_pCFontResource				(nullptr)
	, m_stSpeakString				()
	, m_stSelectString				()
	, m_SpeakNum					(0)
	, m_fFontAlpha					(0.0f)
	, m_ChangingFontNum				(0)
	, m_bAppearanceAllFont			(false)
	, m_bFinishAppearancedAllFont	(false)
	, m_bAutoFlag					(false)
{
	m_pCFontResource = CResourceManager::GetResourceManagerInstance()->GetFont();
	//�O�̃f�[�^���폜.
	m_pCFontResource->Destroy();
}

CSpeakUI::~CSpeakUI()
{
	m_pCFontResource = nullptr;
}

//======================================.
//		�����`�揈���֐�.
//======================================.
void CSpeakUI::RenderFont()
{
	//�����̕`��.
	if (m_ChangingFontNum < m_pCFontResource->GetStrLength()) {
		m_pCFontResource->SetAlpha(m_fFontAlpha, m_ChangingFontNum);
	}
	m_pCFontResource->String_Render();
}

//======================================.
//		�������ߏ����֐�.
//======================================.
void CSpeakUI::TransparentFont()
{
	//��O����.
	if (m_ChangingFontNum >= m_pCFontResource->GetStrLength()) {
		m_bFinishAppearancedAllFont = true;
		return;
	}

	//���̕����ɕύX.
	if (m_fFontAlpha >= ALPHA_MAX) {
		m_ChangingFontNum++;
		m_fFontAlpha = ALPHA_MIN;
	}

	const int	FileNum			= static_cast<int>(CFileResource::enStatusCharaType::GhostSpeak);
	const int	StatusNum		= static_cast<int>(enStatusType::FontSpeed);
	const int	FontDispSpeed	= static_cast<int>(m_pCFileResource->GetStatusNum(FileNum, StatusNum, 0));
	const float AlphaSpeed		= ALPHA_MAX / FontDispSpeed;
	m_fFontAlpha += AlphaSpeed;

	//��C�ɓ��ߒl�ő�l��.
	if (m_bAppearanceAllFont == true) {
		m_fFontAlpha = ALPHA_MAX;
	}

	//�������.
	if (m_fFontAlpha > ALPHA_MAX) {
		m_fFontAlpha = ALPHA_MAX;

		//������SE�����H.
	}
}

//=======================================.
//		���͕ύX���菈���֐�.
//=======================================.
bool CSpeakUI::DesicionChangeString()
{
	if (m_ChangingFontNum < m_pCFontResource->GetStrLength()) {
		m_bAppearanceAllFont = true;
		return false;
	}

	//���͂����ɍs�����邽�߂̏���������.
	m_fFontAlpha = ALPHA_MIN;
	m_bAppearanceAllFont = false;
	m_ChangingFontNum = 0;
	m_bFinishAppearancedAllFont = false;

	return true;
}

//=======================================.
//		�����Đ������֐�.
//=======================================.
bool CSpeakUI::AutomaticReproducing()
{
	if (GetAsyncKeyState('Z') & 0x8000) {
		if (m_bAutoFlag == false) {
			m_bAutoFlag = true;
			return true;
		}

		m_bAutoFlag = false;
		return false;
	}

	if (m_bAutoFlag == false) {
		return false;
	}
	
	if (DesicionChangeString() == false) {
		return false;
	}


	return true;
}