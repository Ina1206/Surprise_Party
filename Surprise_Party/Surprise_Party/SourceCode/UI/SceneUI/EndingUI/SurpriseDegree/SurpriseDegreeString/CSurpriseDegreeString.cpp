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
	if (GetAsyncKeyState(VK_UP) & 0x8000) {
		m_vPos.y -= 0.5f;
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
		m_vPos.y += 0.5f;
	}
	if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
		m_vPos.x -= 0.5f;
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
		m_vPos.x += 0.5f;
	}
}

//==================================================.
//		初期化処理関数.
//==================================================.
void CSurpriseDegreeString::Init()
{
	m_pCSpriteUI = m_pCResourceManager->GetSpriteUI(enSpriteUI::SurpriseDegree);
	m_vEatchSizeScale = EATCH_SCALE_MAX;
	m_vPos = INIT_POS;
}

//==================================================.
//		解放処理関数.
//==================================================.
void CSurpriseDegreeString::Release()
{

}