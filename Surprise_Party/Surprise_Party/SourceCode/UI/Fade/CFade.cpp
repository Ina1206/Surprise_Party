#include "CFade.h"

CFade::CFade()
	: m_pCResourceManager	(nullptr)
{
	m_pCResourceManager = CResourceManager::GetResourceManagerInstance();
}

CFade::~CFade()
{
}
