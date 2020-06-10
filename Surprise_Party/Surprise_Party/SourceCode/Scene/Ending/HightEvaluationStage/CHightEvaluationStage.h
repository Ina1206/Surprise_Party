#ifndef CHIGHT_EVALUATION_STAGE_H
#define CHIGHT_EVALUATION_STAGE_H

#include "..\CEndingStageBase\CEndingStageBase.h"

/**************************************************
*			高評価ステージクラス.
********************/
class CHightEvaluationStage
	: public CEndingStageBase
{
public:
	CHightEvaluationStage();
	~CHightEvaluationStage();

	//========================関数============================//.
	void Update();		//更新処理関数.
	void Render();		//描画処理関数.

private:
	//========================関数============================//.
	void Init();		//初期化処理関数.
	void Release();		//解放処理関数.

};

#endif	//#ifndef CHIGHT_EVALUATION_STAGE_H.