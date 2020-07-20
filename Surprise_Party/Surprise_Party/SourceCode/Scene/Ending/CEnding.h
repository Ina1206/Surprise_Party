#ifndef CENDING_H
#define CENDING_H

#include "..\SceneBase\CSceneBase.h"

#include "BeforeResultStage\CBeforeResultStage.h"


/************************************************
*		エンディングクラス.
***********/
class CEnding
	: public CSceneBase
{
public:
	CEnding();
	~CEnding();

	//========================定数===========================//.
	const int LOW_EVALUATION_NUM			= 0;	//低評価の番号.
	const int INTERMEDIATE_EVALUATION_NUM	= 1;	//中間評価の番号.

	//========================関数===========================//.
	void UpDate();						//更新処理関数.
	void Render();						//描画処理関数.
private:
	//========================関数===========================//.
	void Init();						//初期化処理関数.
	void Release();						//解放処理関数.
	void ChangeStage();					//ステージ変更処理関数.
	CEndingStageBase* DecideStage();	//ステージ決定処理関数.

	//========================変数===========================//.
	std::unique_ptr<CEndingStageBase>	m_pCEndingStageBase;	//エンディングステージ基底クラス.
	int									m_ChangeStageCnt;		//ステージ変更カウント.
};

#endif	//#ifndef CENDING_H.