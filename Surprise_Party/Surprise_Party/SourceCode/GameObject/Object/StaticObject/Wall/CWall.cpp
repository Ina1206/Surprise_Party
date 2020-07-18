#include "CWall.h"

/*****************************************
*		壁オブジェクトクラス.
*******/
CWall::CWall()
{
	//初期化処理関数.
	Init();
}

CWall::~CWall()
{
	//解放処理関数.
	Release();
}

//====================================.
//		更新処理関数.
//====================================.
void CWall::Update()
{
	m_fAlpha = fabsf(m_vPos.x - m_vCameraPos.x) / ALPHA_DIVISOR;
	m_fAlpha += WALL_ALPHA_MIN;
	if (m_fAlpha >= ALPHA_MAX) {
		m_fAlpha = ALPHA_MAX;
	}
}

//====================================.
//		初期化処理関数.
//====================================.
void CWall::Init()
{
	m_fScale = SCALE;
	m_vRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pCMesh = m_pCResourceManager->GetStaticMesh(enStaticMeshType::Wall);
}

//====================================.
//		解放処理関数.
//====================================.
void CWall::Release()
{
	m_pCMesh = nullptr;
}