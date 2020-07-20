#include "CFade.h"

/******************************************
*		�t�F�[�h�N���X.
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
