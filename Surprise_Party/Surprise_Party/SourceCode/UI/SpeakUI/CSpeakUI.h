#ifndef CSPEAK_UI_H
#define CSPEAK_UI_H

#include "..\CUI.h"
#include "..\..\Drawing\Resource\FontResource\CFontResource.h"
#include "..\..\FileLoad\FileResource\CFileResource.h"

class CSpeakUI
	: public CUI
{
public:
	CSpeakUI();
	virtual ~CSpeakUI();

	//===================定数======================//.
	const float		ALPHA_MIN = 0.0f;			//透過値最小値.
	const float		ALPHA_SPEED = 0.1f;			//透過値速度.

	//===================関数======================//.
	virtual void Update() = 0;	//更新処理関数.

	//=============情報取得処理関数================//.
	//全ての文字出現フラグ.
	bool GetAppearancedAllFont() const { return m_bFinishAppearancedAllFont; }
	
protected:
	//===================関数======================//.
	void RenderFont();							//文字描画処理関数.
	void TransparentFont();						//文字透過処理関数.
	bool DesicionChangeString();				//文章変更判定処理関数.

	//===================変数======================//.
	CFontResource*				m_pCFontResource;				//フォント読み込みクラス.
	std::vector<std::string>	m_stSpeakString;				//会話文章.
	std::vector<std::string>	m_stSelectString;				//選択文章.
	int							m_SpeakNum;						//会話番号.
	int							m_ChangingFontNum;				//変更中のフォント番号.
	bool						m_bAppearanceAllFont;			//全ての文字出現フラグ.
	bool						m_bFinishAppearancedAllFont;	//全ての文字出現終了フラグ.

private:
	//===================変数======================//.
	float						m_fFontAlpha;					//文字透過値.
	
};


#endif	//#ifndef CSPEAK_UI_H.