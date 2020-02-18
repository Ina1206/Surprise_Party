#ifndef CMAP_GIMMICK_CUROSR_H
#define CMAP_GIMMICK_CUROSR_H

#include "..\CMapCursor.h"

/****************************************
*	マップ上のギミック用カーソルクラス.
********/
class CMapGimmickCursor
	: public CMapCursor
{
public:
	CMapGimmickCursor();
	~CMapGimmickCursor();

	//========================関数=============================//.
	void UpDate();		//更新処理関数.

private:
	//========================関数=============================//.
	void Init();		//初期化処理関数.
	void Release();		//解放処理関数.


};

#endif	//#ifndef CMAP_GIMMICK_CUROSR_H.