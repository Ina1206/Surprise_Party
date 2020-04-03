#include "CSpeakUI.h"

CSpeakUI::CSpeakUI()
	: m_pCFontResource	(nullptr)
	, m_stSpeakString	()
	, m_SpeakNum		(0)
	, m_fFontAlpha		(0.0f)
	, m_ChangingFontNum	(0)
{
	m_pCFontResource = CResourceManager::GetResourceManagerInstance()->GetFont();
}

CSpeakUI::~CSpeakUI()
{
	m_pCFontResource = nullptr;
}
