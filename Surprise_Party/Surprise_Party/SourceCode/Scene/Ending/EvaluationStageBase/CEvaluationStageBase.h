#ifndef CEVALUATION_STAGE_BASE_H
#define CEVALUATION_STAGE_BASE_H

#include "..\CEndingStageBase\CEndingStageBase.h"
#include "..\..\UI\SceneUI\EndingUI\CEndingUI.h"

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
	void Update();			//更新処理関数.
	void Render();			//描画処理関数.

protected:

private:
	//======================関数=========================//.
	void InitUI();			//UIの初期化処理関数.
	void UpdateCommonUI();	//共通のUIの更新処理関数.
	void RenderCommonUI();	//共通のUIの描画処理関数.

	//========================変数=============================//.
	std::unique_ptr<CEndingUI>				m_pCEndingUI;				//EndingUIクラス.

};

#endif	//#ifndef CEVALUATION_STAGE_BASE_H.