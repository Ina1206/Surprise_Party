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

	m_pCDepthStencil->SetDepth(true);
	
}

//==========================================.
//		�����������֐�.
//==========================================.
void CReputationSNS::Init()
{
	m_pCSpriteUI = m_pCResourceManager->GetSpriteUI(enSpriteUI::CursorSNS);
	m_vCursorPos = D3DXVECTOR3(50.0f, 250.0f, 0.0f);
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
	m_FlashingCursorCnt++;

	if (m_FlashingCursorCnt > 30) {
		
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