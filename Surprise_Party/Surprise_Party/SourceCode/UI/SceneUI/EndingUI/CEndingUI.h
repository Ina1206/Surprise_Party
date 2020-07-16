#ifndef CENDING_UI_H
#define CENDING_UI_H

#include "PushEnter\CPushEnter.h"
#include "EvaluationUI\EvaluationUIManager\CEvaluationUIManager.h"
#include "SurpriseDegree\SurpriseDegreeManager\CSurpriseDegreeManager.h"
#include "..\CSceneUIBase.h"

/*******************************************
*		エンディングUIクラス.
********************/
class CEndingUI
	: public CSceneUIBase
{
public:
	CEndingUI();
	CEndingUI(const int& EvaluationNum);
	~CEndingUI();

	//======================定数==========================//.
	const unsigned int SURPRISE_DEGREE_FLAG = (1 << 0);	//驚かし度フラグ.
	const unsigned int EVALUATION_FLAG		= (1 << 1);	//評価フラグ.
	const unsigned int PUSH_ENTER_FLAG		= (1 << 2);	//PushEnterフラグ.

	//======================関数==========================//.
	void Update();					//更新処理関数.
	void Render();					//描画処理関数.

	//===============-情報取得処理関数====================//.
	//評価終了フラグ.
	bool GetFinishEvaluationFlag() const { return m_bFinishEvaluationFlag; }
	//シーン変更フラグ.
	bool GetChangeSceneFlag() const { return m_bChangeSceneFlag; }

private:
	//======================関数==========================//.
	void Init();					//初期化処理関数.
	void Release();					//解放処理関数.
	void UpdateSurpriseDegree();	//驚かし度更新処理関数.
	void UpdateEvaluation();		//評価更新処理関数.
	void UpdatePushEnter();			//PushEnter更新処理関数.

	//======================変数==========================//.
	std::unique_ptr<CSurpriseDegreeManager>	m_pCSurpriseDegreeManager;	//驚かし度UI管理クラス.
	std::unique_ptr<CEvaluationUIManager>	m_pCEvaluationManager;		//評価UI管理クラス.
	std::unique_ptr<CPushEnter>				m_pCPushEnter;				//PushEnterクラス.

	unsigned int							m_UpdateUIFlag;				//更新処理UIフラグ.
	bool									m_bFinishEvaluationFlag;	//評価終了フラグ.
	int										m_EvaluationNum;			//評価番号.
	bool									m_bDisplayAllAtOnce;		//一気に描画するフラグ.
	bool									m_bChangeSceneFlag;			//シーン変更フラグ.

};


#endif	//#ifndef CENDING_UI_H.