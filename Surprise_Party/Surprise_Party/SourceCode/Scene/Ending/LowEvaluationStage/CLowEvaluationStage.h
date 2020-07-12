#ifndef CLOW_EVALUATION_STAGE_H
#define CLOW_EVALUATION_STAGE_H

#include "..\EvaluationStageBase\CEvaluationStageBase.h"

/***********************************************
*		低評価のステージクラス.
*****************/
class CLowEvaluationStage
	: public CEvaluationStageBase
{
public:
	CLowEvaluationStage();
	CLowEvaluationStage(const int& EvaluationNum);
	~CLowEvaluationStage();

private:
	//======================関数========================//.
	void Init();		//初期化処理関数.
	void Release();		//解放処理関数.


};

#endif	//#ifndef CLOW_EVALUATION_STAGE_H.