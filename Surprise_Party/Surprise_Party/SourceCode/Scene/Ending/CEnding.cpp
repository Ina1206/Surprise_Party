#include "CEnding.h"

CEnding::CEnding()
	: m_pCEndingStageBase	(nullptr)
{
	//‰Šú‰»ˆ—ŠÖ”.
	Init();
}

CEnding::~CEnding()
{
	//‰ğ•úˆ—ŠÖ”.
	Release();
}

//=================================.
//		XVˆ—ŠÖ”.
//=================================.
void CEnding::UpDate()
{
	m_pCEndingStageBase->Update();
}

//==================================.
//		•`‰æˆ—ŠÖ”.
//==================================.
void CEnding::Render()
{
	m_pCEndingStageBase->RenderInitSetting(m_mProj);
	m_pCEndingStageBase->Render();
}

//==================================.
//		‰Šú‰»ˆ—ŠÖ”.
//==================================.
void CEnding::Init()
{
	m_vBackColor = D3DXVECTOR4(1.0f, 0.5f, 0.0f, 1.0f);

	m_pCEndingStageBase.reset(new CBeforeResultStage());
}

//==================================.
//		‰ğ•úˆ—ŠÖ”.
//==================================.
void CEnding::Release()
{

}