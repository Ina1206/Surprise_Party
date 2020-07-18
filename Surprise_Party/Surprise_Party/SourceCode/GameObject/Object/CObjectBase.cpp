#include "CObjectBase.h"

/********************************************
*		オブジェクト基底クラス.
******************/
CObjectBase::CObjectBase()
	: m_pCMesh				(nullptr)
	, m_pCDepthStenceil		(nullptr)
	, m_fAlpha				(1.0f)
{
	m_pCDepthStenceil = CDepth_Stencil::GetDepthStencilInstance();
}

CObjectBase::~CObjectBase()
{
	m_pCDepthStenceil = nullptr;
}

//==============================================.
//		描画処理関数.
//==============================================.
void CObjectBase::Render()
{
	//座標設定.
	m_pCMesh->SetPosition(m_vPos);
	//角度設定.
	m_pCMesh->SetRotation(m_vRot);
	//大きさ設定.
	m_pCMesh->SetScale(m_fScale);
	//透過値を設定.
	m_pCMesh->SetAlpha(m_fAlpha);
	//描画処理関数.
	m_pCMesh->SetAlphaDepth(true);
	m_pCMesh->Render(m_mView, m_mProj, m_vCameraPos, m_stLight);
	m_pCMesh->SetAlphaDepth(false);
}