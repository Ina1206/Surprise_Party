#ifndef CHIGHT_EVALUATION_STRING_H
#define CHIGHT_EVALUATION_STRING_H

#include "..\EvaluationUIBase\CEvaluationUIBase.h"

/**********************************************
*		高評価文字クラス.
*********************/
class CHightEvaluationString
	: public CEvaluationUIBase
{
public:
	CHightEvaluationString();
	~CHightEvaluationString();

	//=====================定数======================//.
	const D3DXVECTOR3	FINISH_BASE_POS	= D3DXVECTOR3(10.0f, 50.0f, 0.0f);	//最終基準位置.
	const D3DXVECTOR3	INIT_POS		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//初期位置.
	const unsigned int	BOUND_DOWN_FLAG = (1 << 0);							//バウンド下がるフラグ.
	const unsigned int	BOUND_UP_FALG	= (1 << 1);							//バウンド上がるフラグ.
	const float			MOVE_SPEED		= 0.5f;								//移動速度.
	const float			ADD_ACC_SPEED	= 2.0f;								//加速度加算速度.
	const float			GRAVITY			= 20.0f;							//重力.
	const float			JUMP_CNT_MAX	= 2;								//ジャンプカウント最大値.
	const float			BOUND_SPEED		= 0.1f;								//バウンド速度.
	const float			DISP_SPEED		= 0.3f;								//表示速度.

	//=====================関数======================//.
	void Update();					//更新処理関数.

protected:
	//=====================関数======================//.
	void Init();					//初期化処理関数.
	void Release();					//解放処理関数.
	void Disp();					//表示処理関数.
	void Move();					//移動処理関数.
	void Jump();					//ジャンプ処理関数.
	void Bound();					//バウンド処理関数.
	void DisplayAllAtOnce();		//一気に表示する処理関数.

	//=====================変数======================//.
	float			m_fAcc;			//加速度.
	int				m_JumpCnt;		//ジャンプカウント.
	int				m_BoundCnt;		//バウンドカウント.
	unsigned int	m_BoundFlag;	//バウンドフラグ.
};

#endif	//#ifndef CHIGHT_EVALUATION_STRING_H.