#include "CFont.h"
#include <crtdbg.h>


//シェーダーファイル名(ディレクトリも含む).
const char SHADER_NAME[] = "Data\\Shader\\SpriteUI.hlsl";

//コンストラクタ.
CFont::CFont()
	: m_pVertexShader(nullptr)
	, m_pVertexLayout(nullptr)
	, m_pPixelShader(nullptr)
	, m_pConstantBuffer(nullptr)
	, m_pVertexBuffer(nullptr)
	, m_pSampleLinear(nullptr)
	, m_pTexture(nullptr)
	, m_AnimCount(0)
	, m_UV(0.0f, 0.0f)
	, m_vPos()
	, m_Alpha(ALPHA_MAX)	//0:透明,1:完全不透明.
	, m_fScale(SCALE_MAX)
	, m_vRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
{
}

//デストラクタ.
CFont::~CFont()
{
	Release();
}

//初期化.
HRESULT CFont::Init(ID3D11Device* pDevice11,
	ID3D11DeviceContext* pContex11,
	const char* str, HFONT hFont, HDC hdc)
{
	m_pDevice11 = pDevice11;
	m_pContext11 = pContex11;

	//ブレンドステート.
	if (FAILED(InitBlend(m_pDevice11, m_pContext11)))
	{
		return E_FAIL;
	}

	//シェーダ作成.
	if (FAILED(InitShader()))
	{
		return E_FAIL;
	}

	if (FAILED(FontCreate(str, hFont, hdc))) {
		return E_FAIL;
	}
	//板ポリゴン作成.
	if (FAILED(InitModel()))
	{
		return E_FAIL;
	}
	//テクスチャ作成.
	if (FAILED(CreateTexture(&m_pTexture)))
	{
		return E_FAIL;
	}

	return S_OK;
}

//解放.
void CFont::Release()
{

	SAFE_RELEASE(m_pAlphaBlend);
	SAFE_RELEASE(m_pNoAlphaBlend);

	SAFE_RELEASE(m_pSampleLinear);
	SAFE_RELEASE(m_pTexture);
	SAFE_RELEASE(m_pVertexBuffer);
	SAFE_RELEASE(m_pConstantBuffer);
	SAFE_RELEASE(m_pPixelShader);
	SAFE_RELEASE(m_pVertexLayout);
	SAFE_RELEASE(m_pVertexShader);

	m_pContext11 = nullptr;
	m_pDevice11 = nullptr;
}

//==================================================================.
//	HLSLファイルを読み込みシェーダを作成する.
//	HLSL : High Level Shading Language の略.
//==================================================================.
HRESULT CFont::InitShader()
{
	ID3DBlob* pCompiledShader = nullptr;
	ID3DBlob* pErrors = nullptr;
	UINT	  uCompileFlag = 0;
#ifdef _DEBUG
	uCompileFlag =
		D3D10_SHADER_DEBUG | D3D10_SHADER_SKIP_OPTIMIZATION;
#endif	//#ifdef _DEBUG.

	//HLSLからバーテックスシェーダのブロブを作成.
	if (FAILED(
		D3DX11CompileFromFile(
			SHADER_NAME,		//シェーダファイル名(HLSLファイル).
			nullptr,			//マクロ定義の配列へのポインタ(未使用).
			nullptr,			//インクルードファイルを扱うインターフェイスへのポインタ(未使用).
			"VS_Main",			//シェーダエントリーポイント関数の名前.				//""はプロパティの設定項目と一緒.
			"vs_5_0",			//シェーダのモデルを指定する文字列(プロファイル).
			uCompileFlag,		//シェーダコンパイルフラグ.
			0,					//エフェクトコンパイルフラグ(未使用).
			nullptr,			//スレッドポンプインターフェイスへのポインタ(未使用).
			&pCompiledShader,	//ブロブを格納するメモリへのポインタ.
			&pErrors,			//エラーと警告一覧を格納するメモリへのポインタ.
			nullptr)))			//戻り値へのポインタ(未使用).
	{
		_ASSERT_EXPR(false, L"hlsl読み込み失敗");
		return E_FAIL;
	}
	SAFE_RELEASE(pErrors);

	//上記で作成したブロブから「バーテックスシェーダ」を作成.
	if (FAILED(
		m_pDevice11->CreateVertexShader(
			pCompiledShader->GetBufferPointer(),
			pCompiledShader->GetBufferSize(),
			nullptr,
			&m_pVertexShader)))	//(out)バーテックスシェーダ.
	{
		_ASSERT_EXPR(false, L"バーテックスシェーダ作成失敗");
		return E_FAIL;
	}

	//頂点インプットレイアウトを定義.
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{
			"POSITION",						//位置.
			0,
			DXGI_FORMAT_R32G32B32_FLOAT,	//DXGIのフォーマット(32bit float型*3).
			0,
			0,								//データの開始位置.
			D3D11_INPUT_PER_VERTEX_DATA, 0
		},
		{
			"TEXCOORD",						//テクスチャ位置.
			0,
			DXGI_FORMAT_R32G32_FLOAT,		//DXGIのフォーマット(32bit float型*2).
			0,
			12,								//データの開始位置←上のデータが4バイトが3つあるから12この開始位置は間違えてはいけない.
			D3D11_INPUT_PER_VERTEX_DATA, 0
		}

	};
	//頂点インプットレイアウトの配列要素数を算出.
	UINT numElements = sizeof(layout) / sizeof(layout[0]);

	//頂点インプットレイアウトを作成.
	if (FAILED(
		m_pDevice11->CreateInputLayout(
			layout,
			numElements,
			pCompiledShader->GetBufferPointer(),
			pCompiledShader->GetBufferSize(),
			&m_pVertexLayout)))	//(out)頂点インプットレイアウト.
	{
		_ASSERT_EXPR(false, L"頂点インプットレイアウト作成失敗");
		return E_FAIL;
	}
	SAFE_RELEASE(pCompiledShader);

	//HLSLからピクセルシェーダのブロブを作成.
	if (FAILED(
		D3DX11CompileFromFile(
			SHADER_NAME,		//シェーダファイル名(HLSLファイル).
			nullptr,			//マクロ定義の配列へのポインタ(未使用).
			nullptr,			//インクルードファイルを扱うインターフェイスへのポインタ(未使用).
			"PS_Main",			//シェーダエントリーポイント関数の名前.
			"ps_5_0",			//シェーダのモデルを指定する文字列(プロファイル).
			uCompileFlag,		//シェーダコンパイルフラグ.
			0,					//エフェクトコンパイルフラグ(未使用).
			nullptr,			//スレッドポンプインターフェイスへのポインタ(未使用).
			&pCompiledShader,	//ブロブを格納するメモリへのポインタ.
			&pErrors,			//エラーと警告一覧を格納するメモリへのポインタ.
			nullptr)))			//戻り値へのポインタ(未使用).
	{
		_ASSERT_EXPR(false, L"hlsl読み込み失敗");
		return E_FAIL;
	}
	SAFE_RELEASE(pErrors);

	//上記で作成したブロブから「ピクセルシェーダ」を作成.
	if (FAILED(
		m_pDevice11->CreatePixelShader(
			pCompiledShader->GetBufferPointer(),
			pCompiledShader->GetBufferSize(),
			nullptr,
			&m_pPixelShader)))	//(out)ピクセルシェーダ.
	{
		_ASSERT_EXPR(false, L"ピクセルシェーダ作成失敗");
		return E_FAIL;
	}
	SAFE_RELEASE(pCompiledShader);

	//コンスタント(定数)バッファ作成.
	//シェーダに特定の数値を送るバッファ.
	//ここでは変換行列渡し用.
	//シェーダに World, View, Projection 行列を渡す.
	D3D11_BUFFER_DESC cb;
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;		//コンスタントバッファを指定.
	cb.ByteWidth = sizeof(SHADER_CONSTANT_BUFFER);	//コンスタントバッファのサイズ.
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;			//書き込みでアクセス.
	cb.MiscFlags = 0;								//その他のフラグ(未使用).
	cb.StructureByteStride = 0;								//構造体のサイズ().
	cb.Usage = D3D11_USAGE_DYNAMIC;				//使用方法：直接書き込み.

	//コンスタントバッファの作成.
	if (FAILED(
		m_pDevice11->CreateBuffer(
			&cb,
			nullptr,
			&m_pConstantBuffer)))
	{
		_ASSERT_EXPR(false, L"コンスタントバッファ作成失敗");
		return E_FAIL;
	}

	return S_OK;
}

//フォントの作成.
HRESULT CFont::FontCreate(const char* str, HFONT hFont, HDC hdc)
{
	HFONT oldFont = (HFONT)SelectObject(hdc, hFont);

	
	UINT code = 0;
#if _UNICODE
	// unicodeの場合、文字コードは単純にワイド文字のUINT変換です
	code = (UINT)*c;
#else
	// マルチバイト文字の場合、
	// 1バイト文字のコードは1バイト目のUINT変換、
	// 2バイト文字のコードは[先導コード]*256 + [文字コード]です
	if (IsDBCSLeadByte(*str))
		code = (BYTE)str[0] << 8 | (BYTE)str[1];
	else
		code = str[0];
#endif

	GetTextMetrics(hdc, &TM);
	const MAT2 Mat = { {0,1},{0,0},{0,0},{0,1} };
	DWORD size = GetGlyphOutline(hdc, code, GGO_GRAY4_BITMAP, &GM, 0, nullptr, &Mat);
	ptr = new BYTE[size];
	GetGlyphOutline(hdc, code, GGO_GRAY4_BITMAP, &GM, size, ptr, &Mat);

	// デバイスコンテキストとフォントハンドルの開放
	SelectObject(hdc, oldFont);
	DeleteObject(oldFont);
	
	return S_OK;
}


//モデル作成.
HRESULT CFont::InitModel()
{
	float w = 1.0f;						//表示スプライト幅.
	float h = 1.0f;						//表示スプライト高さ.
	float u = 1.0f;	//1コマ当たりの幅.
	float v = 1.0f;	//1コマ当たりの高さ.

	//板ポリ(四角形)の頂点を作成.
	VERTEX vertices[] =
	{
		//頂点座標(x,y,z).				UV座標(u,v).
		D3DXVECTOR3(0.0f,    h, 0.0f),	D3DXVECTOR2(0.0f,    v),//頂点１(左下).
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),	D3DXVECTOR2(0.0f, 0.0f),//頂点２(左上).
		D3DXVECTOR3(w,    h, 0.0f),	D3DXVECTOR2(u,    v),//頂点３(右下).
		D3DXVECTOR3(w, 0.0f, 0.0f),	D3DXVECTOR2(u, 0.0f)	//頂点４(右上).
	};
	//最大要素数を算出する.
	UINT uVerMax = sizeof(vertices) / sizeof(vertices[0]);

	//バッファ構造体.
	D3D11_BUFFER_DESC bd;
	bd.Usage = D3D11_USAGE_DEFAULT;				//使用方法(デフォルト).
	bd.ByteWidth = sizeof(VERTEX) * uVerMax;	//頂点のサイズ.
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;	//頂点バッファとして扱う.
	bd.CPUAccessFlags = 0;						//CPUからはアクセスしない.
	bd.MiscFlags = 0;							//その他のフラグ(未使用).
	bd.StructureByteStride = 0;					//構造体のサイズ(未使用).

	//サブリソースデータ構造体.
	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = vertices;				//板ポリの頂点をセット.

	//頂点バッファの作成.
	if (FAILED(m_pDevice11->CreateBuffer(
		&bd, &InitData, &m_pVertexBuffer)))
	{
		_ASSERT_EXPR(false, L"頂点バッファ作成失敗");
		return E_FAIL;
	}

	//頂点バッファをセット.
	UINT stride = sizeof(VERTEX);	//データ間隔.
	UINT offset = 0;
	m_pContext11->IASetVertexBuffers(
		0, 1,
		&m_pVertexBuffer, &stride, &offset);

	//テクスチャ用のサンプラ構造体.
	D3D11_SAMPLER_DESC	samDesc;
	ZeroMemory(&samDesc, sizeof(samDesc));
	samDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;	//リニアフィルタ(線形補間).
							//POINT:高速だが粗い.
	samDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;		//ラッピングモード(WRAP:繰り返し).
	samDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	//MIRROR: 反転繰り返し.
	//CLAMP : 端の模様を引き伸ばす.
	//BORDER: 別途境界色を決める.
	//サンプラ作成.
	if (FAILED(m_pDevice11->CreateSamplerState(
		&samDesc, &m_pSampleLinear)))					//(out)サンプラ.
	{
		_ASSERT_EXPR(false, L"サンプラ作成失敗");
		return E_FAIL;
	}


	return S_OK;
}

//テクスチャ作成.
HRESULT CFont::CreateTexture(ID3D11ShaderResourceView** pTexture)
{
	//テクスチャ作成.
	D3D11_TEXTURE2D_DESC desc;
	memset(&desc, 0, sizeof(desc));
	desc.Width = GM.gmCellIncX;
	desc.Height = TM.tmHeight;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.SampleDesc.Count = 1;
	desc.Usage = D3D11_USAGE_DYNAMIC;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	ID3D11Texture2D* tex2D;
	if (FAILED(m_pDevice11->CreateTexture2D(&desc, 0, &tex2D)))
	{
		_ASSERT_EXPR(nullptr, L"テクスチャ作成失敗");
		return E_FAIL;
	}

	D3D11_MAPPED_SUBRESOURCE hMappedResource;
	if (FAILED(m_pContext11->Map( tex2D, 0,	D3D11_MAP_WRITE_DISCARD,
		0, &hMappedResource))) {
		_ASSERT_EXPR(nullptr, L"テクスチャマップ失敗");
		return E_FAIL;
	}

	BYTE* pBits = (BYTE*)hMappedResource.pData;

	int iOfs_x = GM.gmptGlyphOrigin.x;
	int iOfs_y = TM.tmAscent - GM.gmptGlyphOrigin.y;
	int iBmp_w = GM.gmBlackBoxX + (4 - (GM.gmBlackBoxX % 4)) % 4;
	int iBmp_h = GM.gmBlackBoxY;
	int Level = 17;
	int x, y;
	DWORD Alpha, Color;
	memset(pBits, 0, hMappedResource.RowPitch * TM.tmHeight);
	for (y = iOfs_y; y < iOfs_y + iBmp_h; y++) {
		for (x = iOfs_x; x < iOfs_x + iBmp_w; x++) {
			Alpha = (255 * ptr[x - iOfs_x + iBmp_w * (y - iOfs_y)]) / (Level - 1);
			Color = 0x00ffffff | (Alpha << 24);
			
			memcpy((BYTE*)pBits + hMappedResource.RowPitch * y + 4 * x, &Color, sizeof(DWORD));
		}
	}
	m_pContext11->Unmap(tex2D, 0);

	D3D11_TEXTURE2D_DESC texDesc;
	tex2D->GetDesc(&texDesc);

	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	ZeroMemory(&srvDesc, sizeof(srvDesc));
	srvDesc.Format = texDesc.Format;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MostDetailedMip = 0;
	srvDesc.Texture2D.MipLevels = texDesc.MipLevels;
	m_pDevice11->CreateShaderResourceView(tex2D, &srvDesc, pTexture);

	//解放処理.
	SAFE_RELEASE(tex2D);
	SAFE_DELETE_ARRAY(ptr);

	return S_OK;
}


//レンダリング用.
void CFont::Render()
{
	//ワールド行列.
	D3DXMATRIX mWorld, mScale, mRot;
	D3DXMATRIX mYaw, mPitch, mRoll;

	//Y軸回転行列作成.
	D3DXMatrixRotationY(&mYaw, m_vRot.y);
	//X軸回転行列作成.
	D3DXMatrixRotationX(&mPitch, m_vRot.x);
	//Z軸回転行列作成.
	D3DXMatrixRotationZ(&mRoll, m_vRot.z);

	//平行移動.
	D3DXMatrixTranslation(&mWorld, m_vPos.x, m_vPos.y, m_vPos.z);

	//拡大縮小行列作成.
	D3DXMatrixScaling(
		&mScale,						//(out)計算結果.
		m_fScale, m_fScale, m_fScale);	//x,y,zそれぞれの拡縮値.

	//回転行列を作成.
	mRot = mYaw * mPitch * mRoll;

	mWorld = mScale * mRot * mWorld;

	//使用するシェーダの登録.
	m_pContext11->VSSetShader(m_pVertexShader, nullptr, 0);
	m_pContext11->PSSetShader(m_pPixelShader, nullptr, 0);

	//シェーダのコンスタントバッファに各種データを渡す.
	D3D11_MAPPED_SUBRESOURCE	pData;
	SHADER_CONSTANT_BUFFER		cb;		//コンスタントバッファ.
	//バッファ内のデータの書き換え開始時にmap.
	if (SUCCEEDED(
		m_pContext11->Map(m_pConstantBuffer,
			0, D3D11_MAP_WRITE_DISCARD, 0, &pData)))
	{
		//ワールド行列を渡す.
		D3DXMATRIX m = mWorld;
		D3DXMatrixTranspose(&m, &m);			//行列を転置する.
		cb.mW = m;

		//ビューポート幅,高さを渡す.
		cb.fViewPortWidth = WND_W;
		cb.fViewPortHeight = WND_H;

		//アルファ値を渡す.
		//フェードインフェードアウトで使うことができる.
		//ブレイクポイントの時変数の数値を変更することができる.
		D3DXVECTOR4 vColor = D3DXVECTOR4(1.0f, 1.0f, 1.0f, m_Alpha);
		cb.vColor = vColor;


		//UV座標.
		//1コマ当たりの割合にパターン番号をかけて位置を設定する.
		//アンカーという基準値を設定すると回転とかも真ん中を中心に動ける.
		cb.vUV.x = 0.0f;
		cb.vUV.y = 0.0f;

		memcpy_s(pData.pData, pData.RowPitch, (void*)(&cb), sizeof(cb));

		m_pContext11->Unmap(m_pConstantBuffer, 0);
	}

	//このコンスタントバッファをどのシェーダで使うか？.
	//registarのb2の2と連動している.
	m_pContext11->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);
	m_pContext11->PSSetConstantBuffers(0, 1, &m_pConstantBuffer);

	//頂点バッファをセット.
	UINT stride = sizeof(VERTEX);	//データの間隔.
	UINT offset = 0;
	m_pContext11->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);

	//頂点インプットレイアウトをセット.
	m_pContext11->IASetInputLayout(m_pVertexLayout);
	//プリミティブ・トポロジーをセット.
	m_pContext11->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//テクスチャーをシェーダに渡す.
	m_pContext11->PSSetSamplers(0, 1, &m_pSampleLinear);
	m_pContext11->PSSetShaderResources(0, 1, &m_pTexture);

	//アルファブレンド有効にする.
	SetBlend(true);

	//プリミティブをレンダリング.
	m_pContext11->Draw(4, 0);	//板ポリ(頂点４つ分).

	//アルファブレンド無効にする.
	SetBlend(false);
}

