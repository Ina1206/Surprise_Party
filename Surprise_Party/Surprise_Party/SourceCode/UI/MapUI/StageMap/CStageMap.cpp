#include "CStageMap.h"

CStageMap::CStageMap()
{
	//‰Šú‰»ˆ—ŠÖ”.
	Init();
}

CStageMap::~CStageMap()
{
	//‰ğ•úˆ—ŠÖ”.
	Release();
}

//=================================.
//		‰Šú‰»ˆ—ŠÖ”.
//=================================.
void CStageMap::Init()
{
	m_pCSpriteUI = m_pCResourceManager->GetSpriteUI(enSpriteUI::StageMap);
	m_vPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//=================================.
//		‰ğ•úˆ—ŠÖ”.
//=================================.
void CStageMap::Release()
{

}