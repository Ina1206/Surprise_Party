#ifndef _CDX9BASE_H
#define _CDX9BASE_H

#include "ObjectAlphaBlend\CObjectAlphaBlend.h"
#define ALIGN16 _declspec(align(16))

//ﾗｲﾄ情報.
struct LIGHT
{
	D3DXVECTOR3	vPos;			//位置.
	D3DXMATRIX	mRot;			//回転行列.
	float		fIntensity;		//強度(明るさ).
	float		m_fLightWidth;	//光の広さ.
	D3DXVECTOR3 vLightColor;	//ライトの色.
};

/***************************************
*	DirectX9Draw基底クラス.
***************/
class CDX9Base
{
public:
	CDX9Base();
	virtual ~CDX9Base();

	//位置情報を設定.
	//inline void のinlineは関数自体を直接展開するため速度が上がる.
	void SetPosition(float x, float y, float z) {
		m_vPos.x = x;
		m_vPos.y = y;
		m_vPos.z = z;
	}
	void SetPosition(const D3DXVECTOR3& vPos) {
		m_vPos = vPos;
	}
	//位置情報を取得.
	D3DXVECTOR3 GetPosition()
	{
		return m_vPos;
	}
	//回転情報を設定.
	void SetRotation(const D3DXVECTOR3& vRot) {
		m_vRot = vRot;
	}
	//回転情報を取得.
	D3DXVECTOR3 GetRotation() {
		return m_vRot;
	}
	//拡縮情報を設定.
	void SetScale(float Scale) { m_fScale = Scale; }
	//拡縮情報を取得.
	float GetScale() { return m_fScale; }

	//透過値を設定.
	void SetAlpha(const float& Alpha) { m_fAlpha = Alpha; }

	//初期位置をずらす.
	void SetPrePos(D3DXVECTOR3 vPrePos) { m_vPrePos = vPrePos; }

	//回転行列作成.
	void SetRot(const D3DXMATRIX& mRot) {
		m_bvRotNotUse = true;
		m_mRot = mRot;
	}

	//回転角度反映.
	void SetRotAngleApplication() {
		m_bvRotNotUse = false;
	}

	void SetUV(const D3DXVECTOR2& vUV) { m_vUV = vUV; }

	void SetAlphaDepth(const bool& flag) { m_pCObjectAlphaBlend->SetAlphaDepth(flag); }

protected:
	//======================================.
	//	構造体.
	//======================================.
	//コンスタントバッファのアプリ側の定義.
	//※シェーダ内のコンスタントバッファと一致している必要あり.
	struct CBUFFER_PER_MESH
	{
		D3DXMATRIX	mW;			//ワールド行列.
		D3DXMATRIX	mWVP;		//ワールド,ビュー,プロジェクションの合成変換行列.
	};
	struct CBUFFER_PER_MATERIAL
	{
		D3DXVECTOR4 vAmbient;	//アンビエント色(環境色).
		D3DXVECTOR4	vDiffuse;	//ディフューズ色(拡散反射色).
		D3DXVECTOR4 vSpecular;	//スペキュラ色(鏡面反射色).
	};
	//フレーム単位で渡す情報.
	struct CBUFFER_PER_FRAME
	{
		D3DXVECTOR4			vCamPos;		//カメラ位置(視点位置).
		D3DXVECTOR4			vLightPos;		//ライト方向.
		D3DXMATRIX			mLightRot;		//ライト角度.
		D3DXVECTOR4			fIntensity;		//ﾗｲﾄ強度(明るさ).
		D3DXVECTOR4			fLightWidth;	//ライトの広さ.
		D3DXVECTOR4			vLightColor;	//ライト色.
		D3DXVECTOR4			vAlpha;			//色.
		D3DXVECTOR4			vUV;			//UV.			
	};

	HWND								m_hWnd;					//ウィンドウハンドル.
	LPDIRECT3DDEVICE9					m_pDevice9;				//Dx9デバイスオブジェクト.

	ID3D11Device*						m_pDevice11;			//デバイスオブジェクト.
	ID3D11DeviceContext*				m_pContext11;			//デバイスコンテキスト.
	ID3D11VertexShader*					m_pVertexShader;		//頂点シェーダ.
	ID3D11InputLayout*					m_pVertexLayout;		//頂点レイアウト.
	ID3D11PixelShader*					m_pPixelShader;			//ピクセルシェーダ.
	ID3D11Buffer*						m_pCBufferPerMesh;		//コンスタントバッファ(メッシュ毎).
	ID3D11Buffer*						m_pCBufferPerMaterial;	//コンスタントバッファ(マテリアル毎).
	ID3D11Buffer*						m_pCBufferPerFrame;		//コンスタントバッファ(フレーム毎)

	D3DXVECTOR3							m_vPos;					//位置.
	D3DXVECTOR3							m_vRot;					//角度.
	float								m_fScale;				//大きさ.
	D3DXVECTOR3							m_vPrePos;				//読み込み時のオブジェクトの中心軸差分.

	float								m_fAlpha;				//透過値.

	D3DXVECTOR2							m_vUV;					//UV.
	bool								m_bvRotNotUse;			//角度使わないフラグ.
	D3DXMATRIX							m_mRot;					//回転行列.

	std::unique_ptr<CObjectAlphaBlend>	m_pCObjectAlphaBlend;	//オブジェクトアルファブレンド.
};

#endif	//#ifndef _CDX9BASE_H.