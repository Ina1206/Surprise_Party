#include "CGameObject.h"

/************************************
*	ゲームオブジェクトクラス.
*******/
CGameObject::CGameObject()
	: m_mView		()
	, m_mProj		()
	, m_stLight		()
	, m_vCameraPos	(0.0f, 0.0f, 0.0f)
	, m_vPos		(STANDERD_POS)
	, m_vRot		(0.0f, 0.0f, 0.0f)
	, m_fScale		(1.0f)
	, m_bDisp		(false)
	, m_pCResourceManager(nullptr)
{
	m_pCResourceManager = CResourceManager::GetResourceManagerInstance();
}

CGameObject::~CGameObject()
{

}

//==========================================.
//		描画初期設定処理関数.
//==========================================.
void CGameObject::RenderInitSetting(const D3DXMATRIX& mView, const D3DXMATRIX& mProj, const LIGHT& stLight)
{
	m_mView = mView;
	m_mProj = mProj;
	m_stLight = stLight;
}