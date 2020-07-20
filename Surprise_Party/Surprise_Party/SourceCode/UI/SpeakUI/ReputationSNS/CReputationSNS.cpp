#include "CReputationSNS.h"

/***************************************
*		SNSでの評判クラス.
*******************/
CReputationSNS::CReputationSNS()
	: m_pCSpriteUI			(0)
	, m_vSpriteUIPos		()
	, m_fSpriteUIAlpha		()
	, m_FlashingCursorCnt	(0)
	, m_stArticleDetail		()
	, m_EndingTypeNum		(0)
	, m_ChangeStageFlag		(0)
{
	//初期化処理関数.
	Init();
}

CReputationSNS::~CReputationSNS()
{
	//解放処理関数.
	Release();
}

//==========================================.
//		更新処理関数.
//==========================================.
void CReputationSNS::Update()
{
	if (GetAsyncKeyState(VK_RETURN) & 0x0001) {
		if (m_bAppearanceAllFont == false) {
			//文字スキップ.
			if (m_bAppearanceAllFont == false) {
				m_pCPlaySoundManager->SetPlaySE(enSEType::FontSkip);
			}
			m_bAppearanceAllFont = true;
			return;
		}

		if (m_bFinishAppearancedAllFont == true) {
			//透過開始.
			m_ChangeStageFlag = START_TRANSPARENT_FLAG;
			//次のステージへ.
			m_pCPlaySoundManager->SetPlaySE(enSEType::NextString);
		}
	}

	if (m_ChangeStageFlag & START_TRANSPARENT_FLAG) {
		//全ての透過処理関数.
		TransparentAll();
		return;
	}

	//文字透過処理.
	TransparentFont();

	//フォントの透過値処理関数.
	FontAlpha();

	//カーソル更新処理関数.
	UpdateCursor();

}

//==========================================.
//		描画処理関数.
//==========================================.
void CReputationSNS::Render()
{
	//デプスステンシル.
	CDepth_Stencil* m_pCDepthStencil = CDepth_Stencil::GetDepthStencilInstance();

	m_pCDepthStencil->SetDepth(false);

	//スプライトUI描画処理関数.
	RenderSpriteUI();

	//文字描画処理関数.
	RenderFont();

	m_pCDepthStencil->SetDepth(true);
	
}

//==========================================.
//		文章決定処理関数.
//==========================================.
void CReputationSNS::DecideString(const int& EndingNum)
{
	const int m_EndingNum = EndingNum;
	CFileResource* m_pCFileResource = CFileResource::GetResourceInstance();
	//読み込むファイル番号.
	const int m_FileNum = static_cast<int>(CFileResource::enSpeakFileType::EndingSpeak);
	//メイン文字列の番号.
	const CFileString::enStringType MainStringNum = CFileString::enStringType::MainString;
	m_stSpeakString.push_back(m_pCFileResource->GetSpeakString(m_FileNum, m_EndingNum, MainStringNum));

	//読み込み処理関数.
	m_pCFontResource->Load(m_stSpeakString[0]);

	//写真決定処理関数.
	DecidePicture(m_EndingNum);

}

//==========================================.
//		初期化処理関数.
//==========================================.
void CReputationSNS::Init()
{
	//カーソル設定処理.
	m_pCSpriteUI.emplace_back(m_pCResourceManager->GetSpriteUI(enSpriteUI::CursorSNS));
	m_vSpriteUIPos.push_back(INIT_FONT_POS);
	m_fSpriteUIAlpha.push_back(ALPHA_MAX);

	
	//フォントの初期化処理.
	m_pCFontResource->SetStartPos(INIT_FONT_POS);
	m_pCFontResource->SetFontScale(FONT_SCALE);
	m_pCFontResource->SetWidthMax(STRING_WIDTH_MAX);
}

//==========================================.
//		解放処理関数.
//==========================================.
void CReputationSNS::Release()
{

}

//==========================================.
//		カーソル更新処理関数.
//==========================================.
void CReputationSNS::UpdateCursor()
{
	//カーソル移動処理関数.
	MoveCursor();

	m_FlashingCursorCnt++;

	if (m_FlashingCursorCnt > FLASING_CNT_MAX) {
		
		m_FlashingCursorCnt = 0;
		if (m_ChangingFontNum >= m_pCFontResource->GetStrLength()) {
			m_pCPlaySoundManager->SetPlaySE(enSEType::Font);
		}

		if (m_fSpriteUIAlpha[CURSOR_NUM] >= ALPHA_MAX) {
			m_fSpriteUIAlpha[CURSOR_NUM] = 0.0f;
			return;
		}
		
		m_fSpriteUIAlpha[CURSOR_NUM] = ALPHA_MAX;
	}
}


//==========================================.
//		カーソル移動処理関数.
//==========================================.
void CReputationSNS::MoveCursor()
{
	if (m_ChangingFontNum < m_pCFontResource->GetStrLength()) {
		m_vSpriteUIPos[CURSOR_NUM] = m_pCFontResource->GetFontPos(m_ChangingFontNum);
		m_vSpriteUIPos[CURSOR_NUM].y += ADJUSTMENT_HEIGHT;
		return;
	}

	//一番端の座標から一文字足したところに置く.
	m_vSpriteUIPos[CURSOR_NUM] = m_pCFontResource->GetFontPos(m_ChangingFontNum - 1);
	m_vSpriteUIPos[CURSOR_NUM].x += FONT_SCALE;

	m_vSpriteUIPos[CURSOR_NUM].y += ADJUSTMENT_HEIGHT;

}

//===========================================.
//		写真決定処理関数.
//===========================================.
void CReputationSNS::DecidePicture(const int& EndingType)
{
	//Sprite番号.
	const int SpriteNum = static_cast<int>(enSpriteUI::PictureSNSRest) + EndingType;

	m_pCSpriteUI.emplace_back(m_pCResourceManager->GetSpriteUI(static_cast<enSpriteUI>(SpriteNum)));
	m_vSpriteUIPos.push_back(PICTURE_POS);
	m_fSpriteUIAlpha.push_back(ALPHA_MAX);
}

//============================================.
//		スプライトUI描画処理関数.
//============================================.
void CReputationSNS::RenderSpriteUI()
{
	for (unsigned int SpriteUI = 0; SpriteUI < m_pCSpriteUI.size(); SpriteUI++) {
		m_pCSpriteUI[SpriteUI]->SetPosition(m_vSpriteUIPos[SpriteUI]);
		m_pCSpriteUI[SpriteUI]->SetAlpha(m_fSpriteUIAlpha[SpriteUI]);
		m_pCSpriteUI[SpriteUI]->Render();
	}
}

//============================================.
//		全ての透過処理関数.
//============================================.
void CReputationSNS::TransparentAll()
{
	//フォントの透過値処理.
	m_fFontAlpha -= FONT_ALPHA_SPEED;
	if (m_fFontAlpha < 0.0f) {
		m_fFontAlpha = 0.0f;
	}

	for (int font = 0; font < m_pCFontResource->GetStrLength(); font++) {
		m_pCFontResource->SetAlpha(m_fFontAlpha, font);
	}

	//スプライトUIの透過処理.
	for (unsigned int SpriteUI = 0; SpriteUI < m_pCSpriteUI.size(); SpriteUI++) {
		m_fSpriteUIAlpha[SpriteUI] -= PICTURE_ALPHA_SPEED;
		m_pCSpriteUI[SpriteUI]->SetAlpha(m_fSpriteUIAlpha[SpriteUI]);

		if (m_fSpriteUIAlpha[SpriteUI] < 0.0f) {
			m_fSpriteUIAlpha[SpriteUI] = 0.0f;
		}
	}

	if (m_fSpriteUIAlpha[PICTURE_NUM] <= 0.0f) {
		//ステージ変更.
		m_ChangeStageFlag = CHANGE_STAGE_FLAG;
	}
}