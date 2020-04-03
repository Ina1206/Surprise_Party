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

	//===================�֐�======================//.
	virtual void Update() = 0;	//�X�V�����֐�.
	
protected:
	//===================�ϐ�======================//.
	CFontResource*	m_pCFontResource;	//�t�H���g�ǂݍ��݃N���X.
};


#endif	//#ifndef CSPEAK_UI_H.