#include "CHightEvaluationStage.h"

/**********************************************
*			高評価ステージクラス.
*******************/
CHightEvaluationStage::CHightEvaluationStage()
{
	//初期化処理関数.
	Init();
}

CHightEvaluationStage::~CHightEvaluationStage()
{
	//解放処理関数.
	Release();
}

//=============================================.
//			更新処理関数.
//=============================================.
void CHightEvaluationStage::Update()
{

}

//=============================================.
//			描画処理関数.
//=============================================.
void CHightEvaluationStage::Render()
{
	//床の描画処理関数.
	RenderFloor();

	//お化け描画処理関数.
	RenderGhost();
}

//=============================================.
//			初期化処理関数.
//=============================================.
void CHightEvaluationStage::Init()
{

}

//=============================================.
//			解放処理関数.
//=============================================.
void CHightEvaluationStage::Release()
{

}