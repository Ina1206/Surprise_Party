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

	//===================�萔======================//.
	const float		ALPHA_MIN = 0.0f;			//���ߒl�ŏ��l.
	const float		ALPHA_SPEED = 0.1f;			//���ߒl���x.

	//===================�֐�======================//.
	virtual void Update() = 0;	//�X�V�����֐�.

	//=============���擾�����֐�================//.
	//�S�Ă̕����o���t���O.
	bool GetAppearancedAllFont() const { return m_bFinishAppearancedAllFont; }
	
protected:
	//===================�֐�======================//.
	void RenderFont();							//�����`�揈���֐�.
	void TransparentFont();						//�������ߏ����֐�.
	bool DesicionChangeString();				//���͕ύX���菈���֐�.

	//===================�ϐ�======================//.
	CFontResource*				m_pCFontResource;				//�t�H���g�ǂݍ��݃N���X.
	std::vector<std::string>	m_stSpeakString;				//��b����.
	std::vector<std::string>	m_stSelectString;				//�I�𕶏�.
	int							m_SpeakNum;						//��b�ԍ�.
	int							m_ChangingFontNum;				//�ύX���̃t�H���g�ԍ�.
	bool						m_bAppearanceAllFont;			//�S�Ă̕����o���t���O.
	bool						m_bFinishAppearancedAllFont;	//�S�Ă̕����o���I���t���O.

private:
	//===================�ϐ�======================//.
	float						m_fFontAlpha;					//�������ߒl.
	
};


#endif	//#ifndef CSPEAK_UI_H.