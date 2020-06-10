#include "CEndingStageBase.h"

/*******************************************
*		エンディングステージ基底クラス.
*****************/
CEndingStageBase::CEndingStageBase()
	: m_mView					()
	, m_mProj					()
	, m_pCBackstageLight		(nullptr)
	, m_pCBigGhost				(nullptr)
	, m_pCGhost					(0)
	, m_pCCameraEnding			(nullptr)
	, m_pCWhiteScreenFade		(nullptr)
	, m_pCFloor					(nullptr)
	, m_vObjLookPos				(0.0f, 0.0f, 0.0f)
	, m_Evaluation				(0)
	, m_OldEvaluation			(INIT_EVALUATION_NUM)
	, m_bChangeStage			(false)
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
		&m_pCCameraEnding->GetPos(), &m_pCCameraEnding->GetLook(), &vUpVec);
}

//=========================================.
//		床の描画処理関数.
//=========================================.
void CEndingStageBase::RenderFloor()
{
	//ライト情報.
	const LIGHT m_Light = m_pCBackstageLight->GetLight();

	m_pCFloor->SetScale(0.5f);
	m_pCFloor->SetCameraPos(m_pCCameraEnding->GetPos());
	m_pCFloor->RenderInitSetting(m_mView, m_mProj, m_Light);
	m_pCFloor->SetPos(D3DXVECTOR3(0.0f, -6.0f, 0.0f));
	m_pCFloor->Render();

}

//=========================================.
//		お化け描画処理関数.
//=========================================.
void CEndingStageBase::RenderGhost()
{
	//ライト情報.
	const LIGHT m_Light = m_pCBackstageLight->GetLight();

	for (unsigned int ghost = 0; ghost < m_pCGhost.size(); ghost++) {
		m_pCGhost[ghost]->RenderInitSetting(m_mView, m_mProj, m_Light);
		m_pCGhost[ghost]->SetCameraPos(m_pCCameraEnding->GetPos());
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
	m_pCCameraEnding.reset(new CCameraEnding());
	m_pCWhiteScreenFade.reset(new CWhiteScreenFade());

	m_vObjLookPos = D3DXVECTOR3(5.0f, 1.5f, 5.0f);

	for (int ghost = 0; ghost < 5; ghost++) {
		//クラスからインスタンスを作成する処理関数.
		CreateInstanceFronClass(ghost);

		const float			RADIAN	= static_cast<float>(D3DXToRadian(122.5f + (ghost * 55.0f)));
		const D3DXVECTOR3	vPos	= (D3DXVECTOR3(cos(RADIAN), 0.0f, sin(RADIAN)) * 2.5f) + D3DXVECTOR3(5.0f, 1.5f + ((ghost % 2) * 0.5f), 5.0f);

		m_pCGhost[ghost]->SetPos(vPos);

		//感情番号.
		const int m_EmotionType = static_cast<int>(CGhostBase::enEmotionType::ViewSmartphone);
		m_pCGhost[ghost]->SetEmotionNum(m_EmotionType);

		m_pCGhost[ghost]->SetLookAtPos(m_vObjLookPos);
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

	if (num % 2 == 0) {
		m_pCGhost.emplace_back(new CEndingDispGhost());
		return;
	}
	m_pCGhost.emplace_back(new CEndingSwitchGhost());
	
}