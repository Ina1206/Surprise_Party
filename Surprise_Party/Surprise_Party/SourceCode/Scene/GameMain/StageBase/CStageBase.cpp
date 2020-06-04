#include "CStageBase.h"

CStageBase::CStageBase()
	: m_mView			()
	, m_mProj			()
	, m_Camera			()
	, m_bChangeStageFlag(false)
	, m_StageNum		(0)
	, m_enBeforeStageEndingType()
	, m_FinishFlag		(0)
	, m_TutorialFlag	(false)
	, m_pCCamera		(nullptr)
{

}

CStageBase::~CStageBase()
{

}

//==========================================.
//		描画初期設定処理関数.
//==========================================.
void CStageBase::RenderInitSetting(const D3DXMATRIX& mView, const D3DXMATRIX& mProj, const D3DXVECTOR3& vCameraPos)
{
	m_mView			= mView;
	m_mProj			= mProj;
	//m_vCameraPos	= vCameraPos;
	const D3DXVECTOR3 m_vCameraLook = m_pCCamera->GetLook();
	const D3DXVECTOR3 m_vCameraPos = m_pCCamera->GetPos();

	D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);	//上方(ベクトル).
	D3DXMatrixLookAtLH(
		&m_mView,								//(out)ビュー計算結果.
		&m_vCameraPos, &m_vCameraLook, &vUpVec);
}

//==========================================.
//		デバッグ用ステージ変更処理関数.
//==========================================.
void CStageBase::DebugStageChange()
{
	if (GetAsyncKeyState(VK_SPACE) & 0x0001) {
		m_bChangeStageFlag = true;
	}
}