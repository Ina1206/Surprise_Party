#ifndef CMAIN_STAGE_SWITCH_GHOST_H
#define CMAIN_STAGE_SWITCH_GHOST_H

#include "..\CMainStageWorkGhostBase.h"

/**********************************************
*	メインステージのスイッチを押すお化けクラス.
*****************/
class CMainStageSwitchGhost
	: public CMainStageWorkGhostBase
{
public:
	CMainStageSwitchGhost();
	~CMainStageSwitchGhost();

	//=================定数====================//.
	const unsigned int	PUSH_PREPARATION_FALG	= (1 << 0);								//押す準備フラグ.
	const unsigned int	PUSH_BUTTON_FLAG		= (1 << 1);								//ボタンを押す.
	const unsigned int	GO_TO_PUSH_FLAG			= (1 << 2);								//押しに行くフラグ.
	const unsigned int	PUSH_END_FLAG			= (1 << 3);								//押し終わるフラグ.
	const unsigned int	PUSH_RETURN_FLAG		= (1 << 4);								//押して戻るフラグ.
	const unsigned int	MOVE_ROT_CHANGE_FLAG	= (1 << 5);								//移動時角度変更処理関数.
	const D3DXVECTOR3	GHOST_COLOR				= D3DXVECTOR3(202.0f, 255.0f, 250.0f);	//お化けの色.
	const float			SWITHC_GHOST_SCALE		= 0.1f;									//スイッチお化けの大きさ.
	const float			POS_HEIGHT_MIN			= 0.2f;									//高さの最小値.
	const float			STANDERD_POS_HIGHT		= 3.5f;									//基本の高さ.
	const float			RETURN_ROTATION			= -1.35f;								//戻った時の角度.
	const float			DISTANCE_ADJUSTMENT		= 0.2f;									//距離の微調整.
	const float			MOVE_SPEED				= 0.1f;									//移動速度.
	const float			CHANGE_ACT_DISTANCE		= 3.0f;									//行動変更距離.
	const float			GRAVITY					= 0.007f;								//重力.
	const int			DOWN_DIRECTION			= -1;									//下の方向.
	const int			CHANGE_DIRECTION		= -1;									//方向変更.
	const float			PUSH_END_ROT_SPEED		= 0.1f;									//押し終わって回転速度.
	const D3DXVECTOR3	SKY_DIRECT				= D3DXVECTOR3(0.0f, 1.0f, 0.0f);		//空方向.
	const float			CHANGE_UP_DOWN_FLAG_H	= 0.7f;									//上下移動フラグ変更高さ.

	//=================関数====================//.
	void Update();							//更新処理関数.
	void Render();							//描画処理関数.
private:
	//=================関数====================//.
	void Init();							//初期化処理関数.
	void Release();							//解放処理関数.
	void SurpriseAct();						//驚かす行動処理関数.
	void ChangeObjectUpDown();				//上下移動変更処理関数.
	void ReturnMove();						//戻る移動処理関数.
	void PushPreparation();					//押す準備処理関数.
	void PushButton();						//押す処理関数.
	void PushEnd();							//押し終わった処理関数.
	void MoveRotation();					//移動角度処理関数.

	//=================変数====================//.
	unsigned int	m_PushSwitchActFlag;	//ボタンを押すときのフラグ.
	float			m_fGravity;				//重力.
	int				m_UpDownDirection;		//落ちる方向.
	D3DXVECTOR3		m_vPointDistance;		//2点間の距離.
	D3DXVECTOR3		m_vUnitVector;			//単位ベクトル.
	D3DXVECTOR3		m_vOldPos;				//前回の座標.
	D3DXMATRIX		m_mPoint;				
	bool			m_bUseRotFlag;			//角度使用フラグ.
};

#endif	//#ifndef CMAIN_STAGE_SWITCH_GHOST_H.