#include "CSurpriesDegreeString.h"

/**********************************************
*		驚かし度文章クラス.
*******************/
CSurpriseDegreeString::CSurpriseDegreeString()
{
	//初期化処理関数.
	Init();
}

CSurpriseDegreeString::~CSurpriseDegreeString()
{
	//解放処理関数.
	Release();
}

//==================================================.
//		更新処理関数.
//==================================================.
void CSurpriseDegreeString::Update()
{

}

//==================================================.
//		初期化処理関数.
//==================================================.
void CSurpriseDegreeString::Init()
{
	m_pCSpriteUI = m_pCResourceManager->GetSpriteUI(enSpriteUI::SurpriseDegree);
}

//==================================================.
//		解放処理関数.
//==================================================.
void CSurpriseDegreeString::Release()
{

}