#ifndef CEVALUATION_UI_BASE_H
#define CEVALUATION_UI_BASE_H

#include "..\..\..\..\CUI.h"
#include "..\..\Sound\PlaySoundManager\CPlaySoundManager.h"

/****************************************
*		評価UIの基底クラス.
*******************/
class CEvaluationUIBase
	: public CUI
{
public:
	CEvaluationUIBase();
	virtual ~CEvaluationUIBase();

	//====================定数========================//.
	const D3DXVECTOR3	EATCH_SCALE_MAX = D3DXVECTOR3(1.0f, 1.0f, 1.0f);	//それぞれの大きさ最大値.
	const D3DXVECTOR3	EATCH_SCALE_MIN = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//それぞれの大きさ最小値
	const float			ALPHA_MIN		= 0.0f;								//透過値最小値.

	//====================関数========================//.
	virtual void Update() = 0;	//更新処理関数.
	void Render();				//描画処理関数.

	//==============情報取得処理関数===================//.
	//全てを表示するフラグ.
	bool GetFinishedAllDispFlag() const { return m_bFinishedAllDispFlag; }

	//==============情報置換処理関数===================//.
	//全て表示するフラグ.
	void SetDisplayAllAtOnce(const bool& bFlag) { m_bDisplayAllAtOnce = bFlag; }

protected:
	//====================関数=========================//.
	void InitElementCount();	//要素数と初期値の初期化処理関数.

	//====================変数=========================//.
	std::vector<CSpriteUI*>		m_pCEvaluationUI;			//評価UI.
	std::vector<D3DXVECTOR3>	m_vEvaluationPos;			//表示座標.
	D3DXVECTOR3					m_vPrePos;					//中心軸を動かす座標.
	std::vector<D3DXVECTOR3>	m_vEvaluationRot;			//角度.
	std::vector<D3DXVECTOR3>	m_vEvaluationScale;			//大きさ.
	std::vector<D3DXVECTOR2>	m_vEvaluationUV;			//UV座標.
	std::vector<float>			m_fEvaluationAlpha;			//透過値.

	SPRITE_STATE				m_stSpriteState;			//スプライト情報.

	bool						m_bFinishedAllDispFlag;		//全て表示するフラグ.
	bool						m_bDisplayAllAtOnce;		//一気に表示するフラグ.
	int							m_UpdateNum;				//更新する番号.

	CPlaySoundManager*			m_pCPlaySoundManager;		//音再生管理クラス.
};

#endif	//#ifndef CEVALUATION_UI_BASE_H.