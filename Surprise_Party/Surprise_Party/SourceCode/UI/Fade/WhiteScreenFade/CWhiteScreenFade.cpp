#include "CWhiteScreenFade.h"

/******************************************
*		���X�N���[���t�F�[�h�N���X.
************/
CWhiteScreenFade::CWhiteScreenFade()
	: m_pCSpriteUI	(nullptr)
	, m_vPos		(0.0f, 0.0f, 0.0f)
	, m_fAlpha		(ALPHA_MAX)
	, m_FadeFlag	(0)
	, m_OldFadeFlag	(0)
	, m_fAlphaRatio	(0.0f)
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
	if (m_FadeFlag != m_OldFadeFlag) {
		//�t�F�[�h�O�̏����������֐�.
		InitFade();
	}

	m_OldFadeFlag = m_FadeFlag;

	if (m_FadeFlag & FADE_IN_FLAG) {
		//�t�F�[�h�C�������֐�.
		FadeIn();
		return;
	}

	//�t�F�[�h�A�E�g�����֐�.
	FadeOut();
}

//=========================================.
//		�`�揈���֐�.
//=========================================.
void CWhiteScreenFade::Render()
{
	//�`���O����.
	if (m_FadeFlag == 0) {
		return;
	}

	m_pCSpriteUI->SetPosition(m_vPos);
	m_pCSpriteUI->SetAlpha(m_fAlpha);
	CDepth_Stencil* m_pCDepthStencil = CDepth_Stencil::GetDepthStencilInstance();
	m_pCDepthStencil->SetDepth(false);
	m_pCSpriteUI->Render();
	m_pCDepthStencil->SetDepth(true);
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

//=========================================.
//		�t�F�[�h�C�������֐�.
//=========================================.
void CWhiteScreenFade::FadeIn()
{
	m_fAlpha += ALPHA_SPEED;
	//���ߒl�̊���.
	const float ALPHA_LENGTH = fabsf(ALPHA_MIN - ALPHA_MAX);
	m_fAlphaRatio = fabsf(m_fAlpha - ALPHA_MAX) / ALPHA_LENGTH;

	if (m_fAlpha > ALPHA_MAX) {
		m_fAlpha = ALPHA_MAX;
		m_FadeFlag = FADE_FINISH_FLAG;
	}
}

//===========================================.
//		�t�F�[�h�A�E�g�����֐�.
//===========================================.
void CWhiteScreenFade::FadeOut()
{
	m_fAlpha -= ALPHA_SPEED;
	//���ߒl�̊���.
	const float ALPHA_LENGTH = fabsf(ALPHA_MIN - ALPHA_MAX);
	m_fAlphaRatio = ALPHA_MAX - fabsf(m_fAlpha - ALPHA_MIN) / ALPHA_LENGTH;

	if (m_fAlpha < ALPHA_MIN) {
		m_fAlpha = ALPHA_MIN;
		m_FadeFlag = FADE_FINISH_FLAG;
	}
}

//===========================================.
//		�t�F�[�h�O�̏����������֐�.
//===========================================.
void CWhiteScreenFade::InitFade()
{
	if (m_FadeFlag & FADE_IN_FLAG) {
		m_fAlpha = ALPHA_MIN;
		return;
	}

	m_fAlpha = ALPHA_MAX;
}