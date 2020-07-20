#include "CMapUI.h"

/******************************************
*		�}�b�vUI�N���X.
**********/
CMapUI::CMapUI()
	: m_pCSpriteUI	(nullptr)
	, m_vColor		(1.0f, 1.0f, 1.0f)
	, m_vPattarn	(0.0f, 0.0f)
{

}

CMapUI::~CMapUI()
{

}

//============================================.
//		�`�揈���֐�.
//============================================.
void CMapUI::Render()
{
	//���W.
	m_pCSpriteUI->SetPosition(m_vPos);
	//�p�x.
	m_pCSpriteUI->SetRotation(m_vRot);
	//�傫��.
	m_pCSpriteUI->SetScale(m_fScale);
	//���ߒl.
	m_pCSpriteUI->SetAlpha(m_fAlpha);
	//�F.
	m_pCSpriteUI->SetColor(m_vColor);
	//�p�^�[��.
	m_pCSpriteUI->SetPattern(m_vPattarn);
	//�`��.
	m_pCDepthStencil->SetDepth(false);
	m_pCSpriteUI->Render();
	m_pCDepthStencil->SetDepth(true);
}