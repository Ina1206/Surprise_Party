#include "CPuaseUI.h"

/**************************************
*		ポーズUIのクラス.
****************/
CPauseUI::CPauseUI()
{
	//初期化処理関数.
	Init();
}

CPauseUI::~CPauseUI()
{

}

//=====================================.
//		更新処理関数.
//=====================================.
void CPauseUI::Update()
{
	//カーソルの更新処理関数.
	m_pCCursor->SetChangeWaitFlag(true);
	m_pCCursor->SetControlFlag(true);
	m_pCCursor->Update();

	//選択肢の更新処理関数.
	m_pCSelectStringUI->SetMoveFlag(m_pCSelectStringUI->CONTROL_FLAG);
	m_pCSelectStringUI->Update();
}

//=====================================.
//		初期化処理関数.
//=====================================.
void CPauseUI::Init()
{
	//シーンタイトル.
	m_pCSpriteUI = m_pCResourceManager->GetSpriteUI(enSpriteUI::Pause);

	//選択肢UIクラスインスタンス化.
	m_pCSelectStringUI.reset(new CSelectStringUI(false));
}

//====================================.
//		シーンタイトル描画処理関数.
//====================================.
void CPauseUI::RenderSceneTitle()
{
	m_pCSpriteUI->SetPosition(PAUSE_POS);
	m_pCSpriteUI->Render();
}