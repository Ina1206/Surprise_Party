#ifndef CSPEAK_BIG_GHOST_H
#define CSPEAK_BIG_GHOST_H

#include "..\CSpeakUI.h"
#include "..\..\FileLoad\FileResource\CFileResource.h"

/**********************************************
*		ビッグゴーストがしゃべるクラス.
*************/
class CSpeakBigGhost
	: public CSpeakUI
{
public:
	CSpeakBigGhost();
	~CSpeakBigGhost();

	//======================定数=======================//.
	const float		STRING_WIDTH_MAX = 950.0f;		//文章の幅最大数.

	//======================関数=======================//.
	void Update();			//更新処理関数.
	void Render();			//描画処理関数.

private:
	//======================関数========================//.
	void Init();			//初期化処理関数.
	void Release();			//解放処理関数.
	void LoadSpeakString();	//会話文章読み込み処理関数.

	//======================変数========================//.
	std::vector<CSpriteUI*>		m_pCSpriteUI;	//スプライトUI.
	std::vector<D3DXVECTOR3>	m_vPos;			//座標.
	std::vector<D3DXVECTOR3>	m_vRot;			//角度.
	std::vector<float>			m_fAlpha;		//透過値.
	std::vector<float>			m_fScale;		//大きさ.

	bool						m_bSelectFlag;	//選択フラグ.

	std::vector<std::string>	m_stSpeakString;//会話文章.
	int							m_SpeakNum;		//会話番号.
};


#endif	//#ifndef CSPEAK_BIG_GHOST_H.