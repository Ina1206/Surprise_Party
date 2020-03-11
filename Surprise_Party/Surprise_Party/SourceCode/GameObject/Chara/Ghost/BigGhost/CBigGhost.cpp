#include "CBigGhost.h"

CBigGhost::CBigGhost()
	: m_pCSkinMesh	(nullptr)
{
	//�����������֐�.
	Init();
}

CBigGhost::~CBigGhost()
{
	//��������֐�.
	Release();
}

//==========================================.
//		�X�V�����֐�.
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
//		�`�揈���֐�.
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
//		�����������֐�.
//==========================================.
void CBigGhost::Init()
{
	m_pCSkinMesh = m_pCResourceManager->GetSkinMesh(enSkinMeshType::BigGhost);
	m_vPos = D3DXVECTOR3(6.0f, 0.0f, 4.5f);
	m_vRot = D3DXVECTOR3(0.0f, -1.35f, 0.0f);
}

//==========================================.
//		��������֐�.
//==========================================.
void CBigGhost::Release()
{

}

//==========================================.
//		�N�������֐�.
//==========================================.
void CBigGhost::WakeUp()
{

}

//==========================================.
//		���銴����֐�.
//==========================================.
void CBigGhost::HaveTroubleEmotion()
{

}

//==========================================.
//		��Ԋ�����֐�.
//==========================================.
void CBigGhost::RejoiceEmotion()
{

}

//==========================================.
//		�Q�鏈���֐�.
//==========================================.
void CBigGhost::Sleep()
{

}