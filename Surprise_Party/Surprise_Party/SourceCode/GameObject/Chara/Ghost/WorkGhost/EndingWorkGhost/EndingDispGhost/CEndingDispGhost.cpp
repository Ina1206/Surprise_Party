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

}

//===========================================.
//		描画処理関数.
//===========================================.
void CEndingDispGhost::Render()
{
	m_pCSkinMesh->ChangeAnimSet_StartPos(0, WAIT_ANIM_START_POS, m_pAnimCtrl);
	RenderDispGhost(m_vPos);
}

//===========================================.
//		初期化処理関数.
//===========================================.
void CEndingDispGhost::Init()
{
	//アニメーション初期化処理関数.
	InitAnimation();
}

//============================================.
//		解放処理関数.
//============================================.
void CEndingDispGhost::Release()
{

}