#ifndef CHIGHT_EVALUATION_STRING_H
#define CHIGHT_EVALUATION_STRING_H

#include "..\EvaluationUIBase\CEvaluationUIBase.h"

/**********************************************
*		高評価文字クラス.
*********************/
class CHightEvaluationString
	: public CEvaluationUIBase
{
public:
	CHightEvaluationString();
	~CHightEvaluationString();

	//=====================関数======================//.
	void Update();		//更新処理関数.

protected:
	//=====================関数======================//.
	void Init();		//初期化処理関数.


};

#endif	//#ifndef CHIGHT_EVALUATION_STRING_H.