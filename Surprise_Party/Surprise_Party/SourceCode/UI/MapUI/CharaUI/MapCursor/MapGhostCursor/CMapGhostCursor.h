#ifndef CMAP_GHOST_CURSOR_H
#define CMAP_GHOST_CURSOR_H

#include "..\CMapCursor.h"

/************************************
*	マップ上のお化けカーソルクラス.
**********/
class CMapGhostCursor
	: public CMapCursor
{
public:
	CMapGhostCursor();
	~CMapGhostCursor();

	//===================関数======================//.
	void UpDate();			//更新処理関数.

private:
	//===================関数======================//.
	void Init();			//初期化処理関数.
	void Release();			//解放処理関数.


};

#endif	//#ifndef CMAP_GHOST_CURSOR_H.