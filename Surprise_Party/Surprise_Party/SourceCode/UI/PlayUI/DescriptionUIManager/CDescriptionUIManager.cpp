#include "CDescriptionUIManager.h"

/*****************************************
*		説明UI管理クラス.
**************/
CDescriptionUIManager::CDescriptionUIManager()
	: m_pCArrow(nullptr)
	, m_pCTutorialBlackScreen(nullptr)
{
	//初期化処理関数.
	Init();
}

CDescriptionUIManager::~CDescriptionUIManager()
{
	//解放処理関数.
	Release();
}

//==========================================.
//		更新処理関数.
//==========================================.
void CDescriptionUIManager::Update()
{
	//矢印の向き設定.
	m_pCArrow->SetUsingArrowFlag(m_pCArrow->USING_LEFT_FLAG);
	const D3DXVECTOR3 vCenterPos = D3DXVECTOR3(m_vCenterPos.x + 500.0f, m_vCenterPos.y - 30.0f, m_vCenterPos.z);
	m_pCArrow->SetCenterPos(vCenterPos);
	
	
	m_pCArrow->SetUsingArrowFlag(m_pCArrow->USING_RIGHT_FLAG);
	const D3DXVECTOR3 vCenterPos = D3DXVECTOR3(m_vCenterPos.x - 100.0f, m_vCenterPos.y, m_vCenterPos.z);
	m_pCArrow->SetCenterPos(vCenterPos);

	
	m_pCArrow->Update();

	m_pCTutorialBlackScreen->SetCenterPos(m_vCenterPos);
	m_pCTutorialBlackScreen->Update();

}

//==========================================.
//		描画処理関数.
//==========================================.
void CDescriptionUIManager::Render()
{
	m_pCTutorialBlackScreen->Render();

	m_pCArrow->Render();

}

//===========================================.
//		初期化処理関数.
//===========================================.
void CDescriptionUIManager::Init()
{
	m_pCArrow.reset(new CArrow());
	m_pCTutorialBlackScreen.reset(new CTutorialBlackScreen());

}

//===========================================.
//		解放処理関数.
//===========================================.
void CDescriptionUIManager::Release()
{

}