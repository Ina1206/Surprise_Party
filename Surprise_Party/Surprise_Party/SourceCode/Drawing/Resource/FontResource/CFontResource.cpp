#include "CFontResource.h"

CFontResource::CFontResource()
	: m_pDevice11	(nullptr)
	, m_pContext11	(nullptr)
	, m_pCFont		()
	, m_StrLength	(0)
	, m_vStartPos	(0.0f, 0.0f, 0.0f)
	, m_vPos		()
	, m_hFont		(nullptr)
	, m_hdc			(nullptr)
	, m_fFontScale	(0.0f)
	, m_fAlpha		()
	, m_fWidthMax	(0.0f)
{

}

CFontResource::~CFontResource()
{
	//解放処理関数.
	Release();
}

//===================================.
//		初期化処理関数.
//===================================.
void CFontResource::Init(ID3D11Device* pDevice11, ID3D11DeviceContext* pContext11)
{
	m_pDevice11 = pDevice11;
	m_pContext11 = pContext11;

	//ttfファイル読み込み.
	DESIGNVECTOR design;
	AddFontResourceEx(
		TEXT("Data\\Font\\SNsanafonmaru.ttf"),
		FR_PRIVATE,
		&design);

	//フォント作成.
	LOGFONT lf = {
		FONT_SIZE,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		SHIFTJIS_CHARSET,
		OUT_TT_ONLY_PRECIS,
		CLIP_DEFAULT_PRECIS,
		PROOF_QUALITY,
		FIXED_PITCH | FF_MODERN,
		_T("さなフォン丸")
	};

	if (!(m_hFont = CreateFontIndirect(&lf))) {
		_ASSERT_EXPR(m_hFont != nullptr, L"文字作成失敗");
	}
	//デバイスコンテキスト作成.
	m_hdc = GetDC(nullptr);
}

//===================================.
//		読み込み処理関数.
//===================================.
void CFontResource::Load(std::string str, bool InputPictureFlag)
{

	//文字数を取得（全角文字のみ）.
	m_StrLength = str.length() / 2;
	if (static_cast<int>(m_pCFont.size()) < m_StrLength) {
		//メモリ確保.
		m_pCFont.reserve(m_StrLength);
		//前回のフォント最大値.
		const int m_StartPos = m_pCFont.size();
		for (int size = m_StartPos; size <= m_StrLength; size++) {
			m_pCFont.push_back(nullptr);
		}
	}
	else {
		//使われない物は解放.
		for (unsigned int size = m_StrLength; size < m_pCFont.size(); size++) {
			m_pCFont[size].reset();
		}
	}
	//透過値サイズ設定.
	m_fAlpha.resize(m_pCFont.size());
	//座標サイズ指定.
	m_vPos.resize(m_pCFont.size());
	m_InputPictureNum.clear();
	m_PictureTypeNum.clear();

	//幅、高さ.
	int widh, hight;
	widh = hight = 0;

	//文字のテクスチャ作成.
	bool bLineFeed = false;
	for (int size = 0; size < m_StrLength; size++) {
		//文字列を１文字に分解.
		std::string cda = str.substr(size * 2, 2);

		m_pCFont[size].reset(new CFont());

		//アイコンを入れる場合は０～９を元に入れる.
		if (InputPictureFlag == true) {
			if (cda >= "０" && cda <= "９") {
				m_InputPictureNum.push_back(size);
				m_PictureTypeNum.push_back(cda);
				cda = "　";
			}
		}

		bLineFeed = false;
		if (cda == "￥") {
			cda = "　";
			bLineFeed = true;
		}

		const char* c = cda.c_str();
		//初期化処理関数.
		m_pCFont[size]->Init(m_pDevice11, m_pContext11, c, m_hFont, m_hdc);
		m_fAlpha[size] = 0.0f;


		//文字の座標.
		const float FONT_WIDTH = widh * (BASIC_WIDTH * m_fFontScale);
		const float	FONT_HEIGHT = hight * (BASIC_WIDTH * m_fFontScale);
		m_vPos[size] = D3DXVECTOR3(m_vStartPos.x + FONT_WIDTH, m_vStartPos.y + FONT_HEIGHT, m_vStartPos.z);
		//改行.
		if (FONT_WIDTH > m_fWidthMax || bLineFeed == true) {
			widh = 0;
			hight++;
		}
		else {
			widh++;
		}

	}


}

//===================================.
//		文字列描画処理関数.
//===================================.
void CFontResource::String_Render()
{
	CDepth_Stencil* m_pCDepthStencil = CDepth_Stencil::GetDepthStencilInstance();

	for (int size = 0; size < m_StrLength; size++) {
		//位置設定処理関数.
		m_pCFont[size]->SetPosition(m_vPos[size]);
		//文字の大きさ設定処理関数.
		m_pCFont[size]->SetScale(m_fFontScale);
		//文字の透過値.
		m_pCFont[size]->SetAlpha(m_fAlpha[size]);
		//描画処理関数.
		m_pCDepthStencil->SetDepth(false);
		m_pCFont[size]->Render();
		m_pCDepthStencil->SetDepth(true);
	}
}

//===================================.
//		削除処理関数.
//===================================.
void CFontResource::Destroy()
{
	//フォントが作成されてなければ処理終了.
	if (m_pCFont.size() <= 0) {
		return;
	}
	//要素数の初期化.
	m_pCFont.clear();
	m_pCFont.shrink_to_fit();
}

//===================================.
//		解放処理関数.
//===================================.
void CFontResource::Release()
{

	//フォント解放.
	DeleteObject(m_hFont);
	//デバイスコンテキスト解放.
	ReleaseDC(NULL, m_hdc);

	//フォント読み込み解放.
	DESIGNVECTOR design;
	RemoveFontResourceEx(
		TEXT("Data\\Font\\SNsanafonmaru.ttf"),
		FR_PRIVATE,
		&design);
}

