#include "CSpeakTutorial.h"

/******************************************
*		チュートリアル会話.
***************/
CSpeakTutorial::CSpeakTutorial()
	: m_pCSpriteUI				()
	, m_pCDescriptionIcon		()
	, m_vIconPos				()
	, m_vPos					()
	, m_vPattern				()
	, m_TutorialFlag			(0)
	, m_DefinitiveTutorialFlag	(0)
	, m_DescriptionFlag			(0)
	, m_bAdvanceCommentFlag		(true)
	, m_SelectMoveCount			(0)
	, m_enStartLatestFlag		(0)
	, m_bDescriptionEnd			(false)
	, m_pCNextSpeakCursor		(nullptr)
{
	//初期化処理関数.
	Init();
}

CSpeakTutorial::~CSpeakTutorial()
{
	//解放処理関数.
	Release();
}

//======================================.
//		更新処理関数.
//======================================.
void CSpeakTutorial::Update()
{
	if (m_enStartLatestFlag & SeePeople) {
		m_enStartLatestFlag = 0;
	}

	if (m_bDescriptionEnd == true) {
		return;
	}

	if (!(m_AutoFlag & AUTO_FLAG)) {
		if (GetAsyncKeyState(VK_RETURN) & 0x0001) {

			if (m_bFinishAppearancedAllFont == false) {
				m_bAppearanceAllFont = true;
			}

			//説明終了処理.
			if (m_enStartLatestFlag & DescriptionEnd &&
				m_bFinishAppearancedAllFont == true) {
				m_bDescriptionEnd = true;
			}

			if (m_bAdvanceCommentFlag == true) {

				//コメント一回進める処理.
				AdvanceOnceComment();
			}
		}
	}

	//自動再生処理関数.
	if (AutomaticReproducing() == true) {
		//説明終了処理.
		if (m_enStartLatestFlag & DescriptionEnd) {
			m_bDescriptionEnd = true;
		}
		//コメントを一回進める処理関数.
		AdvanceOnceComment();
	}
	//if (m_bAdvanceCommentFlag == false) {
	//	m_AutoFlag |= AUTO_SUSPEND_FLAG;
	//}
	//else {
	//	m_AutoFlag &= ~AUTO_SUSPEND_FLAG;
	//}

	if (m_ChangingFontNum >= m_pCFontResource->GetStrLength()) {
		m_DefinitiveTutorialFlag = m_TutorialFlag;
	}

	//文字透過処理関数.
	TransparentFont();

	//次の文章カーソル更新処理.
	bool bDispFlag = false;
	if (m_bFinishAppearancedAllFont == true && m_bAdvanceCommentFlag == true) {
		bDispFlag = true;
	}
	m_pCNextSpeakCursor->SetDispFlag(bDispFlag);
	if (m_ChangingFontNum > 0) {
		D3DXVECTOR3 vFontPos = m_pCFontResource->GetFontPos(m_ChangingFontNum - 1);
		vFontPos.x += 40.0f;
		m_pCNextSpeakCursor->SetStartPos(vFontPos);
	}
	m_pCNextSpeakCursor->Update();
}

//=======================================.
//		描画処理関数.
//=======================================.
void CSpeakTutorial::Render()
{
	//吹き出しの描画.
	for (unsigned int speak = 0; speak < m_pCSpriteUI.size(); speak++) {
		//吹き出し種類設定.
		if (m_pCSpriteUI[speak] == m_pCResourceManager->GetSpriteUI(enSpriteUI::Balloon)) {
			m_pCSpriteUI[speak]->SetPattern(D3DXVECTOR2(1.0f, 1.0f));
		}
		m_pCSpriteUI[speak]->SetScale(1.3f);
		m_pCSpriteUI[speak]->SetPosition(m_vPos[speak]);
		m_pCDepthStencil->SetDepth(false);
		m_pCSpriteUI[speak]->Render();
		m_pCDepthStencil->SetDepth(true);
	}

	//テキストの描画.
	RenderFont();

	//説明用アイコン描画処理関数.
	RenderDescriptionIcon();

	//次の文章カーソル描画処理関数.
	m_pCNextSpeakCursor->Render();

	//自動再生時のUI描画処理関数.
	if (m_AutoFlag & AUTO_FLAG && !(m_AutoFlag & AUTO_SUSPEND_FLAG)) {
		m_pCAutoUI->Render();
	}
}

//========================================.
//		一回コメントを進める処理関数.
//========================================.
void CSpeakTutorial::AdvanceOnceComment()
{
	if (DesicionChangeString() == false) {
		return;
	}

	m_SpeakNum++;
	if (static_cast<unsigned int>(m_SpeakNum) >= m_stSpeakString.size()) {
		m_SpeakNum = m_stSpeakString.size() - 1;

	}
	m_pCFontResource->Load(m_stSpeakString[m_SpeakNum], true);
	//チュートリアル探索処理関数.
	FindTutorial();
}

//========================================.
//		選択移動カウント追加処理関数.
//========================================.
void CSpeakTutorial::AddSelectMoveCount()
{
	//例外処理(選択時以外例外).
	const unsigned int SELECT_FLAG = SELECT_GHOST_FLAG | SELECT_GIMMICK_FLAG;
	//if (!(m_TutorialFlag & SELECT_FLAG)) {
	if (!(m_DefinitiveTutorialFlag & SELECT_FLAG)) {
		return;
	}

	m_SelectMoveCount++;

	if (m_SelectMoveCount >= 2) {
		//一回コメントを進める処理関数.
		AdvanceOnceComment();

		m_SelectMoveCount = 0;
	}
}

//========================================.
//		初期化処理関数.
//========================================.
void CSpeakTutorial::Init()
{
	m_pCSpriteUI.push_back(m_pCResourceManager->GetSpriteUI(enSpriteUI::BigGhostIcon));
	m_pCSpriteUI.push_back(m_pCResourceManager->GetSpriteUI(enSpriteUI::Balloon));
	
	for (unsigned int speak = 0; speak < m_pCSpriteUI.size(); speak++) {
		m_vPos.push_back(D3DXVECTOR3(10.0f + (10.0f * speak), 400.0f - (250.0f * speak), 0.0f));
	}
	
	//読み込むファイル番号.
	const int LoadFileNum = static_cast<int>(CFileResource::enSpeakFileType::SpeakTutorialBigGhost);
	for (int file = 0; file < m_pCFileResource->GetSringMax(LoadFileNum); file++) {
		m_stSpeakString.push_back(m_pCFileResource->GetSpeakString(LoadFileNum, file, CFileString::enStringType::MainString));
		m_stSelectString.push_back(m_pCFileResource->GetSpeakString(LoadFileNum, file, CFileString::enStringType::SelectString));
	}
	m_vPos.push_back(D3DXVECTOR3(60.0f, 210.0f, 0.0f));

	m_pCFontResource->SetFontScale(40.0f);
	m_pCFontResource->SetWidthMax(200.0f);
	const D3DXVECTOR3 vFontPos = m_vPos[2] + D3DXVECTOR3(0.0f, 10.0f, 0.0f);
	m_pCFontResource->SetStartPos(vFontPos);
	m_pCFontResource->Load(m_stSpeakString[m_SpeakNum], true);

	//次の文章カーソルクラスのインスタンス化.
	m_pCNextSpeakCursor.reset(new CNextSpeakCursor());

	//チュートリアルフラグ設定.
	m_pCAutoUI->SetTutorialFlag(true);
}

//========================================.
//		解放処理関数.
//========================================.
void CSpeakTutorial::Release()
{

}

//========================================.
//		チュートリアル見つける処理関数.
//========================================.
void CSpeakTutorial::FindTutorial()
{
	m_DescriptionFlag = 0;
	if (m_stSelectString[m_SpeakNum] == "0") {
		m_bAdvanceCommentFlag = true;
		m_AutoFlag &= ~AUTO_SUSPEND_FLAG;
		return;
	}

	m_AutoFlag |= AUTO_SUSPEND_FLAG;
	if (m_stSelectString[m_SpeakNum] == "GhostSelect") {
		m_TutorialFlag = SELECT_GHOST_FLAG;
		//コメント進めるの停止.
		m_bAdvanceCommentFlag = false;
		return;
	}

	if (m_stSelectString[m_SpeakNum] == "GhostDecide") {
		m_TutorialFlag = DECIDE_GHOST_FLAG;
		return;
	}

	if (m_stSelectString[m_SpeakNum] == "ActDecide") {
		m_TutorialFlag = DECIDE_ACT_FLAG;
		//コメント進めるの停止.
		m_bAdvanceCommentFlag = false;
		return;
	}

	if (m_stSelectString[m_SpeakNum] == "GimmickSelect") {
		m_TutorialFlag = SELECT_GIMMICK_FLAG;
		m_bAdvanceCommentFlag = false;
		return;
	}

	if (m_stSelectString[m_SpeakNum] == "GimmickDecide") {
		m_TutorialFlag = DECIDE_GIMMICK_FLAG;
		return;
	}

	m_AutoFlag &= ~AUTO_SUSPEND_FLAG;
	//説明内容検索処理関数.
	FindDescription();

	//説明用アイコン設定処理関数.
	SettingDescriptionIcon();

}

//========================================.
//		説明内容見つける処理関数.
//========================================.
void CSpeakTutorial::FindDescription()
{

	if (m_stSelectString[m_SpeakNum] == "MapDescription") {
		m_DescriptionFlag = MAP_DESCRIPTION_FLAG;
		return;
	}

	if (m_stSelectString[m_SpeakNum] == "GhostDescription") {
		m_DescriptionFlag = GHOST_DESCRIPTION_FLAG;
		return;
	}

	if (m_stSelectString[m_SpeakNum] == "GimmickDescription") {
		m_DescriptionFlag = GIMMICK_DESCRIPTION_FLAG;
		return;
	}

	if (m_stSelectString[m_SpeakNum] == "PeopleDescription") {
		m_DescriptionFlag = PEOPLE_DESCRIPTION_FLAG;
		return;
	}

	if (m_stSelectString[m_SpeakNum] == "SurpriseGageDescription") {
		m_DescriptionFlag = GAGE_DESCRIPTION_FLAG;
		return;
	}

	if (m_stSelectString[m_SpeakNum] == "CloseTimeDescription") {
		m_DescriptionFlag = CLOSE_TIME_DESCRIPTION_FLAG;
		return;
	}

	if (m_stSelectString[m_SpeakNum] == "CustomerEnterSE") {
		m_enStartLatestFlag = CustomerEnterSE;
		return;
	}

	if (m_stSelectString[m_SpeakNum] == "SeePeople") {
		m_enStartLatestFlag = SeePeople;
		return;
	}

	if (m_stSelectString[m_SpeakNum] == "DescriptionEnd") {
		m_enStartLatestFlag = DescriptionEnd;
	}
}

//=========================================.
//		説明用アイコン設定処理関数.
//=========================================.
void CSpeakTutorial::SettingDescriptionIcon()
{
	//削除.
	if (m_pCDescriptionIcon.size() > 0) {
		m_pCDescriptionIcon.clear();
	}

	//挿入アイコンのサイズ.
	const unsigned int ICON_MAX = m_pCFontResource->GetInputPictureSize();

	//例外処理.
	if (ICON_MAX <= 0) {
		return;
	}

	//フォント座標.
	for (unsigned int Icon = 0; Icon < ICON_MAX; Icon++) {
		const int			FontNum = m_pCFontResource->GetInputPictureNum(Icon);
		const D3DXVECTOR3	vPosAdjustment = D3DXVECTOR3(-10.0f, -10.0f, 0.0f);
		const D3DXVECTOR3	vFontPos = m_pCFontResource->GetFontPos(FontNum) + vPosAdjustment;
		
		if (Icon < m_vIconPos.size()) {
			m_vIconPos[Icon] = vFontPos;
			continue;
		}
		m_vIconPos.push_back(vFontPos);
	}

	//お化けのアイコン設定.
	if (m_DescriptionFlag & GHOST_DESCRIPTION_FLAG) {
		GhostIconSetting(ICON_MAX);

		return;
	}

	//ギミックアイコン設定.
	if (m_DescriptionFlag & GIMMICK_DESCRIPTION_FLAG) {
		GimmickIconSetting(ICON_MAX);
		return;
	}

	//人のアイコン.
	if (m_DescriptionFlag & PEOPLE_DESCRIPTION_FLAG) {
		PeopleIconSetting(ICON_MAX);
		return;
	}
}

//===========================================.
//		説明用アイコン描画処理関数.
//===========================================.
void CSpeakTutorial::RenderDescriptionIcon()
{
	if (m_pCDescriptionIcon.size() <= 0) {
		return;
	}
	
	for (unsigned int IconNum = 0; IconNum < m_pCDescriptionIcon.size(); IconNum++) {
		if (m_DescriptionFlag & GHOST_DESCRIPTION_FLAG) {
			m_pCDescriptionIcon[IconNum]->SetPattern(m_vPattern[IconNum]);
		}
		m_pCDescriptionIcon[IconNum]->SetAlpha(ALPHA_MAX);
		m_pCDescriptionIcon[IconNum]->SetPosition(m_vIconPos[IconNum]);
		m_pCDescriptionIcon[IconNum]->SetScale(DESCRIPTION_ICON_SCALE);
		m_pCDepthStencil->SetDepth(false);
		m_pCDescriptionIcon[IconNum]->Render();
		m_pCDepthStencil->SetDepth(true);
	}
}

//============================================.
//		お化けアイコン設定処理関数.
//============================================.
void CSpeakTutorial::GhostIconSetting(const int& IconMax)
{
	if (m_vPattern.size() > 0) {
		m_vPattern.clear();
	}

	for (int Icon = 0; Icon < IconMax; Icon++) {
		
		m_pCDescriptionIcon.push_back(m_pCResourceManager->GetSpriteUI(enSpriteUI::Ghost_Icon));

		const std::string InputPictureType = m_pCFontResource->GetPictureTypeNum(Icon);
		if (InputPictureType == "０") {
			m_vPattern.push_back(D3DXVECTOR2(0.0f, 0.0f));
			continue;
		}
		if (InputPictureType == "１") {
			m_vPattern.push_back(D3DXVECTOR2(0.0f, 2.0f));
		}
	}
}

//============================================.
//		ギミックアイコン設定処理関数.
//============================================.
void CSpeakTutorial::GimmickIconSetting(const int& IconMax)
{
	for (int Icon = 0; Icon < IconMax; Icon++) {
		const std::string InputPictureType = m_pCFontResource->GetPictureTypeNum(Icon);
		if (InputPictureType == "０") {
			m_pCDescriptionIcon.push_back(m_pCResourceManager->GetSpriteUI(enSpriteUI::DispGimmick_Iccon));
			continue;
		}
		if (InputPictureType == "１") {
			m_pCDescriptionIcon.push_back(m_pCResourceManager->GetSpriteUI(enSpriteUI::Switch_Icon));
		}
	}
}

//============================================.
//		人々のアイコン設定処理関数.
//============================================.
void CSpeakTutorial::PeopleIconSetting(const int& IconMax)
{
	for (int Icon = 0; Icon < IconMax; Icon++) {
		const std::string InputPictureType = m_pCFontResource->GetPictureTypeNum(Icon);
		if (InputPictureType == "０") {
			m_pCDescriptionIcon.push_back(m_pCResourceManager->GetSpriteUI(enSpriteUI::Girl_Icon));
			continue;
		}
		if (InputPictureType == "１") {
			m_pCDescriptionIcon.push_back(m_pCResourceManager->GetSpriteUI(enSpriteUI::Boy_Icon));
		}
	}

}