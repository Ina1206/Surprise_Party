#ifndef CHIGHT_EVALUATION_STAGE_H
#define CHIGHT_EVALUATION_STAGE_H

#include "..\EvaluationStageBase\CEvaluationStageBase.h"

/**************************************************
*			高評価ステージクラス.
********************/
class CHightEvaluationStage
	: public CEvaluationStageBase
{
public:
	CHightEvaluationStage();
	~CHightEvaluationStage();

private:
	//========================関数============================//.
	void Init();		//初期化処理関数.
	void Release();		//解放処理関数.

};

#endif	//#ifndef CHIGHT_EVALUATION_STAGE_H.