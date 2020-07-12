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
	//移動処理関数.
	Move();

	//透過処理関数.
	Transparent();
}

//==================================================.
//		初期化処理関数.
//==================================================.
void CSurpriseDegreeString::Init()
{
	m_pCSpriteUI = m_pCResourceManager->GetSpriteUI(enSpriteUI::SurpriseDegree);
	m_vEatchSizeScale = EATCH_SCALE_MAX;
	m_vPos = INIT_POS;

	m_fAlpha = ALPHA_MIN;
}

//==================================================.
//		解放処理関数.
//==================================================.
void CSurpriseDegreeString::Release()
{

}

//==================================================.
//		移動処理関数.
//==================================================.
void CSurpriseDegreeString::Move()
{
	m_vPos.y += MOVE_SPEED;

	if (m_vPos.y >= FINISH_POS.y) {
		m_vPos = FINISH_POS;
	}
}

//===================================================.
//		透過処理関数.
//===================================================.
void CSurpriseDegreeString::Transparent()
{
	//距離.
	const float DISTANCE = FINISH_POS.y - INIT_POS.y;
	//時間.
	const float TIME = DISTANCE / MOVE_SPEED;
	//速度.
	const float SPEED = ALPHA_MAX / TIME;
	//透過処理.
	m_fAlpha += SPEED;
	if (m_fAlpha > ALPHA_MAX) {
		m_fAlpha = ALPHA_MAX;
		m_bDispFlag = true;
	}
}