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

	const int		SELECT_MAX			= 2;			//選択最大数.

	const unsigned int TRANSPARENTING_FLAG	= (1 << 0);	//透過処理中フラグ.
	const unsigned int SELECT_FLAG			= (1 << 1);	//選択フラグ.
	const unsigned int SELECTED_STRING_FLAG = (1 << 2);	//選択した文章フラグ.

	//======================関数=======================//.
	void Update();			//更新処理関数.
	void Render();			//描画処理関数.

private:
	//======================関数========================//.
	void Init();					//初期化処理関数.
	void Release();					//解放処理関数.
	void LoadSpeakString();			//会話文章読み込み処理関数.
	void TransparentFont();			//文字透過処理関数.
	void DecisionSelectString();	//選択文章処理関数.
	void SelectingMove();			//選択中移動処理関数.

	//======================変数========================//.
	std::vector<CSpriteUI*>		m_pCSpriteUI;		//スプライトUI.
	std::vector<D3DXVECTOR3>	m_vPos;				//座標.
	std::vector<D3DXVECTOR3>	m_vRot;				//角度.
	std::vector<float>			m_fAlpha;			//透過値.
	std::vector<float>			m_fScale;			//大きさ.

	std::vector<std::string>	m_stSpeakString;	//会話文章.
	std::vector<std::string>	m_stSelectString;	//選択文章.
	int							m_SpeakNum;			//会話番号.
	float						m_fFontAlpha;		//文字透過値.
	int							m_ChangingFontNum;	//変更中のフォント番号.
	unsigned int				m_StringFlag;		//文章フラグ.
	int							m_SelectNum;		//選択番号.
	int							m_SelectCnt;		//選択カウント.

};


#endif	//#ifndef CSPEAK_BIG_GHOST_H.