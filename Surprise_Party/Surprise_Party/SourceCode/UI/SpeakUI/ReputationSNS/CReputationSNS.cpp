#include "CReputationSNS.h"

/***************************************
*		SNSでの評判クラス.
*******************/
CReputationSNS::CReputationSNS()
	: m_pCSpriteUI			(nullptr)
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
	const int m_FileNum = static_cast<int>(CFileResource::enSpeakFileType::EndingSpeak);

	const CFileString::enStringType MainStringNum = CFileString::enStringType::MainString;
	m_stSpeakString.push_back(m_pCFileResource->GetSpeakString(m_FileNum, EndingNum, MainStringNum));


	m_pCFontResource->Load(m_stSpeakString[0]);

}

//==========================================.
//		初期化処理関数.
//==========================================.
void CReputationSNS::Init()
{
	m_pCSpriteUI = m_pCResourceManager->GetSpriteUI(enSpriteUI::CursorSNS);
	m_vCursorPos = D3DXVECTOR3(50.0f, 250.0f, 0.0f);

	m_pCFontResource->SetStartPos(D3DXVECTOR3(50.0f, 250.0f, 0.0f));
	m_pCFontResource->SetFontScale(90.0f);
	m_pCFontResource->SetWidthMax(1000.0f);
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

	if (m_FlashingCursorCnt > 20) {
		
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
		m_vCursorPos.y += 15.0f;
		return;
	}

	m_vCursorPos = m_pCFontResource->GetFontPos(m_ChangingFontNum - 1);
	m_vCursorPos.x += 90.0f;
	m_vCursorPos.y += 15.0f;
}