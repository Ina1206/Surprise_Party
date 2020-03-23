#include "CFontResource.h"

CFontResource::CFontResource()
	: m_pDevice11	(nullptr)
	, m_pContext11	(nullptr)
	, m_pCFont		()
	, m_StrLength	(0)
	, m_vStartPos	(0.0f, 0.0f, 0.0f)
	, m_hFont		(nullptr)
	, m_hdc			(nullptr)
	, m_fFontScale	(1.0f)
	, m_fWidthMax	(0.0f)
	, m_fAlpha		(1.0f)
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
		TEXT("Data\\Font\\APJapanesefontF.ttf"),
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
		_T("あんずもじ湛")
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
void CFontResource::Load(std::string str)
{
	//文字数を取得（全角文字のみ）.
	m_StrLength = str.length() / 2;
	if (static_cast<int>(m_pCFont.size()) < m_StrLength) {
		//メモリ確保.
		m_pCFont.reserve(m_StrLength);
		for (int size = 0; size <= m_StrLength; size++) {
			m_pCFont.push_back(nullptr);
		}
	}
	else {
		//使われない物は解放.
		for (unsigned int size = m_StrLength; size < m_pCFont.size(); size++) {
			m_pCFont[size].reset();
		}
	}

	//文字のテクスチャ作成.
	for (int size = 0; size < m_StrLength; size++) {
		m_pCFont[size].reset(new CFont());
		//文字列を１文字に分解.
		std::string cda = str.substr(size * 2, 2);
		const char* c = cda.c_str();
		//初期化処理関数.
		m_pCFont[size]->Init(m_pDevice11, m_pContext11, c, m_hFont, m_hdc);
	}


}

//===================================.
//		文字列描画処理関数.
//===================================.
void CFontResource::String_Render()
{
	//幅、高さ.
	int widh, hight;
	widh = hight = 0;
	const float	WIDTH_MAX = WND_W - 150.0f;

	for (int size = 0; size < m_StrLength; size++) {
		CDepth_Stencil* m_pCDepthStencil = CDepth_Stencil::GetDepthStencilInstance();
		//文字の座標.
		const float FONT_WIDTH = widh * (BASIC_WIDTH * m_fFontScale);
		const float	FONT_HEIGHT = hight * (BASIC_WIDTH * m_fFontScale);
		//位置設定処理関数.
		m_pCFont[size]->SetPosition(D3DXVECTOR3(m_vStartPos.x + FONT_WIDTH, m_vStartPos.y + FONT_HEIGHT, m_vStartPos.z));
		//文字の大きさ設定処理関数.
		m_pCFont[size]->SetScale(m_fFontScale);
		//文字の透過値.
		m_pCFont[size]->SetAlpha(m_fAlpha);
		//描画処理関数.
		m_pCDepthStencil->SetDepth(false);
		m_pCFont[size]->Render();
		m_pCDepthStencil->SetDepth(true);

		//改行.
		if (FONT_WIDTH > m_fWidthMax) {
			widh = 0;
			hight++;
		}
		else {
			widh++;
		}
	}
}

//===================================.
//		削除処理関数.
//===================================.
void CFontResource::Destroy()
{
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
		TEXT("Data\\Font\\APJapanesefontF.ttf"),
		FR_PRIVATE,
		&design);
}