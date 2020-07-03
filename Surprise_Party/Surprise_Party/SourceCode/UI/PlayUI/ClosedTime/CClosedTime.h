#ifndef CCLOSED_TIME_H
#define CCLOSED_TIME_H

#include "..\CPlayUI.h"

/************************************
*	閉店時間UIクラス.
*********/
class CClosedTime
	: public CPlayUI
{
public:
	CClosedTime();
	CClosedTime(const int& StageNum);
	~CClosedTime();

	//====================定数=====================//.
	const int			TIME_UI_MAX				= 7;	//時間UI最大数.
	const int			TIME_START_NUM			= 2;	//時間のスプライト開始番号.
	const int			TREE_BORD				= 0;	//木の板番号.
	const int			CLOSED_STRING_NUM		= 1;	//閉店文字.
	const int			HOUR_DELIMITER			= 60;	//時間(h)区切り.
	const int			NUM_RANK_DELIMITER		= 10;	//数値区切り.
	const int			TIME_REDUCE_DELIMITER	= 60;	//時間減らす区切り.
	const int			TIME_MIN				= 0;	//時間最小値.
	const int			BONUS_TIME_ADD			= 1;	//ボーナス追加時間.

	const D3DXVECTOR2	TREE_PATTARN_NO			= D3DXVECTOR2(1.0f, 0.0f);	//木の板のパターン番号.
	const D3DXVECTOR2	COLON_PATTARN_NO		= D3DXVECTOR2(10.0f, 0.0f);	//コロンパターン番号.
	
	const D3DXVECTOR3	COLON_POS				= D3DXVECTOR3(1110.0f, 640.0f, 0.0f);	//木の板の座標.
	const D3DXVECTOR3	TREE_BORD_POS			= D3DXVECTOR3(980.0f, 580.0f, 0.0f);	//コロンの座標.
	const D3DXVECTOR3	CLOSED_STRING_POS		= D3DXVECTOR3(1080.0f, 580.0f, 0.0f);	//閉店文字の座標.
	const D3DXVECTOR3	TIME_POS				= D3DXVECTOR3(1055.0f, 640.0f, 0.0f);	//時間の座標.
	
	const float			TIME_INTERVAL			= 50.0f;								//時間の間隔.
	
	//====================関数=====================//.
	void Update();							//更新処理関数.
	void GiveBornusTime(const bool& flag);	//追加時間与える処理関数.

	//==============情報取得処理関数===============//.
	//閉店フラグ.
	bool GetClosedFlag() { return m_bClosedFlag; }

private:
	//====================関数=====================//.
	void Init();							//初期化処理関数.
	void Release();							//解放処理関数.
	void HourCalc(int time);				//時間(h)計算処理関数.
	void MinutesCalc(int time);				//分(m)計算処理関数.
	void TitmeCalc();						//時間計算処理関数.


	//====================変数=====================//.
	int		m_TimeUpToClose;				//閉店までの時間.
	int		m_TimeReduceCnt;				//時間減らすカウント.
	bool 	m_GiveBornusTime;				//追加時間与えるフラグ.
	bool	m_bClosedFlag;					//閉店フラグ.
	int		m_StageNum;						//ステージ番号.
};

#endif	//#ifndef CCLOSED_TIME_H.