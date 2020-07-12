#ifndef CSURPRSEI_REGREE_BASE_H
#define CSURPRSEI_REGREE_BASE_H

#include "..\..\..\..\CUI.h"

/****************************************
*		驚かし度の基底クラス.
**********************/
class CSurpriseDegreeBase
	: public CUI
{
public:
	CSurpriseDegreeBase();
	virtual ~CSurpriseDegreeBase();

	//===================定数====================//.
	const D3DXVECTOR3	EATCH_SCALE_MAX = D3DXVECTOR3(1.0f, 1.0f, 1.0f);	//それぞれの大きさ最大値.
	const float			ALPHA_MIN		= 0.0f;								//透過値最小値.

	//===================関数====================//.
	virtual void Update() = 0;		//更新処理関数.
	void Render();					//描画処理関数.
	
	//=============情報取得処理関数==============//.
	//表示フラグ.
	bool GetDispFlag() const { return m_bDispFlag; }

	//=============情報置換処理関数==============//.
	//一気に表示フラグ.
	void SetDisplayAllAtOnce(const bool& bFlag) { m_bDisplayAllAtOnce = bFlag; }

protected:

	//===================変数====================//.
	CSpriteUI*	m_pCSpriteUI;		//スプライトUI.
	D3DXVECTOR3 m_vEatchSizeScale;	//それぞれの大きさ.
	bool		m_bDispFlag;		//表示フラグ.
	bool		m_bDisplayAllAtOnce;//一気に表示フラグ.

private:
};

#endif	//#ifndef CSURPRSEI_REGREE_BASE_H.