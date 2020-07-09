#ifndef CTITLE_UI_H
#define CTITLE_UI_H

#include "..\CSceneUIBase.h"

/*************************************
*		タイトルUIクラス.
****************/
class CTitleUI
	: public CSceneUIBase
{
public:
	CTitleUI();
	~CTitleUI();
	//======================定数=======================//.
	//m_SelectTypeFlag.
	const unsigned int GAME_START_FLAG		= (1 << 0);		//ゲームスタートフラグ.
	const unsigned int GAME_FINISH_FLAG		= (1 << 1);		//ゲーム終了フラグ.	
	//m_ControlFlag.
	const unsigned int CONTROL_WAIT_FLAG	= (1 << 0);		//操作待機フラグ.
	const unsigned int CONTROL_FLAG			= (1 << 1);		//操作フラグ.

	//======================関数=======================//.
	void Update();	//更新処理関数.

	//================情報取得処理関数=================//.
	unsigned int GetSelectTypeFlag() const;	//選択種類のフラグを取得処理関数.
	
private:
	//======================関数=======================//.
	void Init();	//初期化処理関数.

	//======================変数=======================//.
	unsigned int m_SelectTypeFlag;	//選択種類フラグ.
	unsigned int m_ControlFlag;		//操作フラグ.

};

#endif	//#ifndef CTITLE_UI_H.