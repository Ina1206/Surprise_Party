#ifndef CINTERMEDIATE_EVALUATION_STAGE_H
#define CINTERMEDIATE_EVALUATION_STAGE_H

#include "..\EvaluationStageBase\CEvaluationStageBase.h"

/***********************************************
*		中間評価ステージクラス.
********************/
class CIntermediateEvaluationStage
	: public CEvaluationStageBase
{
public:
	CIntermediateEvaluationStage();
	~CIntermediateEvaluationStage();

private:
	//=========================関数==============================//.
	void Init();		//初期化処理関数.
	void Release();		//解放処理関数.


};


#endif	//#ifndef CINTERMEDIATE_EVALUATION_STAGE_H.