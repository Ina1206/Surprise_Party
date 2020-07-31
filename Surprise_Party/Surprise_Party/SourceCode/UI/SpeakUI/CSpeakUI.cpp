#include "CSpeakUI.h"

/****************************************************
*		SpeakUI�N���X.
***********************/
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
	, m_pCAutoUI					(nullptr)
	, m_AutoFlag					(0)
	, m_AutoWaitCnt					(0)
	, m_pCPlaySoundManager			(CPlaySoundManager::GetPlaySoundManager())
{
	m_pCFontResource = CResourceManager::GetResourceManagerInstance()->GetFont();
	//�O�̃f�[�^���폜.
	m_pCFontResource->Destroy();
	//�����Đ�����UI�N���X�C���X�^���X��.
	m_pCAutoUI.reset(new CAutoUI());
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
		m_pCPlaySoundManager->SetPlaySE(enSEType::Font);
	}
}

//=======================================.
//		���͕ύX���菈���֐�.
//=======================================.
bool CSpeakUI::DesicionChangeString()
{
	//�ꕶ���ڕ\�����̓X�L�b�v���Ȃ�.
	if (m_ChangingFontNum <= 0) {
		return false;
	}

	if (m_ChangingFontNum < m_pCFontResource->GetStrLength()) {
		//�t�H���g�X�L�b�v.
		if (m_bAppearanceAllFont == false) {
			m_pCPlaySoundManager->SetPlaySE(enSEType::FontSkip);
		}
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
	//�����Đ��̕ύX����.
	if (GetAsyncKeyState('Z') & 0x0001) {
		if (!(m_AutoFlag & AUTO_FLAG)) {
			m_AutoFlag = AUTO_FLAG;
			return false;
		}

		m_AutoFlag = 0;
		return false;
	}

	//�ꎞ��~���̓I�[�g�t���O�̏��������Ȃ�.
	if (m_AutoFlag & AUTO_SUSPEND_FLAG) {
		return false;
	}

	if (!(m_AutoFlag & AUTO_FLAG)) {
		return false;
	}

	//�����Đ�����UI�X�V�����֐�.
	m_pCAutoUI->Update();

	//�������S�ĂŏI���܂ōĐ����Ȃ�����.
	if (m_ChangingFontNum < m_pCFontResource->GetStrLength()) {
		return false;
	}
	
	//�S�ďo�Ă������҂��Ă���Đ����鏈��.
	const int FileNum		= static_cast<int>(CFileResource::enStatusCharaType::GhostSpeak);			//�t�@�C���ԍ�.
	const int StatusNum		= static_cast<int>(enStatusType::AutoWaitSpeed);							//�X�e�[�^�X�ԍ�.
	const int AutoWaitMax	= static_cast<int>(m_pCFileResource->GetStatusNum(FileNum, StatusNum, 0));	//�����Đ��ҋ@�ő�l.
	m_AutoWaitCnt++;
	if (m_AutoWaitCnt < AutoWaitMax) {
		return false;
	}
	m_AutoWaitCnt = 0;

	return true;
}

//===========================================.
//		�t�H���g�̓��ߒl�����֐�.
//===========================================.
void CSpeakUI::FontAlpha()
{
	//�S�Ă�\�����鏈��.
	if (m_bAppearanceAllFont == true) {
		for (int str = 0; str < m_pCFontResource->GetStrLength(); str++) {
			m_pCFontResource->SetAlpha(ALPHA_MAX, str);
		}
		m_ChangingFontNum = m_pCFontResource->GetStrLength();
		return;
	}

	//�ꕶ�����\�����鏈��.
	if (m_ChangingFontNum < m_pCFontResource->GetStrLength()) {
		m_pCFontResource->SetAlpha(m_fFontAlpha, m_ChangingFontNum);
	}

}