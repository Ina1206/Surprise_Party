#ifndef INTERMEDIATE_EVALUATION_STRING_H
#define INTERMEDIATE_EVALUATION_STRING_H

#include "..\EvaluationUIBase\CEvaluationUIBase.h"

/***************************************
*		中間評価の文章クラス.
***************/
class CIntermediateEvaluationString
	: public CEvaluationUIBase
{
public:
	CIntermediateEvaluationString();
	~CIntermediateEvaluationString();

	//==========================定数==========================//.
	const D3DXVECTOR3	BASE_POS				= D3DXVECTOR3(100.0f, 100.0f, 0.0f);//基準座標.

	const unsigned int	FINISH_SCALE_FLAG		= (1 << 0);							//拡大終了フラグ.
	const unsigned int	FINISH_ROTATION_FLAG	= (1 << 1);							//回転終了フラグ.

	const D3DXVECTOR3	SCALE_SPEED				= D3DXVECTOR3(0.05f, 0.05f, 0.05f);	//拡大速度.
	const float			ROTATION_SPEED			= 0.2f;								//回転速度.
	const float			ROT_MAX					= 360.0f;							//角度最大値.

	//==========================関数==========================//.
	void Update();					//更新処理関数.

private:
	//==========================関数==========================//.
	void Init();					//初期化処理関数.
	void Release();					//解放処理関数.
	void Scale();					//拡大処理関数.
	void Rotation();				//回転処理関数.
	void DisplayAllAtOnce();		//一気に表示処理関数.

	//==========================変数==========================//.
	unsigned int m_ActFinishFlag;	//行動終了フラグ.

};


#endif	//#ifndef INTERMEDIATE_EVALUATION_STRING_H