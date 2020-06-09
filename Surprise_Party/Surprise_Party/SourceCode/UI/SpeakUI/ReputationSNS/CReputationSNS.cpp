#include "CReputationSNS.h"

/***************************************
*		SNS�ł̕]���N���X.
*******************/
CReputationSNS::CReputationSNS()
	: m_pCSpriteUI			(nullptr)
	, m_pCPictureUI			(nullptr)
	, m_vCursorPos			(0.0f, 0.0f, 0.0f)
	, m_fCursorAlpha		(ALPHA_MAX)
	, m_FlashingCursorCnt	(0)
	, m_stArticleDetail		()
	, m_EndingTypeNum		(0)
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
	//�������ߏ���.
	TransparentFont();

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

	//�J�[�\���`�揈���֐�.
	RenderCursor();

	//�ʐ^�`�揈���֐�.
	RenderPicture();

	//�����`�揈���֐�.
	RenderFont();

	m_pCDepthStencil->SetDepth(true);
	
}

//==========================================.
//		���͌��菈���֐�.
//==========================================.
void CReputationSNS::DecideString(const int& EndingNum)
{
	CFileResource* m_pCFileResource = CFileResource::GetResourceInstance();
	//�ǂݍ��ރt�@�C���ԍ�.
	const int m_FileNum = static_cast<int>(CFileResource::enSpeakFileType::EndingSpeak);
	//���C��������̔ԍ�.
	const CFileString::enStringType MainStringNum = CFileString::enStringType::MainString;
	m_stSpeakString.push_back(m_pCFileResource->GetSpeakString(m_FileNum, EndingNum, MainStringNum));

	//�ǂݍ��ݏ����֐�.
	m_pCFontResource->Load(m_stSpeakString[0]);

	//�ʐ^���菈���֐�.
	DecidePicture(EndingNum);

}

//==========================================.
//		�����������֐�.
//==========================================.
void CReputationSNS::Init()
{
	m_pCSpriteUI = m_pCResourceManager->GetSpriteUI(enSpriteUI::CursorSNS);
	m_vCursorPos = INIT_FONT_POS;

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

		if (m_fCursorAlpha >= ALPHA_MAX) {
			m_fCursorAlpha = 0.0f;
			return;
		}
		
		m_fCursorAlpha = ALPHA_MAX;
	}
}

//==========================================.
//		�J�[�\���`�揈���֐�.
//==========================================.
void CReputationSNS::RenderCursor()
{
	//���W.
	m_pCSpriteUI->SetPosition(m_vCursorPos);
	//���ߒl.
	m_pCSpriteUI->SetAlpha(m_fCursorAlpha);
	//�`��.
	m_pCSpriteUI->Render();
}

//==========================================.
//		�J�[�\���ړ������֐�.
//==========================================.
void CReputationSNS::MoveCursor()
{
	if (m_ChangingFontNum < m_pCFontResource->GetStrLength()) {
		m_vCursorPos = m_pCFontResource->GetFontPos(m_ChangingFontNum);
		m_vCursorPos.y += ADJUSTMENT_HEIGHT;
		return;
	}

	//��Ԓ[�̍��W����ꕶ���������Ƃ���ɒu��.
	m_vCursorPos = m_pCFontResource->GetFontPos(m_ChangingFontNum - 1);
	m_vCursorPos.x += FONT_SCALE;

	m_vCursorPos.y += ADJUSTMENT_HEIGHT;

}

//===========================================.
//		�ʐ^���菈���֐�.
//===========================================.
void CReputationSNS::DecidePicture(const int& EndingType)
{
	//Sprite�ԍ�.
	const int SpriteNum = static_cast<int>(enSpriteUI::PictureSNSRest) + EndingType;

	m_pCPictureUI = m_pCResourceManager->GetSpriteUI(static_cast<enSpriteUI>(SpriteNum));
}

//============================================.
//		�ʐ^�`�揈���֐�.
//============================================.
void CReputationSNS::RenderPicture()
{
	m_pCPictureUI->SetPosition(D3DXVECTOR3(350.0f, 5.0f, 0.0f));
	m_pCPictureUI->SetAlpha(ALPHA_MAX);
	m_pCPictureUI->Render();
}