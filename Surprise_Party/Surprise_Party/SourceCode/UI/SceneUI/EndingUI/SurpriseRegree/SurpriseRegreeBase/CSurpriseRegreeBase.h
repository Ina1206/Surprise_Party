#ifndef CSURPRSEI_REGREE_BASE_H
#define CSURPRSEI_REGREE_BASE_H

#include "..\..\..\..\CUI.h"

/****************************************
*		驚かし度の基底クラス.
**********************/
class CSurpriseRegreeBase
	: public CUI
{
public:
	CSurpriseRegreeBase();
	virtual ~CSurpriseRegreeBase();

	//===================定数====================//.
	const D3DXVECTOR3 EATCH_SCALE_MAX = D3DXVECTOR3(1.0f, 1.0f, 1.0f);	//それぞれの大きさ最大値.

	//===================関数====================//.
	virtual void Update() = 0;		//更新処理関数.
	void Render();					//描画処理関数.
	
protected:

	//===================変数====================//.
	CSpriteUI*	m_pCSpriteUI;		//スプライトUI.
	D3DXVECTOR3 m_vEatchSizeScale;	//それぞれの大きさ.

private:
};

#endif	//#ifndef CSURPRSEI_REGREE_BASE_H.