#ifndef CEVALUATION_STAGE_BASE_H
#define CEVALUATION_STAGE_BASE_H

#include "..\CEndingStageBase\CEndingStageBase.h"
#include "..\..\UI\SceneUI\EndingUI\SurpriseDegree\SurpriseDegreeManager\CSurpriseDegreeManager.h"
#include "..\..\UI\SceneUI\EndingUI\EvaluationUI\EvaluationUIManager\CEvaluationUIManager.h"

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
	//===================定数======================//.
	const D3DXVECTOR3	PUSH_ENTER_POS = D3DXVECTOR3(800.0f, 600.0f, 0.0f);	//PushEnterの座標.
	const float			ALPHA_MAX = 1.0f;									//透過値最大値.
	const float			ALPHA_MIN = 0.0f;									//透過値最小値.
	const float			PUSH_ENTER_SCALE_MAX = 2.0f;						//PushEnter大きさ.

	//======================関数=========================//.
	void InitUI();			//UIの初期化処理関数.
	void UpdateCommonUI();	//共通のUIの更新処理関数.
	void RenderCommonUI();	//共通のUIの描画処理関数.
	void UpdatePushEnter();	//PushEnterの更新処理関数.
	void RenderPushEnter();	//PushEnterの描画処理関数.

	//========================変数=============================//.
	std::unique_ptr<CSurpriseDegreeManager> m_pCSurpriseDegreeManager;	//驚かし度の管理クラス.
	std::unique_ptr<CEvaluationUIManager>	m_pCEvaluationUIManager;	//評価UI管理クラス.
	CSpriteUI*								m_pCPushEnterUI;			//SpriteUIクラス(PushEnterの文字).
	float									m_fPushEnterUIAlpha;		//SpriteUIの透過値.
	int										m_AlphaAddDecDirect;		//透過値の加算減算方向.

};

#endif	//#ifndef CEVALUATION_STAGE_BASE_H.