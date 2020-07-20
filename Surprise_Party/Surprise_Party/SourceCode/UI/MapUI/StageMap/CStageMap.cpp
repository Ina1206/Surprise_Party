#include "CStageMap.h"

/**************************************
*		ステージマップクラス.
********/
CStageMap::CStageMap()
{
	//初期化処理関数.
	Init();
}

CStageMap::~CStageMap()
{
	//解放処理関数.
	Release();
}

//=================================.
//		初期化処理関数.
//=================================.
void CStageMap::Init()
{
	m_pCSpriteUI = m_pCResourceManager->GetSpriteUI(enSpriteUI::StageMap);
	m_vPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//=================================.
//		解放処理関数.
//=================================.
void CStageMap::Release()
{

}