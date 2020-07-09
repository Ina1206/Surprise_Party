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
	const unsigned int	GAME_START_FLAG		= (1 << 0);							//ゲームスタートフラグ.
	const unsigned int	GAME_FINISH_FLAG	= (1 << 1);							//ゲーム終了フラグ.	
	//m_ControlFlag.
	const unsigned int	CONTROL_WAIT_FLAG	= (1 << 0);							//操作待機フラグ.
	const unsigned int	CONTROL_FLAG		= (1 << 1);							//操作フラグ.

	const D3DXVECTOR3	TITLE_POS			= D3DXVECTOR3(40.5f, 90.8f, 0.0f);	//タイトル座標.

	const int			TITLE_MAX			= 2;								//タイトル最大値.



	//======================関数=======================//.
	void Update();							//更新処理関数.

	//================情報取得処理関数=================//.
	unsigned int GetSelectTypeFlag() const;	//選択種類のフラグを取得処理関数.
	
private:
	//======================関数=======================//.
	void Init();							//初期化処理関数.
	void InitTitlePos();					//タイトル座標の初期化処理関数.
	void ControlTitlePos();					//操作時タイトル座標設定処理関数.

	//======================変数=======================//.
	unsigned int				m_SelectTypeFlag;			//選択種類フラグ.
	unsigned int				m_ControlFlag;				//操作フラグ.
	std::vector<D3DXVECTOR3>	m_vTitleLastPos;			//タイトル最終座標.

};

#endif	//#ifndef CTITLE_UI_H.