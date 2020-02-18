#ifndef CMAP_UI_H
#define CMAP_UI_H

#include "..\CUI.h"

/******************************************
*		マップUIクラス.
**********/
class CMapUI
	: public CUI
{
public:
	CMapUI();
	virtual ~CMapUI();

	//====================関数========================//.
	void Render();						//描画処理関数.

protected:
	//====================変数========================//.
	CSpriteUI*		m_pCSpriteUI;		//SpriteUIクラス.
	D3DXVECTOR3		m_vColor;			//色(アルファ値を抜く).
	D3DXVECTOR2		m_vPattarn;			//パターン.

};

#endif	//#ifndef CMAP_UI_H.