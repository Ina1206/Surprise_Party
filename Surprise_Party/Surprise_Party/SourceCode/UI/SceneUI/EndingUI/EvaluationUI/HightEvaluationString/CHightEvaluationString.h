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

	//=====================関数======================//.
	void Update();		//更新処理関数.

protected:
	//=====================関数======================//.
	void Init();		//初期化処理関数.
	void Release();		//解放処理関数.
	void Move();		//移動処理関数.
	void Jump();		//ジャンプ処理関数.
	void Bound();		//バウンド処理関数.

	//=====================変数======================//.
	float	m_fAcc;			//加速度.
	int		m_JumpCnt;		//ジャンプカウント.
	int		m_BoundCnt;		//バウンドカウント.
};

#endif	//#ifndef CHIGHT_EVALUATION_STRING_H.