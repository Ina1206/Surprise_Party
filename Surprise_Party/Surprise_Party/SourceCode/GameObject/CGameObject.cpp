#include "CGameObject.h"

/************************************
*	�Q�[���I�u�W�F�N�g�N���X.
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
//		�`�揉���ݒ菈���֐�.
//==========================================.
void CGameObject::RenderInitSetting(const D3DXMATRIX& mView, const D3DXMATRIX& mProj, const LIGHT& stLight)
{
	m_mView = mView;
	m_mProj = mProj;
	m_stLight = stLight;
}