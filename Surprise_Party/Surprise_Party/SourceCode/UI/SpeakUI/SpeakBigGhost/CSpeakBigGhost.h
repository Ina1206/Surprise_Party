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
	const float		STRING_WIDTH_MAX	= 950.0f;		//文章の幅最大数.
	const float		ALPHA_MIN			= 0.0f;			//透過値最小値.
	const float		ALPHA_MAX			= 1.0f;			//透過値最大値.
	const float		ALPHA_SPEED			= 0.1f;			//透過値速度.
	const float		FONT_SCALE			= 50.0f;		//文字の大きさ.

	//======================関数=======================//.
	void Update();			//更新処理関数.
	void Render();			//描画処理関数.

private:
	//======================関数========================//.
	void Init();					//初期化処理関数.
	void Release();					//解放処理関数.
	void LoadSpeakString();			//会話文章読み込み処理関数.
	void TransparentFont();			//文字透過処理関数.

	//======================変数========================//.
	std::vector<CSpriteUI*>		m_pCSpriteUI;		//スプライトUI.
	std::vector<D3DXVECTOR3>	m_vPos;				//座標.
	std::vector<D3DXVECTOR3>	m_vRot;				//角度.
	std::vector<float>			m_fAlpha;			//透過値.
	std::vector<float>			m_fScale;			//大きさ.

	bool						m_bSelectFlag;		//選択フラグ.

	std::vector<std::string>	m_stSpeakString;	//会話文章.
	int							m_SpeakNum;			//会話番号.
	float						m_fFontAlpha;		//文字透過値.
	int							m_ChangingFontNum;	//変更中のフォント番号.
	bool						m_bChangeStringFlag;//文章変更フラグ.
};


#endif	//#ifndef CSPEAK_BIG_GHOST_H.