#include "CPeopleBase.h"

CPeopleBase::CPeopleBase()
	: m_pCSkinMesh		(nullptr)
	, m_fAnimSpeed		(0.0f)
	, m_fWalkAnimSpeed	(0.0f)
	, m_fStageMax		(0.0f)
	, m_fMoveSpeed		(0.0f)
	, m_SurpriseQuantity(0)
	, m_pAnimCtrl		(nullptr)
	, m_bSurpriseFlag	(false)
	, m_AnimNo			(0)
	, m_WalkAnimNo		(0)
	, m_SurpriseActFlag	(0)
	, m_pCSurpriseEffect(nullptr)
	, m_vEffectCenterPos(0.0f, 0.0f, 0.0f)
	, m_AnimTime		(0.0)
	, m_HumanNearNum	(FAR_NUM)
	, m_SurpriseHumanMax(0)
	, m_bTutorialFlag	(false)
{
	m_vRot = PERSON_ROT;
}

CPeopleBase::~CPeopleBase()
{
	if (m_pAnimCtrl != nullptr) {
		m_pAnimCtrl->Release();
		m_pAnimCtrl = nullptr;
	}
}

//======================================.
//		描画処理関数.
//======================================.
void CPeopleBase::Render()
{
	if (m_bTutorialFlag == true) {
		m_pCSkinMesh->ChangeAnimSet(TUTORIAL_ANIM_NO, m_pAnimCtrl);
		m_bTutorialFlag = false;
	}

	//座標.
	m_pCSkinMesh->SetPosition(m_vPos);
	//角度.
	m_pCSkinMesh->SetRotation(m_vRot);
	//大きさ.
	m_pCSkinMesh->SetScale(m_fScale);
	//アニメーション速度.
	if (m_AnimNo == m_WalkAnimNo) {
		m_pCSkinMesh->SetAnimSpeed(m_fWalkAnimSpeed);
	}
	else {
		m_pCSkinMesh->SetAnimSpeed(m_fAnimSpeed);
	}
	//描画.
	m_pCSkinMesh->SetAlphaDepth(true);
	m_pCSkinMesh->Render(m_mView, m_mProj, m_vCameraPos, m_stLight, m_pAnimCtrl);
	m_pCSkinMesh->SetAlphaDepth(false);

	//エフェクトの描画.
	m_pCSurpriseEffect->SetCenterPos(m_vEffectCenterPos);
	m_pCSurpriseEffect->Render(m_mView, m_mProj, m_vCameraPos);
}

//======================================.
//		追加ポイント量獲得処理関数.
//======================================.
int CPeopleBase::GetAddPointQuantity(int NearNo)
{
	//驚き行動しているときにはポイントは加算しない.
	if (m_bSurpriseFlag == true) {
		return 0;
	}

	int m_AddPointQuantity;	//追加ポイント量.
	m_AddPointQuantity = m_SurpriseQuantity - (NearNo * DECREMENT_POINT);

	if (m_AddPointQuantity < 0) {
		return 0;
	}

	return m_AddPointQuantity;
}

//======================================.
//		表示判定処理関数.
//======================================.
void CPeopleBase::DispDecision()
{
	if (m_vPos.x > m_fStageMax) {
		m_bDisp = false;
	}
}

//=======================================.
//	アニメーションコントローラ作成処理関数.
//=======================================.
void CPeopleBase::AnimCtrlCreat() 
{
	LPD3DXANIMATIONCONTROLLER pAC = m_pCSkinMesh->GetAnimationController();

	if (FAILED(pAC->CloneAnimationController(
		pAC->GetMaxNumAnimationOutputs(),
		pAC->GetMaxNumAnimationSets(),
		pAC->GetMaxNumTracks(),
		pAC->GetMaxNumEvents(),
		&m_pAnimCtrl))) {
		_ASSERT_EXPR(false, L"アニメーションコントローラのクローン作成失敗");
	}
}

//========================================.
//		人の移動処理関数.
//========================================.
void CPeopleBase::HumanMove()
{
	if (m_AnimNo == m_WalkAnimNo) {
		m_vPos.x += m_fMoveSpeed;
	}

}

//========================================.
//		驚きアニメーション変更処理関数.
//========================================.
void CPeopleBase::SurpriseAnimChange(int surpriseAnimNo)
{
	if (m_SurpriseActFlag != 0) {
		//驚く行動終了処理.
		if (m_bSurpriseFlag == false) {
			m_SurpriseActFlag &= ~SURPRISE_ACT;
			return;
		}
	}

	//驚きアニメーション変更処理.
	if ( m_bSurpriseFlag == true && m_SurpriseActFlag == 0) {
		m_AnimNo = surpriseAnimNo;
		m_pCSkinMesh->ChangeAnimSet(m_AnimNo, m_pAnimCtrl);
		m_AnimTime = 0.0;
		m_SurpriseActFlag = SURPRISE_ACT;

		//驚きエフェクト開始.
		m_pCSurpriseEffect->SetDispFlag(true);
	}

	if (m_SurpriseActFlag & SURPRISE_ACT) {
		//歩きアニメーション変更.
		if (m_pCSkinMesh->GetAnimPeriod(m_AnimNo) - m_pCSkinMesh->GetAnimSpeed() <= m_AnimTime) {
			m_AnimNo = m_WalkAnimNo;
			m_pCSkinMesh->ChangeAnimSet(m_AnimNo, m_pAnimCtrl);
			m_AnimTime = 0.0;
			m_bSurpriseFlag = false;

			//速度加速処理関数.
			SpeedAcceleration();
			return;
		}
	}

	m_AnimTime += m_pCSkinMesh->GetAnimSpeed();
}

//===========================================.
//		速度加速処理関数.
//===========================================.
void CPeopleBase::SpeedAcceleration()
{
	//驚いた順番によって移動速度とアニメーション速度の追加計算.
	m_fMoveSpeed += (m_SurpriseHumanMax - m_HumanNearNum) * ACCELERATION_SPEED;
	m_fWalkAnimSpeed += (m_SurpriseHumanMax - m_HumanNearNum) * ADD_ANIM_SPEED;

	//遠くに人がいる番号に戻す.
	m_HumanNearNum = FAR_NUM;
}
