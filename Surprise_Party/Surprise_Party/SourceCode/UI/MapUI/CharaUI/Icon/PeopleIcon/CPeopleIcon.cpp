#include "CPeopleIcon.h"

/*********************************
*		人のアイコンクラス.
*****/
CPeopleIcon::CPeopleIcon()
	: m_bSurpriseFlag		(false)
	, m_bShoutWoman			(false)
	, m_fAcc				(0.0f)
	, m_pCShockingEffect	(nullptr)
	, m_bJumpFlag			(false)
	, m_bShoutFlag			(false)
	, m_pCSoundPlayManager	(CPlaySoundManager::GetPlaySoundManager())
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

	//驚きジャンプ判定処理関数.
	if (DecisionSurpriseJump() == false) {
		//ジャンプしない場合処理終了.
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
	if (m_bSurpriseFlag == false) {
		return;
	}

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
		m_bJumpFlag = false;
	}
}

//======================================.
//		驚きジャンプ判定処理関数.
//======================================.
bool CPeopleIcon::DecisionSurpriseJump()
{
	if (m_bSurpriseFlag == false) {
		if (m_bJumpFlag == false) {
			m_fAcc = 0.0f;
			m_bShoutFlag = false;
			return false;
		}
	}
	m_bJumpFlag = true;

	if (m_bShoutPossibleFlag == false) {
		return true;
	}

	if (m_bShoutFlag == false) {
		m_bShoutFlag = true;
		if (m_bShoutWoman == true) {
			//男の子の叫び声.
			m_pCSoundPlayManager->SetPlaySE(enSEType::WomanShout);
			m_pCSoundPlayManager->SetSEVolume(enSEType::WomanShout, m_pCSoundPlayManager->VOLUME_MAX);
			return true;
		}

		//女の子の叫び声.
		m_pCSoundPlayManager->SetPlaySE(enSEType::ManShout);
		m_pCSoundPlayManager->SetSEVolume(enSEType::ManShout, m_pCSoundPlayManager->VOLUME_MAX);
	}

	return true;

}