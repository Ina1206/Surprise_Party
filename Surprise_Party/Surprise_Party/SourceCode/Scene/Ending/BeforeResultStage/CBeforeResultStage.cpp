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

}

//=======================================.
//		描画処理関数.
//=======================================.
void CBeforeResultStage::Render()
{
	//床の描画処理関数.
	RenderFloor();

}

//=======================================.
//		初期化処理関数.
//=======================================.
void CBeforeResultStage::Init()
{

}

//=======================================.
//		解放処理関数.
//=======================================.
void CBeforeResultStage::Release()
{

}