#include "CEnding.h"

CEnding::CEnding()
	: m_pCEndingStageBase	(nullptr)
{
	//初期化処理関数.
	Init();
}

CEnding::~CEnding()
{
	//解放処理関数.
	Release();
}

//=================================.
//		更新処理関数.
//=================================.
void CEnding::UpDate()
{
	//評価置換処理関数.
	m_pCEndingStageBase->SetEvaluation(m_Evaluation);
	//更新処理関数.
	m_pCEndingStageBase->Update();
}

//==================================.
//		描画処理関数.
//==================================.
void CEnding::Render()
{
	m_pCEndingStageBase->RenderInitSetting(m_mProj);
	m_pCEndingStageBase->Render();
}

//==================================.
//		初期化処理関数.
//==================================.
void CEnding::Init()
{
	m_vBackColor = D3DXVECTOR4(0.0f, 0.0f, 0.0f ,1.0f);

	m_pCEndingStageBase.reset(new CBeforeResultStage());
}

//==================================.
//		解放処理関数.
//==================================.
void CEnding::Release()
{

}