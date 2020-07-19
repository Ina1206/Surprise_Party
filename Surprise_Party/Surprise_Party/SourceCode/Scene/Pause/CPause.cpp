#include "CPause.h"

/****************************************
*		一時停止クラス.
************/
CPause::CPause()
	: m_pCPauseUI	(nullptr)
{
	//初期化処理関数.
	Init();
}

CPause::~CPause()
{
	//解放処理関数.
	Release();
}

//========================================.
//		更新処理関数.
//========================================.
void CPause::UpDate()
{
	//更新処理関数.
	m_pCPauseUI->Update();

	m_bTitle = false;
	if (m_pCPauseUI->GetSelectFinishFlag() == true) {
		if (m_pCPauseUI->GetSelectNum() == 1) {
			m_bTitle = true;
		}
		m_bPauseFlag = false;
	}
}

//========================================.
//		描画処理関数.
//========================================.
void CPause::Render()
{
	//描画処理関数.
	m_pCPauseUI->Render();
}

//========================================.
//		初期化処理関数.
//========================================.
void CPause::Init()
{
	m_pCPauseUI.reset(new CPauseUI());
}

//========================================.
//		解放処理関数.
//========================================.
void CPause::Release()
{

}