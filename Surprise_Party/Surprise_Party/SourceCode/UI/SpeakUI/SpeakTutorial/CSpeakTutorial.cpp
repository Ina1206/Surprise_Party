#include "CSpeakTutorial.h"

/******************************************
*		�`���[�g���A����b.
***************/
CSpeakTutorial::CSpeakTutorial()
	: m_pCSpriteUI			()
	, m_pCDescriptionIcon	()
	, m_vIconPos			()
	, m_vPos				()
	, m_vPattern			()
	, m_TutorialFlag		(0)
	, m_DescriptionFlag		(0)
	, m_bAdvanceCommentFlag	(true)
	, m_SelectMoveCount		(0)
	, m_enStartLatestFlag	(0)
	, m_bDescriptionEnd		(false)
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
	if (m_enStartLatestFlag & SeePeople) {
		m_enStartLatestFlag = 0;
	}

	if (m_bAdvanceCommentFlag == true) {
		if (GetAsyncKeyState(VK_RETURN) & 0x0001) {
			if (m_enStartLatestFlag & DescriptionEnd) {
				m_bDescriptionEnd = true;
				return;
			}

			//�R�����g���i�߂鏈��.
			AdvanceOnceComment();
		}
	}
}

//=======================================.
//		�`�揈���֐�.
//=======================================.
void CSpeakTutorial::Render()
{
	//�����o���̕`��.
	for (unsigned int speak = 0; speak < m_pCSpriteUI.size(); speak++) {
		//�����o����ސݒ�.
		if (m_pCSpriteUI[speak] == m_pCResourceManager->GetSpriteUI(enSpriteUI::Balloon)) {
			m_pCSpriteUI[speak]->SetPattern(D3DXVECTOR2(1.0f, 1.0f));
		}
		m_pCSpriteUI[speak]->SetScale(1.3f);
		m_pCSpriteUI[speak]->SetPosition(m_vPos[speak]);
		m_pCDepthStencil->SetDepth(false);
		m_pCSpriteUI[speak]->Render();
		m_pCDepthStencil->SetDepth(true);
	}

	//�e�L�X�g�̕`��.
	for (unsigned int font = 0; font < m_stSpeakString[m_SpeakNum].length() / 2; font++) {
		m_pCFontResource->SetAlpha(1.0f, font);
	}
	m_pCFontResource->String_Render();

	//�����p�A�C�R���`�揈���֐�.
	RenderDescriptionIcon();
}

//========================================.
//		���R�����g��i�߂鏈���֐�.
//========================================.
void CSpeakTutorial::AdvanceOnceComment()
{
	m_SpeakNum++;
	if (static_cast<unsigned int>(m_SpeakNum) >= m_stSpeakString.size()) {
		m_SpeakNum = 0;
	}
	m_pCFontResource->Load(m_stSpeakString[m_SpeakNum], true);
	//�`���[�g���A���T�������֐�.
	FindTutorial();
}

//========================================.
//		�I���ړ��J�E���g�ǉ������֐�.
//========================================.
void CSpeakTutorial::AddSelectMoveCount()
{
	//��O����(�I�����ȊO��O).
	const unsigned int SELECT_FLAG = SELECT_GHOST_FLAG | SELECT_GIMMICK_FLAG;
	if (!(m_TutorialFlag & SELECT_FLAG)) {
		return;
	}

	m_SelectMoveCount++;

	if (m_SelectMoveCount >= 2) {
		//���R�����g��i�߂鏈���֐�.
		AdvanceOnceComment();

		m_SelectMoveCount = 0;
	}
}

//========================================.
//		�����������֐�.
//========================================.
void CSpeakTutorial::Init()
{
	m_pCSpriteUI.push_back(m_pCResourceManager->GetSpriteUI(enSpriteUI::BigGhostIcon));
	m_pCSpriteUI.push_back(m_pCResourceManager->GetSpriteUI(enSpriteUI::Balloon));
	
	for (unsigned int speak = 0; speak < m_pCSpriteUI.size(); speak++) {
		m_vPos.push_back(D3DXVECTOR3(10.0f + (10.0f * speak), 400.0f - (250.0f * speak), 0.0f));
	}
	
	CFileResource*	m_pCFileResource = CFileResource::GetResourceInstance();
	//�ǂݍ��ރt�@�C���ԍ�.
	const int LoadFileNum = static_cast<int>(CFileResource::enSpeakFileType::SpeakTutorialBigGhost);
	for (int file = 0; file < m_pCFileResource->GetSringMax(LoadFileNum); file++) {
		m_stSpeakString.push_back(m_pCFileResource->GetSpeakString(LoadFileNum, file, CFileString::enStringType::MainString));
		m_stSelectString.push_back(m_pCFileResource->GetSpeakString(LoadFileNum, file, CFileString::enStringType::SelectString));
	}
	m_vPos.push_back(D3DXVECTOR3(60.0f, 210.0f, 0.0f));

	m_pCFontResource->SetFontScale(40.0f);
	m_pCFontResource->SetWidthMax(200.0f);
	const D3DXVECTOR3 vFontPos = m_vPos[2] + D3DXVECTOR3(0.0f, 10.0f, 0.0f);
	m_pCFontResource->SetStartPos(vFontPos);
	m_pCFontResource->Load(m_stSpeakString[m_SpeakNum], true);

}

//========================================.
//		��������֐�.
//========================================.
void CSpeakTutorial::Release()
{

}

//========================================.
//		�`���[�g���A�������鏈���֐�.
//========================================.
void CSpeakTutorial::FindTutorial()
{
	m_DescriptionFlag = 0;
	if (m_stSelectString[m_SpeakNum] == "0") {
		m_bAdvanceCommentFlag = true;
		return;
	}

	if (m_stSelectString[m_SpeakNum] == "GhostSelect") {
		m_TutorialFlag = SELECT_GHOST_FLAG;
		//�R�����g�i�߂�̒�~.
		m_bAdvanceCommentFlag = false;
		return;
	}

	if (m_stSelectString[m_SpeakNum] == "GhostDecide") {
		m_TutorialFlag = DECIDE_GHOST_FLAG;
		return;
	}

	if (m_stSelectString[m_SpeakNum] == "ActDecide") {
		m_TutorialFlag = DECIDE_ACT_FLAG;
		//�R�����g�i�߂�̒�~.
		m_bAdvanceCommentFlag = false;
		return;
	}

	if (m_stSelectString[m_SpeakNum] == "GimmickSelect") {
		m_TutorialFlag = SELECT_GIMMICK_FLAG;
		m_bAdvanceCommentFlag = false;
		return;
	}

	if (m_stSelectString[m_SpeakNum] == "GimmickDecide") {
		m_TutorialFlag = DECIDE_GIMMICK_FLAG;
		return;
	}

	//�������e���������֐�.
	FindDescription();

	//�����p�A�C�R���ݒ菈���֐�.
	SettingDescriptionIcon();

}

//========================================.
//		�������e�����鏈���֐�.
//========================================.
void CSpeakTutorial::FindDescription()
{

	if (m_stSelectString[m_SpeakNum] == "MapDescription") {
		m_DescriptionFlag = MAP_DESCRIPTION_FLAG;
		return;
	}

	if (m_stSelectString[m_SpeakNum] == "GhostDescription") {
		m_DescriptionFlag = GHOST_DESCRIPTION_FLAG;
		return;
	}

	if (m_stSelectString[m_SpeakNum] == "GimmickDescription") {
		m_DescriptionFlag = GIMMICK_DESCRIPTION_FLAG;
		return;
	}

	if (m_stSelectString[m_SpeakNum] == "PeopleDescription") {
		m_DescriptionFlag = PEOPLE_DESCRIPTION_FLAG;
		return;
	}

	if (m_stSelectString[m_SpeakNum] == "SurpriseGageDescription") {
		m_DescriptionFlag = GAGE_DESCRIPTION_FLAG;
		return;
	}

	if (m_stSelectString[m_SpeakNum] == "CloseTimeDescription") {
		m_DescriptionFlag = CLOSE_TIME_DESCRIPTION_FLAG;
		return;
	}

	if (m_stSelectString[m_SpeakNum] == "CustomerEnterSE") {
		m_enStartLatestFlag = CustomerEnterSE;
		return;
	}

	if (m_stSelectString[m_SpeakNum] == "SeePeople") {
		m_enStartLatestFlag = SeePeople;
		return;
	}

	if (m_stSelectString[m_SpeakNum] == "DescriptionEnd") {
		m_enStartLatestFlag = DescriptionEnd;
	}
}

//=========================================.
//		�����p�A�C�R���ݒ菈���֐�.
//=========================================.
void CSpeakTutorial::SettingDescriptionIcon()
{
	//�폜.
	if (m_pCDescriptionIcon.size() > 0) {
		m_pCDescriptionIcon.clear();
	}

	//�}���A�C�R���̃T�C�Y.
	const unsigned int ICON_MAX = m_pCFontResource->GetInputPictureSize();

	//��O����.
	if (ICON_MAX <= 0) {
		return;
	}

	//�t�H���g���W.
	for (unsigned int Icon = 0; Icon < ICON_MAX; Icon++) {
		const int			FontNum = m_pCFontResource->GetInputPictureNum(Icon);
		const D3DXVECTOR3	vPosAdjustment = D3DXVECTOR3(-10.0f, -10.0f, 0.0f);
		const D3DXVECTOR3	vFontPos = m_pCFontResource->GetFontPos(FontNum) + vPosAdjustment;
		
		if (Icon < m_vIconPos.size()) {
			m_vIconPos[Icon] = vFontPos;
			continue;
		}
		m_vIconPos.push_back(vFontPos);
	}

	//�������̃A�C�R���ݒ�.
	if (m_DescriptionFlag & GHOST_DESCRIPTION_FLAG) {
		GhostIconSetting(ICON_MAX);

		return;
	}

	//�M�~�b�N�A�C�R���ݒ�.
	if (m_DescriptionFlag & GIMMICK_DESCRIPTION_FLAG) {
		GimmickIconSetting(ICON_MAX);
		return;
	}

	//�l�̃A�C�R��.
	if (m_DescriptionFlag & PEOPLE_DESCRIPTION_FLAG) {
		PeopleIconSetting(ICON_MAX);
		return;
	}
}

//===========================================.
//		�����p�A�C�R���`�揈���֐�.
//===========================================.
void CSpeakTutorial::RenderDescriptionIcon()
{
	if (m_pCDescriptionIcon.size() <= 0) {
		return;
	}
	
	for (unsigned int IconNum = 0; IconNum < m_pCDescriptionIcon.size(); IconNum++) {
		if (m_DescriptionFlag & GHOST_DESCRIPTION_FLAG) {
			m_pCDescriptionIcon[IconNum]->SetPattern(m_vPattern[IconNum]);
		}
		m_pCDescriptionIcon[IconNum]->SetAlpha(ALPHA_MAX);
		m_pCDescriptionIcon[IconNum]->SetPosition(m_vIconPos[IconNum]);
		m_pCDescriptionIcon[IconNum]->SetScale(DESCRIPTION_ICON_SCALE);
		m_pCDepthStencil->SetDepth(false);
		m_pCDescriptionIcon[IconNum]->Render();
		m_pCDepthStencil->SetDepth(true);
	}
}

//============================================.
//		�������A�C�R���ݒ菈���֐�.
//============================================.
void CSpeakTutorial::GhostIconSetting(const int& IconMax)
{
	if (m_vPattern.size() > 0) {
		m_vPattern.clear();
	}

	for (int Icon = 0; Icon < IconMax; Icon++) {
		
		m_pCDescriptionIcon.push_back(m_pCResourceManager->GetSpriteUI(enSpriteUI::Ghost_Icon));

		const std::string InputPictureType = m_pCFontResource->GetPictureTypeNum(Icon);
		if (InputPictureType == "�O") {
			m_vPattern.push_back(D3DXVECTOR2(0.0f, 0.0f));
			continue;
		}
		if (InputPictureType == "�P") {
			m_vPattern.push_back(D3DXVECTOR2(0.0f, 2.0f));
		}
	}
}

//============================================.
//		�M�~�b�N�A�C�R���ݒ菈���֐�.
//============================================.
void CSpeakTutorial::GimmickIconSetting(const int& IconMax)
{
	for (int Icon = 0; Icon < IconMax; Icon++) {
		const std::string InputPictureType = m_pCFontResource->GetPictureTypeNum(Icon);
		if (InputPictureType == "�O") {
			m_pCDescriptionIcon.push_back(m_pCResourceManager->GetSpriteUI(enSpriteUI::DispGimmick_Iccon));
			continue;
		}
		if (InputPictureType == "�P") {
			m_pCDescriptionIcon.push_back(m_pCResourceManager->GetSpriteUI(enSpriteUI::Switch_Icon));
		}
	}
}

//============================================.
//		�l�X�̃A�C�R���ݒ菈���֐�.
//============================================.
void CSpeakTutorial::PeopleIconSetting(const int& IconMax)
{
	for (int Icon = 0; Icon < IconMax; Icon++) {
		const std::string InputPictureType = m_pCFontResource->GetPictureTypeNum(Icon);
		if (InputPictureType == "�O") {
			m_pCDescriptionIcon.push_back(m_pCResourceManager->GetSpriteUI(enSpriteUI::Girl_Icon));
			continue;
		}
		if (InputPictureType == "�P") {
			m_pCDescriptionIcon.push_back(m_pCResourceManager->GetSpriteUI(enSpriteUI::Boy_Icon));
		}
	}

}