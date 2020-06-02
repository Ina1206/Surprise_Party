#include "CEnding.h"

CEnding::CEnding()
	: m_pCEndingStageBase	(nullptr)
{
	//�����������֐�.
	Init();
}

CEnding::~CEnding()
{
	//��������֐�.
	Release();
}

//=================================.
//		�X�V�����֐�.
//=================================.
void CEnding::UpDate()
{
	m_pCEndingStageBase->Update();
}

//==================================.
//		�`�揈���֐�.
//==================================.
void CEnding::Render()
{
	m_pCEndingStageBase->RenderInitSetting(m_mProj);
	m_pCEndingStageBase->Render();
}

//==================================.
//		�����������֐�.
//==================================.
void CEnding::Init()
{
	m_vBackColor = D3DXVECTOR4(1.0f, 0.5f, 0.0f, 1.0f);

	m_pCEndingStageBase.reset(new CBeforeResultStage());
}

//==================================.
//		��������֐�.
//==================================.
void CEnding::Release()
{

}