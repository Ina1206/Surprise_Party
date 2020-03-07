#include "CMoveObjectBase.h"

CMoveObjectBase::CMoveObjectBase()
	: m_pCEffect			(nullptr)
	, m_EffectHandle		(EFFECT_HANDLE_DEFAULT_VALUE)
	, m_bCameraDisp			(false)
	, m_vEffectPos			(0.0f, 0.0f, 0.0f)
	, m_fEffectScale		(1.5f)
	, m_pCAttachedObjMesh	()
	, m_vAttachedObjPos		()
	, m_vAttachedObjRot		()
{
	m_vEffectPos = D3DXVECTOR3(0.0f, 0.1f, -3.0f);
}

CMoveObjectBase::~CMoveObjectBase()
{

}

//===================================.
//		エフェクト描画処理関数.
//===================================.
void CMoveObjectBase::EffectRender()
{
	if (m_EffectHandle != EFFECT_HANDLE_DEFAULT_VALUE) {
		D3DXVECTOR3 vEffectScale = D3DXVECTOR3(m_fEffectScale, m_fEffectScale, m_fEffectScale);
		m_pCEffect->SetScale(m_EffectHandle, vEffectScale);
		m_pCEffect->Render(m_mView, m_mProj);
	}
}

//===================================.
//		当たり判定処理関数.
//===================================.
void CMoveObjectBase::Hit()
{

}

//===================================.
//		エフェクト更新処理関数.
//===================================.
void CMoveObjectBase::EffectUpDate()
{
	//エフェクトの座標設定.
	m_vEffectPos.x = m_vPos.x;

	if (m_bCameraDisp == true) {
		//エフェクト再生処理関数.
		EffectPlay();
		m_bCameraDisp = false;
		return;
	}

	//エフェクト停止処理関数.
	EffectStop();

}

//===================================.
//	付属オブジェクト描画処理関数.
//===================================.
void CMoveObjectBase::AttachedObjRender()
{
	for (unsigned int attached = 0; attached < m_pCAttachedObjMesh.size(); attached++) {
		if (m_pCAttachedObjMesh[attached] != nullptr) {
			m_pCAttachedObjMesh[attached]->SetRotation(m_vAttachedObjRot[attached]);
			m_pCAttachedObjMesh[attached]->SetScale(0.1f);
			m_pCAttachedObjMesh[attached]->SetPosition(m_vAttachedObjPos[attached]);
			m_pCAttachedObjMesh[attached]->SetBlend(true);
			m_pCAttachedObjMesh[attached]->Render(m_mView, m_mProj, m_vCameraPos, m_stLight);
			m_pCAttachedObjMesh[attached]->SetBlend(false);
		}
	}
}

//===================================.
//		エフェクト再生処理関数.
//===================================.
void CMoveObjectBase::EffectPlay()
{
	//エフェクトの再生.
	if (m_EffectHandle == EFFECT_HANDLE_DEFAULT_VALUE) {
		m_EffectHandle = m_pCEffect->Play(m_vEffectPos);
		return;
	}

	
	//エフェクト再生終了後にエフェクト再生.
	if (m_pCEffect->GetEffectShow(m_EffectHandle) == false) {
		m_pCEffect->Stop(m_EffectHandle);
		m_EffectHandle = m_pCEffect->Play(m_vEffectPos);
	}
}

//===================================.
//		エフェクト停止処理関数.
//===================================.
void CMoveObjectBase::EffectStop()
{
	//エフェクト停止.
	if (m_EffectHandle != EFFECT_HANDLE_DEFAULT_VALUE) {
		m_pCEffect->Stop(m_EffectHandle);
		m_EffectHandle = EFFECT_HANDLE_DEFAULT_VALUE;
	}
}