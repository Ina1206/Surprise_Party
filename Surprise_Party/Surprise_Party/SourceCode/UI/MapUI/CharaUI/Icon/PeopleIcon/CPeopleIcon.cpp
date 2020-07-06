#include "CPeopleIcon.h"

CPeopleIcon::CPeopleIcon()
	: m_bSurpriseFlag		(false)
	, m_fAcc				(0.0f)
	, m_pCShockingEffect	(nullptr)
{
	m_pCShockingEffect.reset(new CShockingEffect());
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

	//衝撃エフェクト更新処理関数.
	m_pCShockingEffect->SetCenterPos(m_vPos);
	m_pCShockingEffect->Update();
}

//=====================================.
//		エフェクト描画処理関数.
//=====================================.
void CPeopleIcon::RenderEffect()
{
	m_pCShockingEffect->Render();
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