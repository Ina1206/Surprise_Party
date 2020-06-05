#include "CWhiteScreenFade.h"

/******************************************
*		���X�N���[���t�F�[�h�N���X.
************/
CWhiteScreenFade::CWhiteScreenFade()
	: m_pCSpriteUI	(nullptr)
	, m_vPos		(0.0f, 0.0f, 0.0f)
	, m_fAlpha		(ALPHA_MAX)
{
	//�����������֐�.
	Init();
}

CWhiteScreenFade::~CWhiteScreenFade()
{
	//��������֐�.
	Release();
}

//=========================================.
//		�X�V��������.
//=========================================.
void CWhiteScreenFade::Update()
{

}

//=========================================.
//		�`�揈���֐�.
//=========================================.
void CWhiteScreenFade::Render()
{
	m_pCSpriteUI->SetPosition(m_vPos);
	m_pCSpriteUI->SetAlpha(m_fAlpha);
	m_pCSpriteUI->Render();
}

//=========================================.
//		�����������֐�.
//=========================================.
void CWhiteScreenFade::Init()
{
	m_pCSpriteUI = m_pCResourceManager->GetSpriteUI(enSpriteUI::WhiteScreen);
}

//=========================================.
//		��������֐�.
//=========================================.
void CWhiteScreenFade::Release()
{

}