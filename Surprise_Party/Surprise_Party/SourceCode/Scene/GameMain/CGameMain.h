#ifndef CGAME_MAIN_H
#define CGAME_MAIN_H

#include "..\SceneBase\CSceneBase.h"
#include "StageManager/CStageManager.h"

/***************************************
*		ゲームメインクラス.
***********/
class CGameMain
	: public CSceneBase
{
public:
	CGameMain();
	~CGameMain();


	//=========================関数===========================//.
	void UpDate();		//更新処理関数.
	void Render();		//描画処理関数.

private:
	//=========================関数===========================//.
	void Init();		//初期化処理関数.
	void Release();		//解放処理関数.

	//===================変数=======================//.
	std::unique_ptr<CStageManager>	m_pCStageManager;	//ステージ管理クラス.
							
};

#endif	//#ifndef CGAME_MAIN_H.