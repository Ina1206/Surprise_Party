#include "CSpeakUI.h"

CSpeakUI::CSpeakUI()
	: m_pCFontResource				(nullptr)
	, m_stSpeakString				()
	, m_stSelectString				()
	, m_SpeakNum					(0)
	, m_fFontAlpha					(0.0f)
	, m_ChangingFontNum				(0)
	, m_bAppearanceAllFont			(false)
	, m_bFinishAppearancedAllFont	(false)
{
	m_pCFontResource = CResourceManager::GetResourceManagerInstance()->GetFont();
}

CSpeakUI::~CSpeakUI()
{
	m_pCFontResource = nullptr;
}

//======================================.
//		文字描画処理関数.
//======================================.
void CSpeakUI::RenderFont()
{
	//文字の描画.
	if (m_ChangingFontNum < m_pCFontResource->GetStrLength()) {
		m_pCFontResource->SetAlpha(m_fFontAlpha, m_ChangingFontNum);
	}
	m_pCFontResource->String_Render();
}

//======================================.
//		文字透過処理関数.
//======================================.
void CSpeakUI::TransparentFont()
{
	//例外処理.
	if (m_ChangingFontNum >= m_pCFontResource->GetStrLength()) {
		m_bFinishAppearancedAllFont = true;
		return;
	}

	//次の文字に変更.
	if (m_fFontAlpha >= ALPHA_MAX) {
		m_ChangingFontNum++;
		m_fFontAlpha = ALPHA_MIN;
	}

	m_fFontAlpha += ALPHA_SPEED;

	//一気に透過値最大値へ.
	if (m_bAppearanceAllFont == true) {
		m_fFontAlpha = ALPHA_MAX;
	}

	//上限処理.
	if (m_fFontAlpha > ALPHA_MAX) {
		m_fFontAlpha = ALPHA_MAX;

		//ここにSE入れる？.
	}
}

//=======================================.
//		文章変更判定処理関数.
//=======================================.
bool CSpeakUI::DesicionChangeString()
{
	if (m_ChangingFontNum < m_pCFontResource->GetStrLength()) {
		m_bAppearanceAllFont = true;
		return false;
	}

	//文章を次に行かせるための初期化処理.
	m_fFontAlpha = ALPHA_MIN;
	m_bAppearanceAllFont = false;
	m_ChangingFontNum = 0;
	m_bFinishAppearancedAllFont = false;

	return true;
}