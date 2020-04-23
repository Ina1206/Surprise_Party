#include "CTutorialBlackScreen.h"

/******************************************
*		チュートリアル時の黒画面.
**************/
CTutorialBlackScreen::CTutorialBlackScreen()
	: m_vCenterPos			(0.0f, 0.0f, 0.0f)
	, m_vOldCenterPos		(0.0f, 0.0f, 0.0f)
	, m_bDispFlag			(false)
	, m_FadeFlag			(0)
{
	//初期化処理関数.
	Init();
}

CTutorialBlackScreen::~CTutorialBlackScreen()
{
	//解放処理関数.
	Release();
}

//==========================================.
//		更新処理関数.
//==========================================.
void CTutorialBlackScreen::Update()
{
	if (m_vCenterPos != m_vOldCenterPos) {
		//フェード判定処理関数.
		FadeDecision();
	}

	//座標設定処理関数.
	if (!(m_FadeFlag & FADE_OUT_FLAG)) {
		SettingPos();
	}
	m_vOldCenterPos = m_vCenterPos;

	//フェードアウト.
	if (m_FadeFlag & FADE_OUT_FLAG) {
		FadeOut();
		return;
	}
	//フェードイン.
	if (m_FadeFlag & FADE_IN_FLAG) {
		FadeIn();
		return;
	}
}

//===========================================.
//		初期化処理関数.
//===========================================.
void CTutorialBlackScreen::Init()
{
	m_pCSpriteUI.push_back(m_pCResourceManager->GetSpriteUI(enSpriteUI::DescriptionBlack));
	//初期設定処理.
	SettingInit();
	const int SpriteNum = static_cast<int>(m_pCSpriteUI.size()) - 1;
	m_vUIPos[SpriteNum].y -= 90.0f;
	m_vUIScale[SpriteNum] = D3DXVECTOR3(1.2f, 1.2f, 1.2f);

	m_fUIAlpha[SpriteNum] = 0.0f;
}

//============================================.
//		解放処理関数.
//============================================.
void CTutorialBlackScreen::Release()
{

}

//============================================.
//		座標設定処理関数.
//============================================.
void CTutorialBlackScreen::SettingPos()
{

	const int SpriteNum = static_cast<int>(m_pCSpriteUI.size()) - 1;
	if (m_vCenterPos.x < HALF_SCREEN_SIZE) {
		m_vUIPos[SpriteNum].x = 0.0f;
		return;
	}

	m_vUIPos[SpriteNum].x = 1300.0f;
	m_vUIRot[SpriteNum].y = 3.1f;
}

//============================================.
//		フェード判定処理関数.
//============================================.
void CTutorialBlackScreen::FadeDecision()
{
	if (m_vCenterPos.y <= 0) {
		//m_bDispFlag = false;
		m_FadeFlag = FADE_OUT_FLAG;
		return;
	}
	
	m_bDispFlag = true;
	m_FadeFlag = FADE_IN_FLAG | FADE_OUT_FLAG;
}

//============================================.
//		フェードイン処理関数.
//============================================.
void CTutorialBlackScreen::FadeIn()
{
	const int SpriteNum = static_cast<int>(m_pCSpriteUI.size()) - 1;
	
	if (m_fUIAlpha[SpriteNum] > ALPHA_MAX) {
		m_fUIAlpha[SpriteNum] = ALPHA_MAX;
		m_FadeFlag &= ~FADE_IN_FLAG;
		return;
	}

	m_fUIAlpha[SpriteNum] += 0.05f;
}

//=============================================.
//		フェードアウト処理関数.
//=============================================.
void CTutorialBlackScreen::FadeOut()
{
	const int SpriteNum = static_cast<int>(m_pCSpriteUI.size()) - 1;

	if (m_fUIAlpha[SpriteNum] < ALPHA_MIN) {
		m_fUIAlpha[SpriteNum] = ALPHA_MIN;
		m_FadeFlag &= ~FADE_OUT_FLAG;
		return;
	}

	m_fUIAlpha[SpriteNum] -= 0.05f;


}