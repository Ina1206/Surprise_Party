#include "CSpeakUI.h"

CSpeakUI::CSpeakUI()
	: m_pCFontResource(nullptr)
{
	m_pCFontResource = CResourceManager::GetResourceManagerInstance()->GetFont();
}

CSpeakUI::~CSpeakUI()
{
	m_pCFontResource = nullptr;
}
