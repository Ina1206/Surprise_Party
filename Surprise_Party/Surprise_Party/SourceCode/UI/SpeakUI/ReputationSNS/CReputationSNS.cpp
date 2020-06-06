#include "CReputationSNS.h"

/***************************************
*		SNS�ł̕]���N���X.
*******************/
CReputationSNS::CReputationSNS()
	: m_pCSpriteUI		(nullptr)
	, m_vCursorPos		(0.0f, 0.0f, 0.0f)
	, m_fCursorAlpha	(ALPHA_MAX)
	, m_stArticleDetail	()
	, m_EndingTypeNum	(0)
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