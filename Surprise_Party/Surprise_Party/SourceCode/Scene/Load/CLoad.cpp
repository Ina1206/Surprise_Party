#include "CLoad.h"

/*********************************
*		読み込みシーンクラス.
***********/
CLoad::CLoad()
{

}

CLoad::~CLoad()
{
	//解放処理関数.
	Release();
}

//===================================.
//		初期化処理関数.
//===================================.
void CLoad::Init(HWND hWnd, ID3D11Device* pDevice11, ID3D11DeviceContext* pContext11)
{
	m_pCSpriteUI = std::make_unique<CSpriteUI>();
	SPRITE_STATE ss;
	ss.Base.w = WND_W;
	ss.Base.h = WND_H;
	ss.Stride.w = ss.Base.w;
	ss.Stride.h = ss.Base.h;
	ss.Frame.w = 1.0f;
	ss.Frame.h = 1.0f;
	ss.Disp.w = WND_W;
	ss.Disp.h = WND_H;
	
	//初期化処理関数.
	m_pCSpriteUI->Init(pDevice11, pContext11, "Data\\Texture\\UI\\Game\\LoadShutter.png", &ss);
}

//===================================.
//		描画処理関数.
//===================================.
void CLoad::Render()
{
	m_pCSpriteUI->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//描画処理関数.
	m_pCSpriteUI->Render();
}

//====================================.
//		解放処理関数.
//====================================.
void CLoad::Release()
{

}