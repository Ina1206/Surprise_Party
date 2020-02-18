#ifndef CGAME_GHOST_CURSOL_H
#define CGAME_GHOST_CURSOL_H

#include "..\CGameWorldCursor.h"

/*********************************************
*	ゲーム内のお化けのカーソルクラス.
*************/
class CGameGhostCursor
	: public CGameWorldCursor
{
public:
	CGameGhostCursor();
	~CGameGhostCursor();

	//=====================定数==========================//.
	const float	CURSOL_BASE_HIGHT	= 7.0f;	//カーソル基本高さ.
	const float	SCALE				= 2.5f;	//大きさ.

	//=====================関数==========================//.
	void UpDate();			//更新処理関数.

	//===============情報獲得処理化数====================//.
	//休憩フラグ.
	void SetRestFlag(const bool& flag) { m_bRestFlag = flag; }
	
private:
	//=====================関数==========================//.
	void Init();			//初期化処理関数.
	void Release();			//解放処理関数.

	//=====================変数==========================//.
	bool	m_bRestFlag;	//休憩フラグ.

	

};

#endif //#ifndef CGAME_GHOST_CURSOL_H.