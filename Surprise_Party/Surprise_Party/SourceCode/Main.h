#ifndef MAIN_H
#define MAIN_H
//警告についてのコード分析を無効にする.4005:再定義.
#pragma warning( disable:4005 )
#include <Windows.h>
#include <stdio.h>

#include <D3DX11.h>
#include <D3D11.h>
#include <D3DX10.h>
#include <D3D10.h>
#include <d3dx9.h>

#include "MyMacro.h"
#include "Global.h"

#include <memory>
#include "Scene/SceneManager/CSceneManager.h"
#include "Scene/Load/CLoad.h"

//ライブラリ読み込み.
#pragma comment( lib, "winmm.lib")
#pragma comment( lib, "d3dx11.lib")
#pragma comment( lib, "d3d11.lib")
#pragma comment( lib, "d3dx10.lib")	
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

//=================================================.
//	定数.
//=================================================.
const char WND_TITLE[] = "SurpriseParty";
const char APP_NAME[] = "SurpriseParty";

/********************************************
*	メインクラス.
**/
class CMain
{
public:

	CMain();	//コンストラクタ.
	~CMain();	//デストラクタ.

	//ウィンドウ初期化関数.
	HRESULT InitWindow(
		HINSTANCE hInstance,
		INT x, INT y, INT width, INT height,
		const char* WindowName);

	//ウィンドウ関数(メッセージ毎の処理).
	LRESULT MsgProc(
		HWND hWnd, UINT uMsg,
		WPARAM wParam, LPARAM lParam);

	//メッセージループ.
	void Loop();

	//読み込み処理関数.
	void Load();
	//更新処理関数.
	void UpDate();
	//レンダリング(描画).
	void Render();


//------------------------------.
//	ここから３D関係.

	//DirectX初期化.
	HRESULT InitD3D();
	//Direct3D終了処理.
	void DestroyD3D();

	//メッシュの読み込み関数.
	HRESULT LoadMesh();

	//バックバッファクリア関数.
	void ClearBackBuffer();
	//プロジェクション関数.
	void Proj();


	//=============情報置換処理関数===========//.
	void SethWnd(HWND hWnd) {
		m_hWnd = hWnd;
	}
private:
	HWND							m_hWnd;					//ウィンドウハンドル.
	ID3D11Device*					m_pDevice11;			//デバイスオブジェクト.
	ID3D11DeviceContext*			m_pContext11;			//デバイスコンテキスト.
	IDXGISwapChain*					m_pSwapChain;			//スワップチェーン.
	ID3D11RenderTargetView*			m_pBackBuffer_TexRTV;	//レンダーターゲットビュー.
	ID3D11Texture2D*				m_pBackBuffer_DSTex;	//デプスステンシル用テクスチャ.
	ID3D11DepthStencilView*			m_pBackBuffer_DSTexDSV;	//デプスステンシルビュー.
	LPDIRECT3D9						m_pD3d9;				//Dx9オブジェクト.
	LPDIRECT3DDEVICE9				m_pDevice9;				//Dx9デバイス.

	D3DXMATRIX						m_mProj;				//プロジェクション行列.

	std::unique_ptr<CSceneManager>	m_pCSceneManager;		//シーン管理クラス.
	std::unique_ptr<CLoad>			m_pCLoad;				//読み込みクラス.
	
};

#endif//#ifndef MAIN_H
