#include "CEndingStageBase.h"

/*******************************************
*		エンディングステージ基底クラス.
*****************/
CEndingStageBase::CEndingStageBase()
	: m_mView				()
	, m_mProj				()
	, m_Camera				()
	, m_pCBigGhost			(nullptr)
	, m_pCBackstageLight	(nullptr)
	, m_pCFloor				(nullptr)
{
	//共通の値の初期化処理関数.
	InitCommonValue();
}

CEndingStageBase::~CEndingStageBase()
{

}

//=========================================.
//		描画初期化処理関数.
//=========================================.
void CEndingStageBase::RenderInitSetting(const D3DXMATRIX& mView, const D3DXMATRIX& mProj)
{
	m_mView = mView;
	m_mProj = mProj;
}

//=========================================.
//		床の描画処理関数.
//=========================================.
void CEndingStageBase::RenderFloor()
{
	//ライト情報.
	const LIGHT m_Light = m_pCBackstageLight->GetLight();

	m_pCFloor->SetScale(0.5f);
	m_pCFloor->SetCameraPos(m_Camera.vPos);
	m_pCFloor->RenderInitSetting(m_mView, m_mProj, m_Light);
	m_pCFloor->SetPos(D3DXVECTOR3(0.0f, -6.0f, 0.0f));
	m_pCFloor->Render();

}

//=========================================.
//		ビッグゴースト描画処理関数.
//=========================================.
void CEndingStageBase::RenderBigGhost()
{
	//ライト情報.
	const LIGHT m_Light = m_pCBackstageLight->GetLight();

	m_pCBigGhost->SetCameraPos(m_Camera.vPos);
	m_pCBigGhost->RenderInitSetting(m_mView, m_mProj, m_Light);
	m_pCBigGhost->Render();
}

//=========================================.
//		共通値の初期化処理関数.
//=========================================.
void CEndingStageBase::InitCommonValue()
{
	//インスタンス化.
	m_pCBigGhost.reset(new CBigGhost());
	m_pCFloor.reset(new CFloor());
	m_pCBackstageLight.reset(new CBackstageLight());
}