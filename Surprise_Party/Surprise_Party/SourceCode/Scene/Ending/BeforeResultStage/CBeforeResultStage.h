#ifndef CBEFORE_RESULT_STAGE_H
#define CBEFORE_RESULT_STAGE_H

#include "..\CEndingStageBase\CEndingStageBase.h"

/********************************************
*		結果発表前のステージクラス.
******************/
class CBeforeResultStage
	: public CEndingStageBase
{
public:
	CBeforeResultStage();
	~CBeforeResultStage();

	//========================関数=========================//.
	void Update();		//更新処理関数.
	void Render();		//描画処理関数.

private:
	//========================関数=========================//.
	void Init();		//初期化処理関数.
	void Release();		//解放処理関数.


};

#endif	//#ifndef CBEFORE_RESULT_STAGE_H.