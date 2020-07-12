#ifndef CEVALUATION_STAGE_BASE_H
#define CEVALUATION_STAGE_BASE_H

#include "..\CEndingStageBase\CEndingStageBase.h"

/**********************************************
*		評価ステージ基底クラス.
************************/
class CEvaluationStageBase
	: public CEndingStageBase
{
public:
	CEvaluationStageBase();
	CEvaluationStageBase(const int& EvaluationNum);
	~CEvaluationStageBase();
	
	//======================関数=========================//.
	void Update();	//更新処理関数.
	void Render();	//描画処理関数.

protected:

private:

};

#endif	//#ifndef CEVALUATION_STAGE_BASE_H.