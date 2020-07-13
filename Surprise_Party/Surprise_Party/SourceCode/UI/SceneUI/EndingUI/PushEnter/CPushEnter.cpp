#include "CPushEnter.h"

/********************************************
*		PushEnter�N���X.
***********************/
CPushEnter::CPushEnter()
	: m_pCSpriteUI		(nullptr)
	, m_AlphaAddDirect	(1)
{
	//�����������֐�.
	Init();
}

CPushEnter::~CPushEnter()
{
	//��������֐�.
	Release();
}

//============================================.
//		�X�V�����֐�.
//============================================.
void CPushEnter::Update()
{
	m_fAlpha += TRANSPARENT_SPEED * m_AlphaAddDirect;

	//�ő�l�ȏ�̏���.
	if (m_fAlpha > ALPHA_MAX) {
		m_fAlpha = ALPHA_MAX;
		m_AlphaAddDirect *= CHANGE_ALPHA_ADD_DIRECT;
		return;
	}

	//�ŏ��l�ȉ��̏���.
	if (m_fAlpha < ALPHA_MIN) {
		m_fAlpha = ALPHA_MIN;
		m_AlphaAddDirect *= CHANGE_ALPHA_ADD_DIRECT;
	}

}

//============================================.
//		�`�揈���֐�.
//============================================.
void CPushEnter::Render()
{
	//���ߒl.
	m_pCSpriteUI->SetAlpha(m_fAlpha);
	//�傫��.
	m_pCSpriteUI->SetScale(SCALE_MAX);
	//���W.
	m_pCSpriteUI->SetPosition(POS);
	//�`��.
	m_pCDepthStencil->SetDepth(false);
	m_pCSpriteUI->Render();
	m_pCDepthStencil->SetDepth(true);
}

//============================================.
//		�����������֐�.
//============================================.
void CPushEnter::Init()
{
	m_pCSpriteUI = m_pCResourceManager->GetSpriteUI(enSpriteUI::PushEnterString);
	m_fAlpha = ALPHA_MIN;
}

//============================================.
//		��������֐�.						  
//============================================.
void CPushEnter::Release()
{

}