#ifndef CBIG_GHOST_H
#define CBIG_GHOST_H

#include "..\CGhostBase.h"
#include "..\..\SpriteEffect\SleepEffect\CSleepEffect.h"
#include "..\..\SpriteEffect\HaveTroubleEffect\CHaveTroubleEffect.h"
#include "..\..\SpriteEffect\RejoiceEffect\CRejoiceEffect.h"
#include "..\..\SpriteEffect\QuestionEffect\CQuestionEffect.h"

/******************************************
*		大きいお化けクラス.
**********/
class CBigGhost
	: public CGhostBase
{
public:
	CBigGhost();
	~CBigGhost();


	//=================関数====================//.
	const D3DXVECTOR3	BASE_PRE_POS		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//基準の座標.
	const D3DXVECTOR3	BASE_PRE_ROT		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//
	const D3DXVECTOR3	SLEEP_POS			= D3DXVECTOR3(6.0f, -0.8f, 10.5f);	//寝てる場所.
	const D3DXVECTOR3	SLEEP_ROT			= D3DXVECTOR3(0.0f, -1.35f, 0.0f);	//寝てる角度.
	const D3DXVECTOR3	WAKE_UP_POS			= D3DXVECTOR3(6.0f, 0.7f, 11.2f);	//起きる場所.
	const D3DXVECTOR3	WAKE_UP_ROT			= D3DXVECTOR3(-1.35f, 0.0f, 0.0f);	//起きる角度.
	const D3DXVECTOR3	HAVE_TROUBLE_POS	= D3DXVECTOR3(6.0f, 1.5f, 11.2f);	//困る感情時の座標.
	const D3DXVECTOR3	HAVE_TROUBLE_ROT	= D3DXVECTOR3(-2.4f, 0.0f, 0.0f);	//困る感情の角度.
	const float			SLEEP_ANIM_SPEED	= 0.02f;							//寝てる時のアニメーション速度.
	const int			SLEEP_DIRECT		= -1;								//睡眠方向.
	const float			WAKE_UP_ANIM_SPEED	= 0.0f;								//起きる時のアニメーション速度.
	const double		WAKE_UP_ANIM_POS	= -1.0;								//起きているときのアニメーション位置.
	const float			WAKE_UPING_SPEED	= 0.03f;							//起きる速度.
	const int			WAKE_UP_TIMING		= 600;								//起きるタイミング.
	const int			WAKE_UP_DIRECT		= 1;								//起きる方向.
	const float			HAVE_TROUBLE_SPEED	= 0.025f;							//困る感情行動速度.
	const float			HAVE_TROUBLE_ROT_MAX= 0.7f;								//困る感情行動角度最大値.
	const int			CHANGE_DIRECTION	= -1;								//方向変更.

	const int			FALL_DOWN_DIRECTION = 1;								//倒れる方向.
	const int			UP_DIRECTION		= -1;								//上がる方向.

	const float			LEAN_SPEED			= 0.05f;							//傾く速度.
	const float			REJOICE_MOVE_SPEED	= 0.02f;							//喜び移動速度.
	const float			REJOICE_ROT_MAX		= 0.4f;								//喜び角度最大数.
	const float			REJOICE_ROT_SPEED	= 0.01f;							//喜び傾き速度.

	const float			QUESTION_LEAN_SPEED = 0.02f;							//疑問傾く速度.
	const float			QUESTION_LEAN_MIN	= -30.0f;							//疑問傾く最小値.

	const float			VIEW_PRE_POS_Y		= 10.0f;							//見るときの高さ.

	const float			SCALE				= 0.1f;								//大きさ.

	const unsigned int	MOVING_ROT_FLAG		= (1 << 0);							//角度移動フラグ.
	const unsigned int	MOVING_POS_FLAG		= (1 << 1);							//座標移動フラグ.
	const unsigned int	SWING_FLAG			= (1 << 2);							//揺れるフラグ.

	//=================関数====================//.
	void Update();		//更新処理関数.
	void Render();		//描画処理科数.

	//===========情報取得処理関数==============//.
	bool GetSleepFlag() const { return m_bSleepFlag; }				//眠りフラグ.
	bool GetSkipFlag() const { return m_bSkipFlag; }				//スキップフラグ.

	//===========情報置換処理関数==============//.
	void SetSkipFlag(const bool& bFlag) { m_bSkipFlag = bFlag; }	//スキップフラグ.

private:
	//=================関数====================//.
	void Init();							//初期化処理関数.
	void Release();							//解放処理関数.
	void WakeUp();							//起床処理関数.
	void HaveTroubleEmotion();				//困る感情処理関数.
	void RejoiceEmotion();					//喜ぶ感情処理関数.
	void QuestionEmotion();					//疑問感情処理関数.
	void Sleep();							//寝る処理関数.
	void Lean(const int& Direction);		//傾く処理関数.
	void FallDown(const int& Direction);	//倒れる処理関数.
	void ChangeEffect();					//エフェクト変更処理関数.
	void EmotionMove();						//感情移動処理関数.

	//==================変数====================//.
	CDX9SkinMesh*									m_pCSkinMesh;			//スキンメッシュ.
	double											m_dCntAnimSpeed;		//アニメーション速度カウント.
	float											m_fAnimSpeed;			//アニメーション速度.
	int												m_AnimNum;				//アニメーション番号.

	D3DXVECTOR3										m_vPreRot;				//角度初期設定.

	int												m_WakeUpCnt;			//起きるカウント.
	int												m_LeanDirect;			//傾く方向.
	int												m_UpDownDirect;			//上下方向.
	unsigned int									m_HaveTroubleActFlag;	//困る感情行動フラグ.
	bool											m_ChangeEmotionFlag;	//感情変更フラグ.
	std::vector<std::unique_ptr<CSpriteEffectBase>>	m_pCSpriteEffect;		//スプライトエフェクト.
	int												m_UsingEffectNum;		//使っているエフェクト番号.
	int												m_OldEmotionNum;		//前の感情番号.

	bool											m_bSleepFlag;			//眠りフラグ.
	bool											m_bSkipFlag;			//スキップフラグ.
};


#endif	//#ifndef CBIG_GHOST_H.