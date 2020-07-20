#include "CReputationSNS.h"

/***************************************
*		SNS�ł̕]���N���X.
*******************/
CReputationSNS::CReputationSNS()
	: m_pCSpriteUI			(0)
	, m_vSpriteUIPos		()
	, m_fSpriteUIAlpha		()
	, m_FlashingCursorCnt	(0)
	, m_stArticleDetail		()
	, m_EndingTypeNum		(0)
	, m_ChangeStageFlag		(0)
{
	//�����������֐�.
	Init();
}

CReputationSNS::~CReputationSNS()
{
	//��������֐�.
	Release();
}

//==========================================.
//		�X�V�����֐�.
//==========================================.
void CReputationSNS::Update()
{
	if (GetAsyncKeyState(VK_RETURN) & 0x0001) {
		if (m_bAppearanceAllFont == false) {
			//�����X�L�b�v.
			if (m_bAppearanceAllFont == false) {
				m_pCPlaySoundManager->SetPlaySE(enSEType::FontSkip);
			}
			m_bAppearanceAllFont = true;
			return;
		}

		if (m_bFinishAppearancedAllFont == true) {
			//���ߊJ�n.
			m_ChangeStageFlag = START_TRANSPARENT_FLAG;
			//���̃X�e�[�W��.
			m_pCPlaySoundManager->SetPlaySE(enSEType::NextString);
		}
	}

	if (m_ChangeStageFlag & START_TRANSPARENT_FLAG) {
		//�S�Ă̓��ߏ����֐�.
		TransparentAll();
		return;
	}

	//�������ߏ���.
	TransparentFont();

	//�t�H���g�̓��ߒl�����֐�.
	FontAlpha();

	//�J�[�\���X�V�����֐�.
	UpdateCursor();

}

//==========================================.
//		�`�揈���֐�.
//==========================================.
void CReputationSNS::Render()
{
	//�f�v�X�X�e���V��.
	CDepth_Stencil* m_pCDepthStencil = CDepth_Stencil::GetDepthStencilInstance();

	m_pCDepthStencil->SetDepth(false);

	//�X�v���C�gUI�`�揈���֐�.
	RenderSpriteUI();

	//�����`�揈���֐�.
	RenderFont();

	m_pCDepthStencil->SetDepth(true);
	
}

//==========================================.
//		���͌��菈���֐�.
//==========================================.
void CReputationSNS::DecideString(const int& EndingNum)
{
	const int m_EndingNum = EndingNum;
	CFileResource* m_pCFileResource = CFileResource::GetResourceInstance();
	//�ǂݍ��ރt�@�C���ԍ�.
	const int m_FileNum = static_cast<int>(CFileResource::enSpeakFileType::EndingSpeak);
	//���C��������̔ԍ�.
	const CFileString::enStringType MainStringNum = CFileString::enStringType::MainString;
	m_stSpeakString.push_back(m_pCFileResource->GetSpeakString(m_FileNum, m_EndingNum, MainStringNum));

	//�ǂݍ��ݏ����֐�.
	m_pCFontResource->Load(m_stSpeakString[0]);

	//�ʐ^���菈���֐�.
	DecidePicture(m_EndingNum);

}

//==========================================.
//		�����������֐�.
//==========================================.
void CReputationSNS::Init()
{
	//�J�[�\���ݒ菈��.
	m_pCSpriteUI.emplace_back(m_pCResourceManager->GetSpriteUI(enSpriteUI::CursorSNS));
	m_vSpriteUIPos.push_back(INIT_FONT_POS);
	m_fSpriteUIAlpha.push_back(ALPHA_MAX);

	
	//�t�H���g�̏���������.
	m_pCFontResource->SetStartPos(INIT_FONT_POS);
	m_pCFontResource->SetFontScale(FONT_SCALE);
	m_pCFontResource->SetWidthMax(STRING_WIDTH_MAX);
}

//==========================================.
//		��������֐�.
//==========================================.
void CReputationSNS::Release()
{

}

//==========================================.
//		�J�[�\���X�V�����֐�.
//==========================================.
void CReputationSNS::UpdateCursor()
{
	//�J�[�\���ړ������֐�.
	MoveCursor();

	m_FlashingCursorCnt++;

	if (m_FlashingCursorCnt > FLASING_CNT_MAX) {
		
		m_FlashingCursorCnt = 0;
		if (m_ChangingFontNum >= m_pCFontResource->GetStrLength()) {
			m_pCPlaySoundManager->SetPlaySE(enSEType::Font);
		}

		if (m_fSpriteUIAlpha[CURSOR_NUM] >= ALPHA_MAX) {
			m_fSpriteUIAlpha[CURSOR_NUM] = 0.0f;
			return;
		}
		
		m_fSpriteUIAlpha[CURSOR_NUM] = ALPHA_MAX;
	}
}


//==========================================.
//		�J�[�\���ړ������֐�.
//==========================================.
void CReputationSNS::MoveCursor()
{
	if (m_ChangingFontNum < m_pCFontResource->GetStrLength()) {
		m_vSpriteUIPos[CURSOR_NUM] = m_pCFontResource->GetFontPos(m_ChangingFontNum);
		m_vSpriteUIPos[CURSOR_NUM].y += ADJUSTMENT_HEIGHT;
		return;
	}

	//��Ԓ[�̍��W����ꕶ���������Ƃ���ɒu��.
	m_vSpriteUIPos[CURSOR_NUM] = m_pCFontResource->GetFontPos(m_ChangingFontNum - 1);
	m_vSpriteUIPos[CURSOR_NUM].x += FONT_SCALE;

	m_vSpriteUIPos[CURSOR_NUM].y += ADJUSTMENT_HEIGHT;

}

//===========================================.
//		�ʐ^���菈���֐�.
//===========================================.
void CReputationSNS::DecidePicture(const int& EndingType)
{
	//Sprite�ԍ�.
	const int SpriteNum = static_cast<int>(enSpriteUI::PictureSNSRest) + EndingType;

	m_pCSpriteUI.emplace_back(m_pCResourceManager->GetSpriteUI(static_cast<enSpriteUI>(SpriteNum)));
	m_vSpriteUIPos.push_back(PICTURE_POS);
	m_fSpriteUIAlpha.push_back(ALPHA_MAX);
}

//============================================.
//		�X�v���C�gUI�`�揈���֐�.
//============================================.
void CReputationSNS::RenderSpriteUI()
{
	for (unsigned int SpriteUI = 0; SpriteUI < m_pCSpriteUI.size(); SpriteUI++) {
		m_pCSpriteUI[SpriteUI]->SetPosition(m_vSpriteUIPos[SpriteUI]);
		m_pCSpriteUI[SpriteUI]->SetAlpha(m_fSpriteUIAlpha[SpriteUI]);
		m_pCSpriteUI[SpriteUI]->Render();
	}
}

//============================================.
//		�S�Ă̓��ߏ����֐�.
//============================================.
void CReputationSNS::TransparentAll()
{
	//�t�H���g�̓��ߒl����.
	m_fFontAlpha -= FONT_ALPHA_SPEED;
	if (m_fFontAlpha < 0.0f) {
		m_fFontAlpha = 0.0f;
	}

	for (int font = 0; font < m_pCFontResource->GetStrLength(); font++) {
		m_pCFontResource->SetAlpha(m_fFontAlpha, font);
	}

	//�X�v���C�gUI�̓��ߏ���.
	for (unsigned int SpriteUI = 0; SpriteUI < m_pCSpriteUI.size(); SpriteUI++) {
		m_fSpriteUIAlpha[SpriteUI] -= PICTURE_ALPHA_SPEED;
		m_pCSpriteUI[SpriteUI]->SetAlpha(m_fSpriteUIAlpha[SpriteUI]);

		if (m_fSpriteUIAlpha[SpriteUI] < 0.0f) {
			m_fSpriteUIAlpha[SpriteUI] = 0.0f;
		}
	}

	if (m_fSpriteUIAlpha[PICTURE_NUM] <= 0.0f) {
		//�X�e�[�W�ύX.
		m_ChangeStageFlag = CHANGE_STAGE_FLAG;
	}
}