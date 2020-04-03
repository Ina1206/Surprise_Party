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
	CFontResource*	m_pCFontResource;	//フォント読み込みクラス.
};


#endif	//#ifndef CSPEAK_UI_H.