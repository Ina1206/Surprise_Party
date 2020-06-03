#include "CEndingSwitchGhost.h"

/*******************************************
*		エンディングスイッチお化けクラス.
******************/
CEndingSwitchGhost::CEndingSwitchGhost()
{
	//初期化処理関数.
	Init();
}

CEndingSwitchGhost::~CEndingSwitchGhost()
{
	//解放処理関数.
	Release();
}

//===========================================.
//		更新処理関数.
//===========================================.
void CEndingSwitchGhost::Update()
{
	//移動角度処理関数.
	MoveRotation(m_vPos, m_vLookAtPos);
}

//===========================================.
//		描画処理関数.
//===========================================.
void CEndingSwitchGhost::Render()
{
	//スイッチお化け描画処理関数.
	RenderSwitchGhost(m_vPos);
}

//===========================================.
//		初期化処理関数.
//===========================================.
void CEndingSwitchGhost::Init()
{
	//静的オブジェクトお化け初期化処理関数.
	InitStaticMeshGhost();

	m_fScale = 0.025f;

}

//===========================================.
//		解放処理関数.
//===========================================.
void CEndingSwitchGhost::Release()
{

}