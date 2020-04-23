#ifndef CARROW_H
#define CARROW_H

#include "..\CPlayUI.h"

/**********************************************
*			矢印クラス.
*****************/
class CArrow
	: public CPlayUI
{
public:
	CArrow();
	~CArrow();

	//===================定数====================//.
	const D3DXVECTOR3	BASE_POS			= D3DXVECTOR3(600.0f, 500.0f, 0.0f);	//基本位置.
	const int			ARROW_MAX			= 2;									//矢印最大値.
	const int			LEFT_ARROW_NUM		= 0;									//左矢印番号.
	const int			RIGHT_ARROW_NUM		= 1;									//右矢印番号.
	const float			ARROW_WIDTH			= 100.0f;								//矢印幅.
	const float			LEFT_ARROW_ROT_Y	= 2.9f;									//左矢印y角度.
	const float			ACCELERATION_SPEED	= 0.1f;									//加速速度.
	const float			MOVE_DISTANCE_MAX	= 30.0f;								//移動距離最大値.
	const float			MOVE_DISTANCE_MIN	= 0.0f;									//移動距離最小値.
	const int			CHANGE_DIRECT		= -1;									//方向変更数値.
	const int			MOVE_LEFT_DIRECT	= -1;									//左移動方向.
	const int			MOVE_OUTSIDE_DIRECT = 1;									//外側へ移動方向.

	const unsigned int	USING_LEFT_FLAG		= (1 << 0);								//左の矢印使用フラグ.
	const unsigned int	USING_RIGHT_FLAG	= (1 << 1);								//右の矢印使用フラグ.

	//===================関数====================//.
	void Update();		//更新処理関数.

	//=============情報置換処理関数==============//.
	void SetCenterPos(const D3DXVECTOR3& vPos) { m_vCenterPos = vPos; }
	void SetUsingArrowFlag(const unsigned int& Flag) { m_UsingArrowFlag = Flag; }

	//=============情報取得処理関数==============//.
	unsigned int GetUsingArrowFlag() const { return m_UsingArrowFlag; }

private:
	//===================関数====================//.
	void Init();			//初期化処理関数.
	void Release();			//解放処理関数.
	void MoveArrow();		//矢印移動処理関数.
	void SettingPos();		//座標設定処理関数.			

	//===================変数====================//.
	D3DXVECTOR3		m_vCenterPos;		//中心座標.
	unsigned int	m_UsingArrowFlag;	//使用中の矢印フラグ.
	float			m_fDistance;		//移動距離.
	int				m_fDirect;			//方向.
	float			m_fMoveSpeed;
};

#endif	//#ifndef CARROW_H.