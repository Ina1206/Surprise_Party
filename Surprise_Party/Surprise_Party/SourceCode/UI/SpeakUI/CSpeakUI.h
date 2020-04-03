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

	//===================関数======================//.
	virtual void Update() = 0;	//更新処理関数.
	
protected:
	//===================変数======================//.
	CFontResource*				m_pCFontResource;	//フォント読み込みクラス.
	std::vector<std::string>	m_stSpeakString;	//会話文章.
	std::vector<std::string>	m_stSelectString;	//選択文章.
	int							m_SpeakNum;			//会話番号.
	float						m_fFontAlpha;		//文字透過値.
	int							m_ChangingFontNum;	//変更中のフォント番号.
};


#endif	//#ifndef CSPEAK_UI_H.