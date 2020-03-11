#include "CBigGhost.h"

CBigGhost::CBigGhost()
	: m_pCSkinMesh	(nullptr)
{
	//‰Šú‰»ˆ—ŠÖ”.
	Init();
}

CBigGhost::~CBigGhost()
{
	//‰ğ•úˆ—ŠÖ”.
	Release();
}

//==========================================.
//		XVˆ—ŠÖ”.
//==========================================.
void CBigGhost::Update()
{
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
		m_vPos.x += 0.1f;
	}
	if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
		m_vPos.x -= 0.1f;
	}
	if (GetAsyncKeyState(VK_UP) & 0x8000) {
		m_vPos.y += 0.1f;
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
		m_vPos.y -= 0.1f;
	}
	//if (GetAsyncKeyState('Z') & 0x8000) {
	//	m_vPos.z += 0.1f;
	//}
	//if (GetAsyncKeyState('X') & 0x8000) {
	//	m_vPos.z -= 0.1f;
	//}

}

//==========================================.
//		•`‰æˆ—ŠÖ”.
//==========================================.
void CBigGhost::Render()
{
	m_pCSkinMesh->SetAnimSpeed(0.02f);
	m_pCSkinMesh->SetScale(0.1f);
	m_pCSkinMesh->SetPosition(m_vPos);
	m_pCSkinMesh->SetRotation(m_vRot);
	m_pCSkinMesh->Render(m_mView, m_mProj, m_vCameraPos, m_stLight);
}

//==========================================.
//		‰Šú‰»ˆ—ŠÖ”.
//==========================================.
void CBigGhost::Init()
{
	m_pCSkinMesh = m_pCResourceManager->GetSkinMesh(enSkinMeshType::BigGhost);
	m_vPos = D3DXVECTOR3(6.0f, 0.0f, 4.5f);
	m_vRot = D3DXVECTOR3(0.0f, -1.35f, 0.0f);
}

//==========================================.
//		‰ğ•úˆ—ŠÖ”.
//==========================================.
void CBigGhost::Release()
{

}

//==========================================.
//		‹N°ˆ—ŠÖ”.
//==========================================.
void CBigGhost::WakeUp()
{

}

//==========================================.
//		¢‚éŠ´îˆ—ŠÖ”.
//==========================================.
void CBigGhost::HaveTroubleEmotion()
{

}

//==========================================.
//		Šì‚ÔŠ´îˆ—ŠÖ”.
//==========================================.
void CBigGhost::RejoiceEmotion()
{

}

//==========================================.
//		Q‚éˆ—ŠÖ”.
//==========================================.
void CBigGhost::Sleep()
{

}