#include "CTutorial.h"

CTutorial::CTutorial()
{
	//‰Šú‰»ˆ—ŠÖ”.
	Init();
}

CTutorial::~CTutorial()
{
	//‰ğ•úˆ—ŠÖ”.
	Release();
}

//===========================================.
//		XVˆ—ŠÖ”.
//===========================================.
void CTutorial::UpDate(const bool& ControlFlag)
{
	if (GetAsyncKeyState('Q') & 0x8000) {
		m_TutorialFlag = TUTORIAL_FINISH;
	}
}

//===========================================.
//		•`‰æˆ—ŠÖ”.
//===========================================.
void CTutorial::Render()
{

}

//===========================================.
//		‰Šú‰»ˆ—ŠÖ”.
//===========================================.
void CTutorial::Init()
{
	//m_vBackColor = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);
	m_TutorialFlag = TUTORIAL_START;
}

//===========================================.
//		‰ğ•úˆ—ŠÖ”.
//===========================================.
void CTutorial::Release()
{

}

//===========================================.
//		‘€ìˆ—ŠÖ”.
//===========================================.
void CTutorial::Control()
{

}