#ifndef COBJECT_MOVE_SWITCH_H
#define COBJECT_MOVE_SWITCH_H

#include "..\CSwitchBase.h"

/*****************************************
*		スイッチの移動オブジェクトクラス.
*****************/
class CObjectMoveSwitch
	: public CSwitchBase
{
public:
	CObjectMoveSwitch();
	~CObjectMoveSwitch();

	//============定数===============//.
	const int	MOVE_OBJECT_MAX = 2;	//移動オブジェクト最大数.
	const int	TABLE_NUM		= 0;	//机番号.
	const int	FLOWER_NUM		= 1;	//花番号.

	//============関数===============//.
	void Update();		//更新処理関数.
private:
	//============関数===============//.
	void Init();		//初期化処理関数.
	void Release();		//解放処理関数.

	//============変数===============//.
	D3DXVECTOR3	m_vAttachedOldPos;	//付属オブジェクト前回の座標.

};

#endif //#ifndef COBJECT_MOVE_SWITCH_H.