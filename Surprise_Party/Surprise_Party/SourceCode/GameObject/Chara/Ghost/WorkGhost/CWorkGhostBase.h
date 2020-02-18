#ifndef CWORK_GHOST_BASE_H
#define CWORK_GHOST_BASE_H

#include "..\CGhostBase.h"
#include "..\..\..\..\UI\GameWorldUI\Act_Selection\CAct_Selection.h"
#include "..\..\..\..\UI\MapUI\CharaUI\Icon\GhostIcon\CGhostIcon.h"
#include "..\..\..\..\UI\GameWorldUI\GhostStrengthIcon\CGhostStrengthIcon.h"

/*************************************
*		働くお化け基底クラス.
******/
class CWorkGhostBase
	: public CGhostBase
{
public:
	CWorkGhostBase();
	virtual ~CWorkGhostBase();

	//==============定数=================//.
	//m_MoveFlag.
	const unsigned int	SURPRISE_FLAG		= (1 << 0);							//驚かしているフラグ.
	const unsigned int	SELECT_FLAG			= (1 << 1);							//選択フラグ.
	const unsigned int	SELECT_ACT_FLAG		= (1 << 2);							//選択行動フラグ.
	const unsigned int	MOVE_FLAG			= (1 << 3);							//移動フラグ.
	const unsigned int	REST_FLAG			= (1 << 4);							//休憩フラグ.
	const unsigned int	SELECT_STOP_FLAG	= (1 << 5);							//選択戻るフラグ.
	//m_SurpriseFlag.
	const unsigned int	GIMMICK_TOP_FLAG	= (1 << 0);							//ギミックの上にいるかフラグ.	
	const unsigned int	HUMAN_NEAR_FLAG		= (1 << 1);							//人が近づいているかフラグ.
	const unsigned int	SURPRISE_ACT_FLAG	= (1 << 2);							//人を驚かしているかどうかフラグ.
	const unsigned int	SURPRISE_REST_FLAG	= (1 << 3);							//驚き休憩フラグ.
	//m_RestFlag.
	const unsigned int	REST_PREPARAT_FLAG	= (1 << 0);							//休憩準備フラグ.
	const unsigned int	IN_REST_FLAG		= (1 << 1);							//休憩中フラグ.
	const unsigned int	RESURRECTION_FLAG	= (1 << 2);							//復活フラグ.
	//m_UpDownObjectFlag.
	const unsigned int	DOWN_FLAG			= (1 << 0);							//下げるフラグ.
	const unsigned int	UP_FLAG				= (1 << 1);							//上げるフラグ.

	const float			COLOR_MAX			= 255.0f;							//色の最大値.
	const float			ANGLE_SPEED			= 0.1f;								//角度追加速度.
	const float			ANGLE_MAX			= 360.0f;							//角度最大値.
	const float			ANGLE_MIN			= 0.0f;								//角度最小値.
	const float			UP_DOWN_SPEED		= 0.01f;							//上下移動の速度.
	const float			VERTICAL_WIDTH		= 2.5f;								//縦の幅.
	const float			ADJUSTMENT_WIDTH	= 0.1f;								//幅調整.
	const float			NEAR_SENTER_ADJUST	= 5.0f;								//近づく判定中央差分.
	const float			GIMMICK_UP_DECISION = 0.1f;								//ギミックの上に乗っているかの判定差分.
	const float			SURPRISE_POS_ADJUST = 2.5f;								//驚く場所の差分.
	const int			NOT_SURPRISE_NUM	= -1;								//誰も驚いていないときの番号.
	const float			HUMAN_HIT_SCALE		= 1.0f;								//人が驚く当たり判定大きさ.
	const float			SURPRISE_HIT_SCALE	= 0.5f;								//人が驚く場所の当たり判定大きさ.
	const D3DXVECTOR3	REST_ROTATION_SPEED = D3DXVECTOR3(0.02f, 0.03f, 0.0f);	//回復回転速度.
	const float			REST_MOVE_SPEED		= 0.02f;							//回復移動速度.
	const float			REST_SCALE_SPEED	= 0.002f;							//回復大きさ速度.
	const D3DXVECTOR3	REST_ROTATION_MAX	= D3DXVECTOR3(1.5f, 2.5f, 0.0f);	//回復回転最大数.
	const float			REST_MOVE_MAX		= 1.5f;								//回復移動最大数.
	const float			REST_SCALE_MIN		= 0.0f;								//回復大きさ最小.
	const float			BASIC_REDUCE_SPEED	= 0.01f;							//基本体力減らす速度.
	const float			MOVE_REDUCE_SPEED	= 0.015f;							//移動時の体力減る速度.
	const float			CAMERA_DISP_RANGE	= 15.0f;							//表示カメラ範囲.
	const float			ROT_SPEED			= 0.1f;								//角度の速度.
	const float			ROT_MAX				= 1.35f;							//角度の最大値.
	const float			ROT_MIN				= 0.0f;								//角度の最小値.
	const float			ROT_MIN_ADJUST		= 0.1f;								//角度最小値微調整.
	const int			SURPRISE_REST_MAX	= 120;								//驚かし休憩最大時間.

	//=============列挙体================//.
	//お化けの種類.
	enum class enGhostType {
		DispGhost,			//現れるお化け.
		SwitchGhost,		//スイッチ押すお化け.

		Max,				//最大値.
		Start = DispGhost,	//開始値.
	};

	//ステータス.
	enum class enStatus {
		Strength,			//体力.
		MoveSpeed,			//移動速度.
		RecoverySpeed,		//回復速度.
		SurprisePoint,		//驚きポイント.
	};

	//===============関数=================//.
	void SelectRender();								//行動選択描画処理関数.
	void StrengthIconRender();							//体力アイコン描画処理関数.

	//=========情報置換処理関数===========//.
	//選択フラグ.
	void SetSelectFlag(const bool& flag) { m_bSelectFlag = flag; }
	//ステージ最大距離.
	void SetStageDistanceMax(const float& fDistance) { m_fStageMaxDistance = fDistance; }
	//お化けアイコン選ばれているフラグ.
	void SetGhostSelectIcon(const bool& bFlag) { m_bGhostSelectIcon = bFlag; }
	//目的ギミック座標取得.
	void SetObjectiveGimmickPos(const D3DXVECTOR3& vPos) { m_vObjectiveGimmickPos = vPos; }
	//ギミック選択変更フラグ.
	void SetChangeGimmickSelect(const bool& flag) { m_bChangeGimmickSelect = flag; }
	//驚かすための座標情報取得.
	void SetSurprisePosInfo(const std::vector<D3DXVECTOR3>& vGimmickPos, const std::vector<D3DXVECTOR3>& vHumanPos) {
		m_vGimmickPos	= vGimmickPos;
		m_vHumanPos		= vHumanPos;
	}
	//初めの位置設定.
	void SetInitMovePos() { m_vMovePos = m_vPos; }
	//驚かすオブジェクト設定.
	void SetSurpriseObjectType(const CGameObject::enSurpriseObjectType& enType) {
		m_enSurpriseObjectType = enType;
	}
	//使っているギミック番号.
	void SetUsingGimmickNum(const int& GimmickNum) { m_UsingGimmickNum = GimmickNum; }
	//選択中止設定.
	void SetSelectStop() { m_MoveFlag |= SELECT_STOP_FLAG; }

	//=========情報獲得処理関数===========//.
	//選択フラグ.
	bool GetSelectFlag() { return m_bSelectFlag; }
	//ギミック選択変更フラグ.
	bool GetChangeGimmickSelect() { return m_bChangeGimmickSelect; }
	//驚かすオブジェクト種類.
	enSurpriseObjectType GetSurpriseObjectType(){ return m_enSurpriseObjectType; }
	//人が驚いたフラグ.
	bool GetHumanSurpriseFlag() { return m_bHumanSurpriseFlag; }
	//驚いた人番号.
	int	GetSurpriseHumanNum() { return m_SurpriseHumanNum; }
	//使うギミック番号.
	int GetUseGimmickNum() { return m_UseGimmickNum; }
	//移動フラグ.
	unsigned int GetMoveFlag() { return m_MoveFlag; }
	//上下オブジェクトフラグ.
	unsigned int GetUpDownFlag() { return m_UpDownObjectFlag; }
	//近くにいる人の番号.
	std::vector<int> GetNearHumanNum() { return m_NearHumanNum; }
	//使っているギミック番号.
	int GetUsingGimmickNum() { return m_UsingGimmickNum; }

protected:
	//===============関数=================//.
	void	SelectUpDate();									//選択更新処理関数.
	void	GhostIconUpDate();								//お化けアイコン更新処理関数.
	HRESULT	SurpriseActDecide();							//驚かす行動を決める処理関数.
	HRESULT SurpriseHit();									//驚かす当たり判定処理関数.
	void	DebugHitSphereRender();							//デバッグ用球体描画処理関数.
	void	StrengthIconUpDate();							//体力アイコン更新処理関数.
	void	MoveSpeedChange();								//移動速度変更処理関数.
	void	MovePosReference();								//移動更新処理関数.

	virtual void SurpriseAct()			= 0;				//驚かす行動処理関数.
	virtual void ChangeObjectUpDown()	= 0;				//上下移動変更処理関数.
	virtual void ReturnMove()			= 0;				//戻る移動処理関数.

	//===============変数=================//.
	std::unique_ptr<CAct_Selection>		m_pCAct_Selection;		//行動選択クラス.
	unsigned int						m_MoveFlag;				//行動フラグ.
	bool								m_bSelectFlag;			//選択フラグ.
	unsigned int						m_ActType;				//選択内容フラグ.
	float								m_fStageMaxDistance;	//ステージ最大距離.
	std::unique_ptr<CGhostIcon>			m_pCGhostIcon;			//お化けアイコン.
	bool								m_bGhostSelectIcon;		//お化けが選ばれているかどうか.
	D3DXVECTOR3							m_vObjectiveGimmickPos;	//目的ギミック座標.
	bool								m_bChangeGimmickSelect;	//ギミック選択変更フラグ.
	enSurpriseObjectType				m_enSurpriseObjectType;	//驚かすオブジェクト種類.
	float								m_fStrength;			//体力.
	float								m_fStrengthMax;			//体力最大数.
	float								m_fMoveSpeed;			//移動速度.
	float								m_fMoveSpeedMax;		//移動速度最大数.
	float								m_fRecoverySpeed;		//休憩時間.
	unsigned int						m_SurpriseFlag;			//驚かしているフラグ.
	unsigned int						m_RestFlag;				//休憩フラグ.
	float								m_fScaleMax;			//大きさ最大数.
	std::unique_ptr<CGhostStrengthIcon>	m_pCGhostStrengthIcon;	//お化けの体力アイコン.
	unsigned int						m_UpDownObjectFlag;		//上下オブジェクトフラグ.
	D3DXVECTOR3							m_vMovePos;				//移動している座標.
	D3DXVECTOR3							m_vSurpriseBeforePos;	//驚かす前の座標.
	D3DXVECTOR3							m_vStrengthIconPos;		//体力アイコン座標.
	float								m_fMoveFinishHight;		//移動終了後の高さ.
	bool								m_bNowHumanSurprise;	//現在人が驚くフラグ.

private:
	//===============関数===================//.
	void  SelectAfterActivity();								//選択後の行動処理関数.
	void  RestAct();											//休憩処理関数.
	void  MoveGimmick();										//ギミック移動処理関数.
	void  RestMove(float* pfVar, float fSpped, float fMax);		//休憩移動処理関数.
	void  Resurrection(float* pfVar, float fSpeed, float fMin);	//回復処理関数.

	//===============変数===================//.
	int									m_MoveDirection;		//移動方向.
	float								m_fMoveAngle;			//移動角度.
	std::vector<D3DXVECTOR3>			m_vGimmickPos;			//ギミック座標.
	std::vector<D3DXVECTOR3>			m_vHumanPos;			//人の座標.
	D3DXVECTOR3							m_vSurprisePos;			//驚く場所.
	std::vector<CDX9Mesh*>				m_pCHitSphere;			//当たり判定用スフィア.
	std::vector<int>					m_NearHumanNum;			//近くにいる人の番号.
	bool								m_bHumanSurpriseFlag;	//人が驚くフラグ.
	int									m_SurpriseHumanNum;		//驚いた人番号.
	int									m_UseGimmickNum;		//使うギミック番号.
	int									m_OldStrengthType;		//体力種類.
	int									m_SurpriseRestTime;		//驚き休憩時間.
	int									m_UsingGimmickNum;		//使っている番号.

	bool								m_bLimitationRest;		//限界休憩フラグ.
};

#endif	//#ifndef CWORK_GHOST_BASE_H.