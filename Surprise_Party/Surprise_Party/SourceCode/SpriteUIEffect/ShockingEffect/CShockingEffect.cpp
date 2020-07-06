#include"CShockingEffect.h"

/*************************************
*		�Ռ��G�t�F�N�g�N���X.
****************/
CShockingEffect::CShockingEffect()
	: m_pCSpriteUI	(nullptr)
	, m_vPos		(0.0f, 0.0f, 0.0f)
	, m_fScale		(SCALE_MAX)
	, m_bDispFlag	(false)
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
	m_vPos.y -= SIGN_DISP_HIGHT;

	if (m_bDispFlag == false) {
		m_bDispFlag = true;
		return;
	}
}

//=====================================.
//		�`�揈���֐�.
//=====================================.
void CShockingEffect::Render()
{
	m_pCSpriteUI->SetPosition(m_vPos);
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