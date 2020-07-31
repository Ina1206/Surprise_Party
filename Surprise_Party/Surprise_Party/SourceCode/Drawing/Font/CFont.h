#ifndef CFONT_H
#define CFONT_H

//警告についてのコード分析を無効にする.4005:再定義.
#pragma warning( disable:4005 )

#include "..\CCommon.h"
#include <tchar.h>
#define ALINGN16 _declspec(align(16))

/**************************************************
*			フォントクラス.
******************/
class CFont
	: public CCommon
{
public:
	//==================定数=======================//.
	const float		ALPHA_MAX = 1.0f;		//透過値最大数.
	const float		SCALE_MAX = 1.0f;		//大きさ最大値.

	CFont();
	~CFont();
	//初期化.
	HRESULT Init(ID3D11Device* pDevice11,
		ID3D11DeviceContext* pContex11,
		const char* str, HFONT hFont, HDC hdc);


	//レンダリング用.
	void Render();

	//位置情報を設定.
	void SetPosition(float x, float y, float z) {
		m_vPos.x = x;
		m_vPos.y = y;
		m_vPos.z = z;
	}

	//位置情報を設定.
	void SetPosition(const D3DXVECTOR3& vPos) {
		m_vPos = vPos;
	}

	//大きさを設定.
	void SetScale(float fScale) {
		m_fScale = fScale;
	}
	float GetScale() {
		return m_fScale;
	}

	//角度.
	void SetRotation(D3DXVECTOR3 Rot) {
		m_vRot = Rot;
	}

	//透過値を設定.
	void SetAlpha(float Alpha) {
		m_Alpha = Alpha;
	}


private:
	//解放.
	void Release();

	//シェーダ作成.
	HRESULT InitShader();

	//フォントの作成.
	HRESULT FontCreate(const char* str, HFONT hFont, HDC hdc);

	//モデル作成.
	HRESULT InitModel();
	//テクスチャ作成.
	HRESULT CreateTexture(ID3D11ShaderResourceView** pTexture);
	//======================================.
	//	構造体.
	//======================================.
	//コンスタントバッファのアプリ側の定義.
	//※シェーダ内のコンスタントバッファと一致している必要あり.
	//D3DXMATRIX...float型の4バイト×４.
	struct SHADER_CONSTANT_BUFFER
	{
		ALINGN16 D3DMATRIX	 mW;				//ワールド行列.
		ALINGN16 float		 fViewPortWidth;	//ビューポート幅.
		ALINGN16 float		 fViewPortHeight;	//ビューポート高さ.
		ALINGN16 D3DXVECTOR4 vColor;			//アルファ値(透過で使用する).
		ALINGN16 D3DXVECTOR2 vUV;				//UV座標.
	};
	//頂点の構造体.
	struct VERTEX
	{
		D3DXVECTOR3	Pos;		//頂点座標.
		D3DXVECTOR2 Tex;		//テクスチャ座標.
	
	};

	//↓モデルの種類ごとに用意.
	ID3D11VertexShader*		m_pVertexShader;		//頂点シェーダ.
	ID3D11InputLayout*		m_pVertexLayout;		//頂点レイアウト.
	ID3D11PixelShader*		m_pPixelShader;			//ピクセルシェーダ.
	ID3D11Buffer*			m_pConstantBuffer;		//コンスタントバッファ.

	//↓モデルごとに用意.
	ID3D11Buffer*			m_pVertexBuffer;		//頂点バッファ.

	ID3D11SamplerState*		m_pSampleLinear;		//サンプラ:テクスチャに各種フィルタをかける.
	ID3D11ShaderResourceView*	m_pTexture;			//テクスチャ.

	int						m_AnimCount;			//カウンタ.
	D3DXVECTOR2				m_UV;					//テクスチャUV座標.


	D3DXVECTOR3				m_vPos;					//位置.
	float					m_Alpha;				//アルファ値.
	float					m_fScale;				//大きさ.
	D3DXVECTOR3				m_vRot;					//角度.
	TEXTMETRIC				TM;
	GLYPHMETRICS			GM;
	BYTE*					ptr;
};

#endif	//#ifndef CFONT_H.