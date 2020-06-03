#include "CEndingDispGhost.h"

/******************************************
*	エンディングの現れるお化けクラス.
**************/
CEndingDispGhost::CEndingDispGhost()
{
	//初期化処理関数.
	Init();
}

CEndingDispGhost::~CEndingDispGhost()
{

}

//===========================================.
//		更新処理関数.
//===========================================.
void CEndingDispGhost::Update()
{
	//ConvertRotationMatrixToQuaternion();
}

//===========================================.
//		描画処理関数.
//===========================================.
void CEndingDispGhost::Render()
{
	m_pCSkinMesh->ChangeAnimSet_StartPos(0, WAIT_ANIM_START_POS, m_pAnimCtrl);
	MoveRotation(m_vPos, m_vLookAtPos);
	//D3DXQUATERNION a;
	//D3DXQuaternionRotationMatrix(&a, &m_mPoint);
	//m_vRot = D3DXVECTOR3(a.x, a.y, a.z);
	RenderDispGhost(m_vPos);
	
}

//===========================================.
//		初期化処理関数.
//===========================================.
void CEndingDispGhost::Init()
{
	//アニメーション初期化処理関数.
	InitAnimation();
	m_fScale = 0.07f;
}

//============================================.
//		解放処理関数.
//============================================.
void CEndingDispGhost::Release()
{

}