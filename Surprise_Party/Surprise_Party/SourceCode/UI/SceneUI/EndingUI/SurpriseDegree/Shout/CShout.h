#ifndef CSHOUT_H
#define CSHOUT_H

#include "..\SurpriseDegreeBase\CSurpriseDegreeBase.h"

/*****************************************
*		叫びクラス.
********************/
class CShout
	: public CSurpriseDegreeBase
{
public:
	CShout();
	~CShout();

	//====================定数=======================//.
	const D3DXVECTOR3	FINISH_BASE_POS	= D3DXVECTOR3(300.0f, 560.0f, 0.0f);	//最終位置基本座標.
	const D3DXVECTOR3	INIT_POS		= D3DXVECTOR3(270.0f, 450.0f, 0.0f);	//初期座標.
	const float			MOVE_SPEED		= 0.65f;								//移動速度.
	const unsigned int	BOUND_DOWN_FLAG = (1 << 0);								//バウンド下がるフラグ.
	const unsigned int	BOUND_UP_FALG	= (1 << 1);								//バウンド上がるフラグ.
	const float			DISP_SPEED		= 0.1f;									//表示速度.
	const float			ACC_ADD_SPEED	= 1.0f;									//加速度加算速度.
	const float			GRAVITY			= 10.0f;								//重力.
	const float			BOUND_SPEED		= 0.2f;									//バウンド速度.
	const int			JUMP_MAX		= 2;									//ジャンプ最大数.
	const int			BOUND_MAX		= 1;									//バウンド最大数.

	//====================関数=======================//.
	void Update();		//更新処理関数.

private:
	//====================関数=======================//.
	void Init();		//初期化処理関数.
	void Release();		//解放処理関数.
	void Move();		//移動処理関数.
	void BoundSprite();	//スプライトのバウンド処理関数.
	void Disp();		//表示処理関数.
	void Jump();		//ジャンプ処理関数.

	//====================変数=======================//.
	float			m_fAcc;				//加速度.
	int				m_JumpCnt;			//ジャンプカウント.
	unsigned int	m_BoundFlag;		//バウンドフラグ.
};

#endif	//#ifndef CSHOUT_H.