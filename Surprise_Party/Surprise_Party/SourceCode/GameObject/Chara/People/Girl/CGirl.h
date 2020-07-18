#ifndef CGIRL_H
#define CGIRL_H

#include "..\CPeopleBase.h"

/*******************************************************
*			女の子クラス.
************************/
class CGirl
	: public CPeopleBase
{
public:
	CGirl();
	~CGirl();

	//=================定数====================//.
	const int	SUSPEND_INTERVAL_TIME_MIN	= 2;	//一時停止時間最小値.
	const int	SUSPEND_INRERVAL_TIME_MAX	= 5;	//一時停止時間最大値.
	const int	SECONDS_DELIMITER			= 60;	//秒区切り.
	const float DEPTH_POS					= -3.5f;//奥行きの座標.

	//================列挙体===================//.
	enum class enGirlAnimType {
		FallDown,	//倒れる.
		Stand,		//立つ.
		Walk,		//歩く.
		Search,		//探索.
		Rejoice,	//喜ぶ.
	};

	//=================関数====================//.
	void Update();				//更新処理関数.
	
private:
	//=================関数====================//.
	void Init();				//初期化処理関数.
	void Release();				//解放処理関数.
	void SearchMotion();		//探索処理関数.
	void SearchAnimChange();	//探索アニメーション変更処理関数.

	//=================変数=====================//.
	int		m_SuspendTime;		//一時停止するカウント.
	double	m_dAnimTime;		//アニメーションタイム.
	int		m_SuspendInterval;	//一時停止間隔.
	float	m_fOldPosX;			//X座標の前の座標.
};

#endif	//#ifndef CGIRL_H.