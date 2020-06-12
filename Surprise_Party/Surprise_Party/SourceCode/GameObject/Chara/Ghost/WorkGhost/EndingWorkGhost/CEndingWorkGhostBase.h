#ifndef CENDING_WORK_GHOST_BASE_H
#define CENDING_WORK_GHOST_BASE_H

#include "..\CWorkGhostBase.h"

/**************************************************
*		エンディング働くお化け基底クラス.
********************/
class CEndingWorkGhostBase
	: public CWorkGhostBase
{
public:
	CEndingWorkGhostBase();
	virtual ~CEndingWorkGhostBase();

	//========================定数=============================//.
	const unsigned int	FACE_OUTSIDE		= (1 << 0);							//外側を向く.
	const unsigned int	MOVE_OUTSIDE		= (1 << 1);							//外側を移動.

	const D3DXVECTOR3	VECTOR_AXIS_Z		= D3DXVECTOR3(0.0f, 0.0f, 1.0f);	//z軸.
	const float			LOOK_BACK_SPEED		= 0.05f;							//振り返る速度.
	const float			LOOK_BACK_ROT_MAX	= 180.0f;							//振り返る角度最大値.

	const float			MOVE_SPEED			= 0.01f;							//移動速度.

	const float			MOVE_NOTE_ANGLE		= 30.0f;							//音符移動角度.
	const float			PLAY_DISTANCE_MAX	= 6.0f;								//再生距離最大.

	const float			MOVE_DISTANCE_MAX	= 8.0f;								//移動距離最大値.
	const float			SWING_SPEED			= 0.05f;							//揺れる速度.
	const float			SWING_ROTATION_MAX	= 90.0f;							//揺れる角度最大値.

	const int			CHANGE_DIRECT		= -1;								//方向変更.
	
protected:
	//========================関数=============================//.
	void Jump();				//ジャンプ処理関数.
	void ChangeEffect();		//エフェクト変更処理関数.
	void ActGoodFeeling();		//ご機嫌時の行動処理関数.
	void PlayEffectManager();	//エフェクト再生管理処理関数.

	//========================変数=============================//.
	std::unique_ptr<CSpriteEffectBase>	m_pCSpriteEffect;		//スプライトエフェクト.
	float								m_fAcc;					//加速度.
	float								m_fAccSpeed;			//加速度加算速度.
	float								m_fAccMax;				//加速度最大値.
	float								m_fGravity;				//重力.
	D3DXVECTOR3							m_vChangeBeforeRotation;//変更前の角度.
private:
	//========================関数=============================//.
	void MoveToOutside();		//外側に移動する処理関数.
	void FaceOutside();			//外側を向く処理関数.

	//========================変数=============================//.
	int									m_OldEmotionNum;		//差分用の感情番号.
	unsigned int						m_MoveToOuterFlag;		//外側を移動するフラグ.
};

#endif	//#ifndef CENDING_WORK_GHOST_BASE_H.