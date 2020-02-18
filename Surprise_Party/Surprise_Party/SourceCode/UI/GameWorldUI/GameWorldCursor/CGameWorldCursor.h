#ifndef CGAME_WORLD_CURSOL_H
#define CGAME_WORLD_CURSOL_H

#include "..\CGameWorldUI.h"

/***********************************
*		ゲーム内のカーソルクラス.
***********/
class CGameWorldCursor
	: public CGameWorldUI
{
public:
	CGameWorldCursor();
	virtual ~CGameWorldCursor();

	//==================定数=====================//.
	const float	UNSELECTABLE_ALPHA	= 0.5f;		//選択できないときの透過値.


protected:
	//==================関数=====================//.
	void CursorUpDown();						//カーソル動き処理関数.
	void AlphaChange(bool flag);				//透過値変更処理関数.

	//==================変数=====================//.
	float	m_fUpDownDistance;					//上がり下がり距離.

private:
	//==================定数=====================//.
	const float	ADD_SPEED			= -0.003f;	//加速速度.
	const float	MOVE_DISTANCE_MIN	= -0.5f;	//移動距離最小値.
	const float MOVE_DISTANCE_MAX	= 0.0f;		//移動距離最大値.
	const int	CHANGE_DIRECTION	= -1;		//方向変更数値.

	//=================列挙体====================//.
	//上下の種類.
	enum class enUpDownType {
		Up,		//上がる.
		Down,	//下がる.
	};

	//==================変数======================//.
	enUpDownType	m_enUpDownType;			//上下の種類.
	float			m_fUpDownSpeed;			//上下移動の速度.
	int				m_Direction;			//方向.

};

#endif	//#ifndef CGAME_WORLD_CURSOL_H.