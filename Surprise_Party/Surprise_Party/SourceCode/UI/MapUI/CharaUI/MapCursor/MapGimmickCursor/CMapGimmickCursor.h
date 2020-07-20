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

	//========================定数=============================//.
	const float			CURSOR_HEIGHT	= 60.0f;							//カーソル高さ.
	const float			SCALE			= 1.3f;								//大きさ.
	const D3DXVECTOR3	COLOR			= D3DXVECTOR3(0.0f, 1.0f, 0.0f);	//色.

	//========================関数=============================//.
	void UpDate();		//更新処理関数.

private:
	//========================関数=============================//.
	void Init();		//初期化処理関数.
	void Release();		//解放処理関数.


};

#endif	//#ifndef CMAP_GIMMICK_CUROSR_H.