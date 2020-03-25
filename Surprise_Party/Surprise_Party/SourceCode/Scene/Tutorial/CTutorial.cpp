#include "CTutorial.h"

CTutorial::CTutorial()
{
	//初期化処理関数.
	Init();
}

CTutorial::~CTutorial()
{
	//解放処理関数.
	Release();
}

//===========================================.
//		更新処理関数.
//===========================================.
void CTutorial::UpDate(const bool& ControlFlag)
{
	if (GetAsyncKeyState('Q') & 0x8000) {
		m_TutorialFlag = TUTORIAL_FINISH;
	}
}

//===========================================.
//		描画処理関数.
//===========================================.
void CTutorial::Render()
{

}

//===========================================.
//		初期化処理関数.
//===========================================.
void CTutorial::Init()
{
	//m_vBackColor = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);
	m_TutorialFlag = TUTORIAL_START;
}

//===========================================.
//		解放処理関数.
//===========================================.
void CTutorial::Release()
{

}

//===========================================.
//		操作処理関数.
//===========================================.
void CTutorial::Control()
{

}