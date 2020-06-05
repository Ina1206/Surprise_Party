#ifndef CDX9MESH_H
#define CDX9MESH_H

#include "..\CDX9Base.h"

const int SHADOW_MAX = 10;

//スフィア構造体.
struct SPHERE
{
	D3DXVECTOR3 vCenter;	//中心.
	float		fRadius;	//半径.
};
//バウンディングボックス構造体.
struct BBOX
{
	D3DXVECTOR3 vPosMax;	//最大頂点.
	D3DXVECTOR3 vPosMin;	//最小頂点.
	D3DXVECTOR3 vAxisX;		//x軸.
	D3DXVECTOR3 vAxisY;		//y軸.
	D3DXVECTOR3 vAxisZ;		//z軸.
	FLOAT		LenghtX;	//X長さ.
	FLOAT		LenghtY;	//Y長さ.
	FLOAT		LenghtZ;	//Z長さ.

	//初期化.
	BBOX()
		: vPosMax(), vPosMin()
		, vAxisX(1.0f, 0.0f, 0.0f)
		, vAxisY(0.0f, 1.0f, 0.0f)
		, vAxisZ(0.0f, 0.0f, 1.0f)
		, LenghtX(0.0f), LenghtY(0.0f), LenghtZ(0.0f)
	{}
};

//メッシュデータをファイルから取り出す為だけにDirectX9を使用する.
//※レンダリング(描画)は、DirectX11で行う.
class CDX9Mesh
	: public CDX9Base
{
public:
	CDX9Mesh();		//コンストラクタ.
	~CDX9Mesh();	//デストラクタ.

	HRESULT Init(HWND hWnd, LPDIRECT3DDEVICE9 pDevice9,ID3D11Device* pDevice11,
		ID3D11DeviceContext* pContext11, const char* fileName, const bool& bSpotLightHLSL);

	//レンダリング用.
	void Render(const D3DXMATRIX& mView, const D3DXMATRIX& mProj,
				const D3DXVECTOR3& vCamPos, const LIGHT& stLight);
	//解放関数.
	void Release();

	//メッシュを取得.
	LPD3DXMESH GetMesh() {
		return m_pMesh;
	}

	SPHERE m_Sphere;			//スフィア構造体.
	BBOX   m_BBox;				//Bボックス構造体.



	LPD3DXMESH	m_pMeshForRay;	//レイとメッシュ用.

private:

	//メッシュ読み込み.
	HRESULT LoadXMesh(const char* fileName);

	//シェーダ作成.
	HRESULT InitShader();

	//頂点の構造体.
	struct VERTEX
	{
		D3DXVECTOR3	Pos;		//頂点座標.
		D3DXVECTOR3 Normal;		//法線(陰影計算に必須).
		D3DXVECTOR2 Tex;		//テクスチャ座標.
	};
	//マテリアル構造体.
	struct MY_MATERIAL
	{
		D3DXVECTOR4					Ambient;			//アンビエント.
		D3DXVECTOR4					Diffuse;			//ディフューズ.
		D3DXVECTOR4					Specular;			//スペキュラー.
		char						szTextureName[128];	//テクスチャファイル名.
		ID3D11ShaderResourceView*	pTexture;			//テクスチャ.
		DWORD						dwNumFace;			//そのマテリアルのポリゴン数.
		//コンストラクタ.
		MY_MATERIAL()
			:Ambient(),Diffuse(),Specular(), szTextureName()
			,pTexture(nullptr), dwNumFace(0)
		{
		}
		//デストラクタ.
		~MY_MATERIAL(){
			SAFE_RELEASE(pTexture);
		}
	};


	//Dx9.
	LPDIRECT3D9				m_pD3d9;				//Dx9オブジェクト.

	ID3D11Buffer*			m_pVertexBuffer;		//頂点バッファ.
	ID3D11Buffer**			m_ppIndexBuffer;		//インデックスバッファ.
	ID3D11SamplerState*		m_pSampleLinear;		//サンプラ:テクスチャに各種フィルタをかける.

	LPD3DXMESH				m_pMesh;				//メッシュオブジェクト.
	DWORD					m_NumMaterials;			//マテリアル数.

	MY_MATERIAL*			m_pMaterials;			//マテリアル構造体.
	DWORD					m_NumAttr;				//属性数.
	DWORD					m_AttrID[300];			//属性ID　※300属性まで.

	bool					m_EnableTexture;		//テクスチャあり.

	//レンダリング関数(クラス内でのみ使用).
	void RenderMesh(const D3DXMATRIX& mWorld, const D3DXMATRIX& mView, const D3DXMATRIX& mProj);

};


#endif	//#ifndef CDX9MESH_H