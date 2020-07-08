#include "CSpeakUI.h"

CSpeakUI::CSpeakUI()
	: m_pCFileResource				(CFileResource::GetResourceInstance())
	, m_pCFontResource				(nullptr)
	, m_stSpeakString				()
	, m_stSelectString				()
	, m_SpeakNum					(0)
	, m_fFontAlpha					(0.0f)
	, m_ChangingFontNum				(0)
	, m_bAppearanceAllFont			(false)
	, m_bFinishAppearancedAllFont	(false)
	, m_AutoFlag					(0)
	, m_AutoWaitCnt					(0)
{
	m_pCFontResource = CResourceManager::GetResourceManagerInstance()->GetFont();
	//前のデータを削除.
	m_pCFontResource->Destroy();
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

	const int	FileNum			= static_cast<int>(CFileResource::enStatusCharaType::GhostSpeak);
	const int	StatusNum		= static_cast<int>(enStatusType::FontSpeed);
	const int	FontDispSpeed	= static_cast<int>(m_pCFileResource->GetStatusNum(FileNum, StatusNum, 0));
	const float AlphaSpeed		= ALPHA_MAX / FontDispSpeed;
	m_fFontAlpha += AlphaSpeed;

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

//=======================================.
//		自動再生処理関数.
//=======================================.
bool CSpeakUI::AutomaticReproducing()
{
	//自動再生の変更処理.
	if (GetAsyncKeyState('Z') & 0x0001) {
		if (m_AutoFlag == 0) {
			m_AutoFlag = AUTO_FLAG;
			return false;
		}

		m_AutoFlag = 0;
		return false;
	}

	//一時停止中はオートフラグの処理をしない.
	if (m_AutoFlag & AUTO_SUSPEND_FLAG) {
		return false;
	}

	if (m_AutoFlag == 0) {
		return false;
	}

	//文字が全てで終わるまで再生しない処理.
	if (m_ChangingFontNum < m_pCFontResource->GetStrLength()) {
		return false;
	}
	
	//全て出ても少し待ってから再生する処理.
	const int FileNum		= static_cast<int>(CFileResource::enStatusCharaType::GhostSpeak);			//ファイル番号.
	const int StatusNum		= static_cast<int>(enStatusType::AutoWaitSpeed);							//ステータス番号.
	const int AutoWaitMax	= static_cast<int>(m_pCFileResource->GetStatusNum(FileNum, StatusNum, 0));	//自動再生待機最大値.
	m_AutoWaitCnt++;
	if (m_AutoWaitCnt < AutoWaitMax) {
		return false;
	}
	m_AutoWaitCnt = 0;

	if (DesicionChangeString() == false) {
		return false;
	}

	return true;
}