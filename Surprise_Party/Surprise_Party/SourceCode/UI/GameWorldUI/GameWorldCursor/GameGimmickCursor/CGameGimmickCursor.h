#ifndef CGAME_GIMMICK_CURSOR_H
#define CGAME_GIMMICK_CURSOR_H

#include "..\CGameWorldCursor.h"

/***********************************
*		ギミックカーソルクラス.
********/
class CGameGimmickCursor
	: public CGameWorldCursor
{
public:
	CGameGimmickCursor();
	~CGameGimmickCursor();

	//====================定数======================//.
	const float			ADJUST_HEIGHT	= -3.0f;						//高さ調整.
	const float			ADJUST_WIDTH	= 4.0f;							//幅調整.
	const float			SCALE			= 2.5f;							//大きさ.
	const D3DXVECTOR3	COLOR			= D3DXVECTOR3(0.5f, 1.0f, 0.5f);//色.

	//====================関数======================//.
	void UpDate();					//更新処理関数.

	//==============情報置換処理関数================//.
	//選択できるフラグ.
	void SetUnSelectableFlag(const bool& flag) { m_bUnSelectableFlag = flag; }

private:
	//====================関数======================//.
	void Init();					//初期化処理関数.
	void Release();					//解放処理関数.

	//====================変数======================//.
	bool	m_bUnSelectableFlag;	//選択でるフラグ.

};

#endif	//#ifndef CGAME_GIMMICK_CURSOR_H.