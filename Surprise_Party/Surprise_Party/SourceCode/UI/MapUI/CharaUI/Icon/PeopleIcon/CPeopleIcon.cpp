#include "CPeopleIcon.h"

CPeopleIcon::CPeopleIcon()
	: m_bSurpriseFlag		(false)
	, m_fAcc				(0.0f)
{

}

CPeopleIcon::~CPeopleIcon()
{

}

//=====================================.
//		更新処理関数.
//=====================================.
void CPeopleIcon::UpDate()
{
	//ゲーム内からマップ内に座標変換処理関数.
	GameMapConversion();

	if (m_bSurpriseFlag == false) {
		return;
	}

	//驚き行動処理関数.
	SurpriseAct();
}

//=====================================.
//		驚き行動処理関数.
//=====================================.
void CPeopleIcon::SurpriseAct()
{
	m_fAcc += ACC_SPEED;
	m_vPos.y += m_fAcc - GRAVITY;

	if (m_vPos.y >= START_POS.y) {
		m_vPos.y = START_POS.y;
		m_fAcc = 0.0f;
		m_bSurpriseFlag = false;
	}
}