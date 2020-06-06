#include "CReputationSNS.h"

/***************************************
*		SNS�ł̕]���N���X.
*******************/
CReputationSNS::CReputationSNS()
	: m_pCSpriteUI			(nullptr)
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
	const int m_FileNum = static_cast<int>(CFileResource::enSpeakFileType::EndingSpeak);

	const CFileString::enStringType MainStringNum = CFileString::enStringType::MainString;
	m_stSpeakString.push_back(m_pCFileResource->GetSpeakString(m_FileNum, EndingNum, MainStringNum));


	m_pCFontResource->Load(m_stSpeakString[0]);

}

//==========================================.
//		�����������֐�.
//==========================================.
void CReputationSNS::Init()
{
	m_pCSpriteUI = m_pCResourceManager->GetSpriteUI(enSpriteUI::CursorSNS);
	m_vCursorPos = D3DXVECTOR3(50.0f, 250.0f, 0.0f);

	m_pCFontResource->SetStartPos(D3DXVECTOR3(50.0f, 250.0f, 0.0f));
	m_pCFontResource->SetFontScale(90.0f);
	m_pCFontResource->SetWidthMax(1000.0f);
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

	if (m_FlashingCursorCnt > 20) {
		
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
		m_vCursorPos.y += 15.0f;
		return;
	}

	m_vCursorPos = m_pCFontResource->GetFontPos(m_ChangingFontNum - 1);
	m_vCursorPos.x += 90.0f;
	m_vCursorPos.y += 15.0f;
}