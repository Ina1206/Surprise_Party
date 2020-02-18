#ifndef CGHOST_STRENGTH_ICON_H
#define CGHOST_STRENGTH_ICON_H

#include "..\CGameWorldUI.h"

/************************************************
*		お化けの体力アイコンクラス.
***************/
class CGhostStrengthIcon
	: public CGameWorldUI
{
public:
	CGhostStrengthIcon();
	~CGhostStrengthIcon();

	//=================定数=================//.
	const D3DXVECTOR2	GREAT_STRENGTH		= D3DXVECTOR2(1.0f, 0.0f);			//体力(優良)アイコン番号.
	const D3DXVECTOR2	GOOD_STRENGTH		= D3DXVECTOR2(4.0f, 1.0f);			//体力(良)アイコン番号.
	const D3DXVECTOR2	NORMAL_STRENGTH		= D3DXVECTOR2(1.0f, 3.0f);			//体力(普通)アイコン番号.
	const D3DXVECTOR2	BAD_STRENGTH		= D3DXVECTOR2(0.0f, 1.0f);			//体力(悪)アイコン番号.
	const D3DXVECTOR3	ICON_POS_ADJUST		= D3DXVECTOR3(1.5f, 5.5f, -1.0f);	//アイコン座標微調整.
	const float			ALPHA_CHANGE_POS	= 0.5f;								//透過値変更座標.
	const float			WALL_BACK_ALPHA		= 0.3f;								//壁の後ろにいるときの透過値.
	const float			BEFORE_WALL_ALPHA	= 1.0f;								//壁の前にいるときの透過値.

	//================列挙体================//.
	//体力タイプ.
	enum class enStrengthType {
		Bad = 0,	//悪.
		Normal,		//普通.
		Good,		//良い.
		Great,		//優.
	};

	//=================関数=================//.
	void UpDate();	//更新処理関数.

	//===========情報置換処理関数===========//.
	//休憩フラグ.
	void SetRestFlag(const bool& bflags) { m_bRestFalg = bflags; }
	//体力アイコン.
	void SetStrengthIcon(const int& Strength) { m_StrengthIcon = Strength; }

private:
	//=================関数=================//.
	void Init();	//初期化処理関数.
	void Release();	//解放処理関数.

	//=================変数=================//.
	bool	m_bRestFalg;	//休憩フラグ.
	int		m_StrengthIcon;	//体力アイコン.
};

#endif	//#ifndef CGHOST_STRENGTH_ICON_H.