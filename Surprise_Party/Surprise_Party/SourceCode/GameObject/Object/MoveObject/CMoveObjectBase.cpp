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
//		�G�t�F�N�g�`�揈���֐�.
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
//		�����蔻�菈���֐�.
//===================================.
void CMoveObjectBase::Hit()
{

}

//===================================.
//		�G�t�F�N�g�X�V�����֐�.
//===================================.
void CMoveObjectBase::EffectUpDate()
{
	//�G�t�F�N�g�̍��W�ݒ�.
	m_vEffectPos.x = m_vPos.x;

	if (m_bCameraDisp == true) {
		//�G�t�F�N�g�Đ������֐�.
		EffectPlay();
		m_bCameraDisp = false;
		return;
	}

	//�G�t�F�N�g��~�����֐�.
	EffectStop();

}

//===================================.
//	�t���I�u�W�F�N�g�`�揈���֐�.
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
//		�G�t�F�N�g�Đ������֐�.
//===================================.
void CMoveObjectBase::EffectPlay()
{
	//�G�t�F�N�g�̍Đ�.
	if (m_EffectHandle == EFFECT_HANDLE_DEFAULT_VALUE) {
		m_EffectHandle = m_pCEffect->Play(m_vEffectPos);
		return;
	}

	
	//�G�t�F�N�g�Đ��I����ɃG�t�F�N�g�Đ�.
	if (m_pCEffect->GetEffectShow(m_EffectHandle) == false) {
		m_pCEffect->Stop(m_EffectHandle);
		m_EffectHandle = m_pCEffect->Play(m_vEffectPos);
	}
}

//===================================.
//		�G�t�F�N�g��~�����֐�.
//===================================.
void CMoveObjectBase::EffectStop()
{
	//�G�t�F�N�g��~.
	if (m_EffectHandle != EFFECT_HANDLE_DEFAULT_VALUE) {
		m_pCEffect->Stop(m_EffectHandle);
		m_EffectHandle = EFFECT_HANDLE_DEFAULT_VALUE;
	}
}