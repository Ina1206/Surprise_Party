#include "CWall.h"

CWall::CWall()
{
	//‰Šú‰»ˆ—ŠÖ”.
	Init();
}

CWall::~CWall()
{
	//‰ğ•úˆ—ŠÖ”.
	Release();
}

//====================================.
//		XVˆ—ŠÖ”.
//====================================.
void CWall::UpDate()
{
	m_fAlpha = fabsf(m_vPos.x - m_vCameraPos.x) / ALPHA_DIVISOR;
	m_fAlpha += WALL_ALPHA_MIN;
	if (m_fAlpha >= ALPHA_MAX) {
		m_fAlpha = ALPHA_MAX;
	}
}

//====================================.
//		‰Šú‰»ˆ—ŠÖ”.
//====================================.
void CWall::Init()
{
	m_fScale = 0.1f;
	m_vRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pCMesh = m_pCResourceManager->GetStaticMesh(enStaticMeshType::Wall);
}

//====================================.
//		‰ğ•úˆ—ŠÖ”.
//====================================.
void CWall::Release()
{
	m_pCMesh = nullptr;
}