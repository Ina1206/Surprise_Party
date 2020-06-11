#ifndef CLOW_EVALUATION_STAGE_H
#define CLOW_EVALUATION_STAGE_H

#include "..\CEndingStageBase\CEndingStageBase.h"

/***********************************************
*		低評価のステージクラス.
*****************/
class CLowEvaluationStage
	: public CEndingStageBase
{
public:
	CLowEvaluationStage();
	~CLowEvaluationStage();

	//======================関数========================//.
	void Update();		//更新処理関数.
	void Render();		//描画処理関数.

private:
	//======================関数========================//.
	void Init();		//初期化処理関数.
	void Release();		//解放処理関数.


};

#endif	//#ifndef CLOW_EVALUATION_STAGE_H.