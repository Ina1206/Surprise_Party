#ifndef CSPEAK_BIG_GHOST_H
#define CSPEAK_BIG_GHOST_H

#include "..\CSpeakUI.h"

/**********************************************
*		ビッグゴーストがしゃべるクラス.
*************/
class CSpeakBigGhost
	: public CSpeakUI
{
public:
	CSpeakBigGhost();
	~CSpeakBigGhost();

	//======================関数=======================//.
	void Update();	//更新処理関数.
	void Render();	//描画処理関数.

private:
	//======================関数========================//.
	void Init();	//初期化処理関数.
	void Release();	//解放処理関数.

	//======================変数========================//.
	std::vector<CSpriteUI*>		m_pCSpriteUI;	//スプライトUI.
	std::vector<D3DXVECTOR3>	m_vPos;			//座標.
	std::vector<D3DXVECTOR3>	m_vRot;			//角度.
	std::vector<float>			m_fAlpha;		//透過値.
	std::vector<float>			m_fScale;		//大きさ.

	float						m_fFontScale;	//大きさ

	bool						m_bSelectFlag;	//選択フラグ.
};


#endif	//#ifndef CSPEAK_BIG_GHOST_H.