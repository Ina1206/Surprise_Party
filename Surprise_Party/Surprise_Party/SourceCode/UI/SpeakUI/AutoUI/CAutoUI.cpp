#include "CAutoUI.h"

/**********************************
*		�����Đ�����UI�N���X.
************/
CAutoUI::CAutoUI()
	: m_pCSpriteUI			(nullptr)
	, m_FlashingFlag		(0)
	, m_TransparentDirect	(1)
{
	//�����������֐�.
	Init();
}

CAutoUI::~CAutoUI()
{
	//��������֐�.
	Release();
}

//=================================.
//		�X�V�����֐�.
//=================================.
void CAutoUI::Update()
{
	m_fAlpha += ALPHA_SPEED * m_TransparentDirect;

	//�����Ă��������̎�.
	if (m_FlashingFlag & DISAPPEAR_FLAG) {
		if (m_fAlpha < ALPHA_MIN) {
			m_fAlpha = ALPHA_MIN;
			m_FlashingFlag = APPEAR_FLAG;
			m_TransparentDirect *= CHANGE_DIRECT;
		}
		return;
	}

	//����鏈���̎�.
	if (m_fAlpha > ALPHA_MAX) {
		m_fAlpha = ALPHA_MAX;
		m_FlashingFlag = DISAPPEAR_FLAG;
		m_TransparentDirect *= CHANGE_DIRECT;
	}
}

//=================================.
//		�`�揈���֐�.
//=================================.
void CAutoUI::Render()
{
	//���ߒl.
	m_pCSpriteUI->SetAlpha(m_fAlpha);
	//���W.
	m_pCSpriteUI->SetPosition(POS);
	//�`��.
	m_pCDepthStencil->SetDepth(false);
	m_pCSpriteUI->Render();
	m_pCDepthStencil->SetDepth(true);
}

//=================================.
//		�����������֐�.
//=================================.
void CAutoUI::Init()
{
	m_pCSpriteUI = m_pCResourceManager->GetSpriteUI(enSpriteUI::AutoString);
	m_TransparentDirect *= CHANGE_DIRECT;
	m_FlashingFlag = DISAPPEAR_FLAG;
}

//=================================.
//		��������֐�.
//=================================.
void CAutoUI::Release()
{

}