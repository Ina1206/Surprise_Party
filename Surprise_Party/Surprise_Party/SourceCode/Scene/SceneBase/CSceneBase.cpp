#include "CSceneBase.h"

CSceneBase::CSceneBase()
	: m_mView		()
	, m_mProj		()
	, m_vLightPos	(0.0f, 0.0f, 0.0f)
	, m_vCameraPos	(0.0f, 0.0f, 0.0f)
	, m_vBackColor	(0.0f, 0.0f, 0.0f, 0.0f)
	, m_bChangeScene(false)
	, m_bPauseFlag	(false)
{

}

CSceneBase::~CSceneBase()
{

}

//===========================================.
//		描画初期設定処理関数.
//===========================================.
void CSceneBase::RenderInitSetting(const D3DXMATRIX& mView, const D3DXMATRIX& mProj, const D3DXVECTOR3& vLightPos, const D3DXVECTOR3& vCameraPos)
{
	m_mView			= mView;
	m_mProj			= mProj;
	m_vLightPos		= vLightPos;
	m_vCameraPos	= vCameraPos;
}

//===========================================.
//		デバッグ用シーン変更処理関数.
//===========================================.
void CSceneBase::DebugSceneChange()
{
	if (GetAsyncKeyState('A') & 0x8000) {
		m_bChangeScene = true;
	}
}