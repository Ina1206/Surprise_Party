#include "CAutoUI.h"

/**********************************
*		�����Đ�����UI�N���X.
************/
CAutoUI::CAutoUI()
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

}

//=================================.
//		�`�揈���֐�.
//=================================.
void CAutoUI::Render()
{
	m_pCSpriteUI->SetAlpha(m_fAlpha);
	m_pCSpriteUI->SetPosition(m_vPos);
	m_pCSpriteUI->Render();
}

//=================================.
//		�����������֐�.
//=================================.
void CAutoUI::Init()
{
	m_pCSpriteUI = m_pCResourceManager->GetSpriteUI(enSpriteUI::AutoString);
	m_vPos = D3DXVECTOR3(500.0f, 200.0f, 0.0f);
}

//=================================.
//		��������֐�.
//=================================.
void CAutoUI::Release()
{

}