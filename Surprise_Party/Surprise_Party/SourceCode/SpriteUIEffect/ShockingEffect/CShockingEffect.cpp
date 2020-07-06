#include"CShockingEffect.h"

/*************************************
*		�Ռ��G�t�F�N�g�N���X.
****************/
CShockingEffect::CShockingEffect()
	: m_pCSpriteUI	(nullptr)
	, m_vPos		(0.0f, 0.0f, 0.0f)
	, m_fAlpha		(ALPHA_MAX)
	, m_fScale		(SCALE_MAX)
{
	//�����������֐�.
	Init();
}

CShockingEffect::~CShockingEffect()
{

}

//=====================================.
//		�X�V�����֐�.
//=====================================.
void CShockingEffect::Update()
{
	m_vPos = m_vCenterPos;
}

//=====================================.
//		�`�揈���֐�.
//=====================================.
void CShockingEffect::Render()
{
	m_pCSpriteUI->SetPosition(m_vPos);
	m_pCSpriteUI->SetAlpha(m_fAlpha);
	m_pCSpriteUI->SetScale(m_fScale);
	m_pCDepthStencil->SetDepth(false);
	m_pCSpriteUI->Render();
	m_pCDepthStencil->SetDepth(true);
}

//======================================.
//		�����������֐�.
//======================================.
void CShockingEffect::Init()
{
	m_pCSpriteUI = m_pCResourceManager->GetSpriteUI(enSpriteUI::ShockingSign);
}