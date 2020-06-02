#include "CBeforeResultStage.h"

/********************************************
*		結果発表前のステージクラス.
******************/
CBeforeResultStage::CBeforeResultStage()
{
	//初期化処理関数.
	Init();
}

CBeforeResultStage::~CBeforeResultStage()
{
	//解放処理関数.
	Release();
}

//=======================================.
//		更新処理関数.
//=======================================.
void CBeforeResultStage::Update()
{
	for (unsigned int ghost = 0; ghost < m_pCGhost.size(); ghost++) {
		m_pCGhost[ghost]->Update();
	}
	

}

//=======================================.
//		描画処理関数.
//=======================================.
void CBeforeResultStage::Render()
{
	//床の描画処理関数.
	RenderFloor();

	//ビッグゴースト描画処理関数.
	//RenderBigGhost();

	//お化け描画処理関数.
	RenderGhost();

}

//=======================================.
//		初期化処理関数.
//=======================================.
void CBeforeResultStage::Init()
{
	m_Camera.vPos = D3DXVECTOR3(5.0f, 2.5f, -3.5f);
	m_Camera.vLook = D3DXVECTOR3(5.0f, 2.5f, 5.0f);

}

//=======================================.
//		解放処理関数.
//=======================================.
void CBeforeResultStage::Release()
{

}