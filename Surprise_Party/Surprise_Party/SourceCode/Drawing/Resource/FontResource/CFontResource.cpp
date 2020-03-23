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

	for (int size = 0; size < m_StrLength; size++) {
		CDepth_Stencil* m_pCDepthStencil = CDepth_Stencil::GetDepthStencilInstance();
		//改行.
		if (widh * (BASIC_WIDTH * m_fFontScale) > WND_W - 150.0f) {
			widh = 0;
			hight++;
		}
		else {
			widh++;
		}
		//位置設定処理関数.
		m_pCFont[size]->SetPosition(D3DXVECTOR3(m_vStartPos.x + (widh * (BASIC_WIDTH * m_fFontScale)), m_vStartPos.y + (hight * (BASIC_WIDTH * m_fFontScale)), m_vStartPos.z));
		//文字の大きさ設定処理関数.
		m_pCFont[size]->SetScale(m_fFontScale);
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
	//フォントクラスの解放処理関数.
	//for (int size = m_StrLength - 1; size >= 0; size--) {
	//	SAFE_DELETE(m_pCFont[size]);
	//}
	//要素数の初期化.
	m_pCFont.clear();
	m_pCFont.shrink_to_fit();
}

//===================================.
//		解放処理関数.
//===================================.
void CFontResource::Release()
{
	////削除処理関数.
	//Destroy();

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