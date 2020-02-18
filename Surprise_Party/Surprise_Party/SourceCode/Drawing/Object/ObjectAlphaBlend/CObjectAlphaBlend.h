#ifndef COBJECT_ALPHA_BLEND_H
#define COBJECT_ALPHA_BLEND_H

//警告につてのコード分析を無効にする. 4005:再定義.
#pragma warning( disable:4005)

//#include <Windows.h>
#include <d3dx9.h>
//#include <D3DX11.h>
//#include <D3D11.h>
//#include <D3DX10.h>	
//#include <D3D10.h>
//#include "..\..\..\MyMacro.h"
//
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
//#pragma comment(lib, "d3dx11.lib")
//#pragma comment(lib, "d3d11.lib")
//#pragma comment(lib, "d3dx10.lib")

#include "..\..\..\Global.h"

class CObjectAlphaBlend
{
public:
	CObjectAlphaBlend();
	virtual ~CObjectAlphaBlend();


	//===================関数========================//.
	HRESULT InitAlpha(ID3D11Device* pDevice11, ID3D11DeviceContext* pContext11);				//初期化処理関数.
	void SetAlphaDepth(bool flag);	//透過設定.
private:

	//===================変数=========================//.
	ID3D11Device*			m_pDevice11;
	ID3D11DeviceContext*	m_pContext11;
	ID3D11BlendState*		m_pBlendState;
	ID3D11BlendState*		m_pNoBlendState;
};

#endif	//#ifndef COBJECT_ALPHA_BLEND_H.