#include "CStageMap.h"

CStageMap::CStageMap()
{
	//�����������֐�.
	Init();
}

CStageMap::~CStageMap()
{
	//��������֐�.
	Release();
}

//=================================.
//		�����������֐�.
//=================================.
void CStageMap::Init()
{
	m_pCSpriteUI = m_pCResourceManager->GetSpriteUI(enSpriteUI::StageMap);
	m_vPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//=================================.
//		��������֐�.
//=================================.
void CStageMap::Release()
{

}