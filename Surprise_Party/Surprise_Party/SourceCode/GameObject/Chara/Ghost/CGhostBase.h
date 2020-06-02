#ifndef CGHOST_BASE_H
#define CGHOST_BASE_H

#include "..\CCharaBase.h"

class CGhostBase
	: public CCharaBase
{
public:
	CGhostBase();
	virtual ~CGhostBase();

	//=======================定数==========================//.
	const float	ANGLE_SPEED		= 0.08f;							//角度追加速度.
	const float	ANGLE_MAX		= 360.0f;							//角度最大値.
	const float	ANGLE_MIN		= 0.0f;								//角度最小値.
	const float	UP_DOWN_SPEED	= 0.01f;							//上下移動の速度.
	const float	VERTICAL_WIDTH	= 2.5f;								//縦の幅.

	//================列挙隊===================//.
	enum class enEmotionType {
		Sleep = 0,		//寝る.
		HaveTrounble,	//困る.
		Rejoice,		//喜ぶ.
		Question,		//疑問.
		Nothing,		//無し.

		Max,			//最大値.
	};

protected:
	//=======================関数==========================//.
	void MoveUpDown();		//浮遊処理関数.


	//=======================変数==========================//.
	int		m_EmotionNum;		//感情番号.

private:
	//=======================変数==========================//.
	float	m_fMoveAngle;		//移動角度.

};

#endif	//#ifndef CGHOST_BASE_H.