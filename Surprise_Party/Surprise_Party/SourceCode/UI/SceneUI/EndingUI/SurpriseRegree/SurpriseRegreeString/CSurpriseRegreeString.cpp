#include "CSurpriesRagreeString.h"

/**********************************************
*		驚かし度文章クラス.
*******************/
CSurpriseRegreeString::CSurpriseRegreeString()
{
	//初期化処理関数.
	Init();
}

CSurpriseRegreeString::~CSurpriseRegreeString()
{
	//解放処理関数.
	Release();
}

//==================================================.
//		更新処理関数.
//==================================================.
void CSurpriseRegreeString::Update()
{

}

//==================================================.
//		初期化処理関数.
//==================================================.
void CSurpriseRegreeString::Init()
{
	m_pCSpriteUI = m_pCResourceManager->GetSpriteUI(enSpriteUI::SurpriseDegree);
}

//==================================================.
//		解放処理関数.
//==================================================.
void CSurpriseRegreeString::Release()
{

}