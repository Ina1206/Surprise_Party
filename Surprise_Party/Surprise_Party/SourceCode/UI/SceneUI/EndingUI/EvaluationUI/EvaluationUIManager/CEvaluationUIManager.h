#ifndef CEVALUATION_UI_MANAGER_H
#define CEVALUATION_UI_MANAGER_H

#include "..\EvaluationUIBase\CEvaluationUIBase.h"

/*********************************************
*		評価UIの管理クラス.
********************/
class CEvaluationUIManager
{
public:

	CEvaluationUIManager();
	CEvaluationUIManager(const int& EvaluationNum);
	~CEvaluationUIManager();

	//=====================関数========================//.
	void Update();												//更新処理関数.
	void Render();												//描画処理関数.

	//===============情報取得処理関数==================//.
	//全て表示終了したフラグ.
	bool GetFinishedAllDispFlag() const { return m_bFinishedAllDispFlag; }

	//===============情報置換処理関数==================//.
	//一気に表示するフラグ.
	void SetDispAllAtOnce(const bool& bFlag) { m_bDisplayAllAtOnce = bFlag; }

private:
	//=====================関数========================//.
	void Init();												//初期化処理関数.
	std::unique_ptr<CEvaluationUIBase> DecideEvaluationUIType();//評価UIの種類決定処理関数.

	//=====================変数========================//.
	std::unique_ptr<CEvaluationUIBase>	m_pCEvaluationUIBase;	//評価UI.
	int									m_EvaluationNum;		//評価番号.
	bool								m_bFinishedAllDispFlag;	//全て表示終了したフラグ.
	bool								m_bDisplayAllAtOnce;	//一気に表示するフラグ.
};

#endif	//#ifndef CEVALUATION_UI_MANAGER_H.