#include "CFade.h"

/******************************************
*		フェードクラス.
***********/
CFade::CFade()
	: m_pCResourceManager	(nullptr)
	, m_pCPlaySoundManager	(CPlaySoundManager::GetPlaySoundManager())
{
	m_pCResourceManager = CResourceManager::GetResourceManagerInstance();
}

CFade::~CFade()
{
}
