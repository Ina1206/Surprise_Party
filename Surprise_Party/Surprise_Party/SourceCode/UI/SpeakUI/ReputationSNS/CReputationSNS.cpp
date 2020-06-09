#include "CReputationSNS.h"

/***************************************
*		SNSでの評判クラス.
*******************/
CReputationSNS::CReputationSNS()
	: m_pCSpriteUI			(nullptr)
	, m_pCPictureUI			(nullptr)
	, m_vCursorPos			(0.0f, 0.0f, 0.0f)
	, m_fCursorAlpha		(ALPHA_MAX)
	, m_FlashingCursorCnt	(0)
	, m_stArticleDetail		()
	, m_EndingTypeNum		(0)
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
	//文字透過処理.
	TransparentFont();

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

	//カーソル描画処理関数.
	RenderCursor();

	//写真描画処理関数.
	RenderPicture();

	//文字描画処理関数.
	RenderFont();

	m_pCDepthStencil->SetDepth(true);
	
}

//==========================================.
//		文章決定処理関数.
//==========================================.
void CReputationSNS::DecideString(const int& EndingNum)
{
	CFileResource* m_pCFileResource = CFileResource::GetResourceInstance();
	//読み込むファイル番号.
	const int m_FileNum = static_cast<int>(CFileResource::enSpeakFileType::EndingSpeak);
	//メイン文字列の番号.
	const CFileString::enStringType MainStringNum = CFileString::enStringType::MainString;
	m_stSpeakString.push_back(m_pCFileResource->GetSpeakString(m_FileNum, EndingNum, MainStringNum));

	//読み込み処理関数.
	m_pCFontResource->Load(m_stSpeakString[0]);

	//写真決定処理関数.
	DecidePicture(EndingNum);

}

//==========================================.
//		初期化処理関数.
//==========================================.
void CReputationSNS::Init()
{
	m_pCSpriteUI = m_pCResourceManager->GetSpriteUI(enSpriteUI::CursorSNS);
	m_vCursorPos = INIT_FONT_POS;

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

		if (m_fCursorAlpha >= ALPHA_MAX) {
			m_fCursorAlpha = 0.0f;
			return;
		}
		
		m_fCursorAlpha = ALPHA_MAX;
	}
}

//==========================================.
//		カーソル描画処理関数.
//==========================================.
void CReputationSNS::RenderCursor()
{
	//座標.
	m_pCSpriteUI->SetPosition(m_vCursorPos);
	//透過値.
	m_pCSpriteUI->SetAlpha(m_fCursorAlpha);
	//描画.
	m_pCSpriteUI->Render();
}

//==========================================.
//		カーソル移動処理関数.
//==========================================.
void CReputationSNS::MoveCursor()
{
	if (m_ChangingFontNum < m_pCFontResource->GetStrLength()) {
		m_vCursorPos = m_pCFontResource->GetFontPos(m_ChangingFontNum);
		m_vCursorPos.y += ADJUSTMENT_HEIGHT;
		return;
	}

	//一番端の座標から一文字足したところに置く.
	m_vCursorPos = m_pCFontResource->GetFontPos(m_ChangingFontNum - 1);
	m_vCursorPos.x += FONT_SCALE;

	m_vCursorPos.y += ADJUSTMENT_HEIGHT;

}

//===========================================.
//		写真決定処理関数.
//===========================================.
void CReputationSNS::DecidePicture(const int& EndingType)
{
	//Sprite番号.
	const int SpriteNum = static_cast<int>(enSpriteUI::PictureSNSRest) + EndingType;

	m_pCPictureUI = m_pCResourceManager->GetSpriteUI(static_cast<enSpriteUI>(SpriteNum));
}

//============================================.
//		写真描画処理関数.
//============================================.
void CReputationSNS::RenderPicture()
{
	m_pCPictureUI->SetPosition(D3DXVECTOR3(350.0f, 5.0f, 0.0f));
	m_pCPictureUI->SetAlpha(ALPHA_MAX);
	m_pCPictureUI->Render();
}