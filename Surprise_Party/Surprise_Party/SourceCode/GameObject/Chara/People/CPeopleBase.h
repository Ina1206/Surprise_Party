#ifndef CPEOPLE_BASE_H
#define CPEOPLE_BASE_H

#include "..\CCharaBase.h"
#include "..\..\SpriteEffect\SurpriseEffect\CSurpriseEffect.h"

class CPeopleBase
	: public CCharaBase
{
public:
	CPeopleBase();
	virtual ~CPeopleBase();

	//=================定数======================//.
	const unsigned int	SURPRISE_PRE		= (1 << 0);							//驚く準備.
	const unsigned int	SURPRISE_ACT		= (1 << 1);							//驚く行動.
	const D3DXVECTOR3	PERSON_ROT			= D3DXVECTOR3(0.0f, -1.5f, 0.0f);	//人の角度.
	const int			FAR_NUM				= -1;								//遠い人番号.
	const float			ACCELERATION_SPEED	= 0.02f;							//加速速度.
	const float			BASE_ANIM_SPEED		= 0.02f;							//基本アニメーション速度.
	const float			SCALE				= 0.1f;								//人の大きさ.
	const int			DECREMENT_POINT		= 1;								//ポイント減少.
	const float			ADD_ANIM_SPEED		= 0.005f;							//追加アニメーション速度.
	const D3DXVECTOR3 EFFECT_POS_ADJUSTMENT = D3DXVECTOR3(0.0f, 4.0f, -0.5f);	//エフェクト座標調整.
	const int			TUTORIAL_ANIM_NO	= 3;								//チュートリアル時アニメーション番号.

	//================列挙体=====================//.
	//人の種類.
	enum class enHumanType {
		Girl = 0,		//女の子.
		Boy,			//男の子.

		Max,			//最大値.
		Start = Boy,	//開始.
	};
	//ステータス.
	enum class enStatus {
		MoveSpeed = 0,		//移動速度.
		Scared,				//怖がり度.

		Max,				//最大値.
		Start = MoveSpeed,	//開始.
	};

	//=================関数======================//.
	void Render();			//描画処理関数.

	//============情報置換処理関数===============//.
	//ステージの最大数.
	void SetStageMax(const float& StageMax) { m_fStageMax = StageMax; }
	//驚くフラグ.
	void SetSurpriseFlag(const float& bFlag) { m_bSurpriseFlag = bFlag; }
	//近づいたときの人番号.
	void SetHumanNearNum(const int& Num) { m_HumanNearNum = Num; }
	//驚いた人最大数.
	void SetSurpriseHumanMax(const int& Max) { m_SurpriseHumanMax = Max; }
	//チュートリアルフラグ.
	void SetTutorialFlag(const bool& bFlag) { m_bTutorialFlag = bFlag; }

	//=============情報獲得処理関数==============//.
	//追加ポイント量.
	int GetAddPointQuantity(int NearNo);

protected:
	//=================関数======================//.
	void DispDecision();							//表示判定処理関数.
	void AnimCtrlCreat();							//アニメーションコントローラ作成処理関数.
	void HumanMove();								//人の移動処理関数.
	void SurpriseAnimChange(int surpriseAnimNo);	//驚きアニメーション変更処理関数.

	//=================変数======================//.
	CDX9SkinMesh*						m_pCSkinMesh;		//スキンメッシュ.
	float								m_fAnimSpeed;		//アニメーション速度.
	float								m_fWalkAnimSpeed;	//歩きアニメーション速度.
	float								m_fStageMax;		//ステージ最大距離.
	float								m_fMoveSpeed;		//移動速度.
	int									m_SurpriseQuantity;	//驚きポイント量.
	LPD3DXANIMATIONCONTROLLER			m_pAnimCtrl;		//アニメーションコントローラ.
	bool								m_bSurpriseFlag;	//驚くフラグ.
	int									m_AnimNo;			//アニメーション番号.
	int									m_WalkAnimNo;		//歩きアニメーション番号.
	unsigned int						m_SurpriseActFlag;	//驚く行動フラグ.
	std::unique_ptr<CSurpriseEffect>	m_pCSurpriseEffect;	//エフェクトクラス.
	D3DXVECTOR3							m_vEffectCenterPos;	//エフェクト中心座標.

private:
	//=================関数======================//.
	void SpeedAcceleration();						//速度加速処理関数.

	//=================変数======================//.
	double						m_AnimTime;			//アニメーション時間.
	int							m_HumanNearNum;		//近づいたときの人間番号.
	int							m_SurpriseHumanMax;	//驚いた人最大数.
	bool						m_bTutorialFlag;	//チュートリアルフラグ.
};

#endif	//#ifndef CPEOPLE_BASE_H.