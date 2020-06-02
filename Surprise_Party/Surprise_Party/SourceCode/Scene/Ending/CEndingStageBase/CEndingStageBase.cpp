#include "CEndingStageBase.h"

/*******************************************
*		エンディングステージ基底クラス.
*****************/
CEndingStageBase::CEndingStageBase()
	: m_mView					()
	, m_mProj					()
	, m_Camera					()
	, m_pCBackstageLight		(nullptr)
	, m_pCBigGhost				(nullptr)
	, m_pCEndingWorkGhostBase	(0)
	, m_pCGhost					(0)
	, m_pCFloor					(nullptr)
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
void CEndingStageBase::RenderInitSetting( const D3DXMATRIX& mProj)
{
	m_mProj = mProj;

	D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);	//上方(ベクトル).
	D3DXMatrixLookAtLH(
		&m_mView,								//(out)ビュー計算結果.
		&m_Camera.vPos, &m_Camera.vLook, &vUpVec);
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
//		働くお化け描画処理関数.
//=========================================.
void CEndingStageBase::RenderWorkGhost()
{
	//ライト情報.
	const LIGHT m_Light = m_pCBackstageLight->GetLight();

	for (unsigned int ghost = 0; ghost < m_pCEndingWorkGhostBase.size(); ghost++) {
		m_pCEndingWorkGhostBase[ghost]->RenderInitSetting(m_mView, m_mProj, m_Light);
	}
}

//=========================================.
//		お化け描画処理関数.
//=========================================.
void CEndingStageBase::RenderGhost()
{
	//ライト情報.
	const LIGHT m_Light = m_pCBackstageLight->GetLight();

	for (unsigned int ghost = 0; ghost < m_pCEndingWorkGhostBase.size(); ghost++) {
		m_pCGhost[ghost]->RenderInitSetting(m_mView, m_mProj, m_Light);
		m_pCGhost[ghost]->SetCameraPos(m_Camera.vPos);
		m_pCGhost[ghost]->Render();
	}
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

	for (int ghost = 0; ghost < 5; ghost++) {
		m_pCEndingWorkGhostBase.emplace_back(new CEndingDispGhost());
	}
	for (int ghost = 0; ghost < 5; ghost++) {
		//クラスからインスタンスを作成する処理関数.
		CreateInstanceFronClass(ghost);

		const float			RADIAN	= static_cast<float>(D3DXToRadian(-57.5 + (ghost * 50.0f)));
		const D3DXVECTOR3	vPos	= (D3DXVECTOR3(cos(RADIAN), 0.0f, sin(RADIAN)) * 3.0f) + D3DXVECTOR3(5.0f, -0.8f, 5.0f);
		m_pCGhost[ghost]->SetPos(vPos);

		//感情番号.
		const int m_EmotionType = static_cast<int>(CGhostBase::enEmotionType::ViewSmartphone);
		m_pCGhost[ghost]->SetEmotionNum(m_EmotionType);
	}
}

//==========================================.
//	クラスからインスタンスを作成する処理関数.
//==========================================.
void CEndingStageBase::CreateInstanceFronClass(const int& num)
{
	if (num == 2) {
		m_pCGhost.emplace_back(new CBigGhost());
		return;
	}
	m_pCGhost.emplace_back(new CEndingDispGhost());
}