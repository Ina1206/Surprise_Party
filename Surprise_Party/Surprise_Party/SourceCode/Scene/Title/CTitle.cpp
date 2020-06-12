#include "CTitle.h"

/**********************************
*		タイトルクラス.
******/
CTitle::CTitle()
	: m_pCCameraTitle	(nullptr)
{
	//初期化処理関数.
	Init();
}

CTitle::~CTitle()
{
	//解放処理関数.
	Release();
}

//======================================.
//		更新処理関数.
//======================================.
void CTitle::UpDate()
{
	//タイトル用カメラの更新処理関数.
	m_pCCameraTitle->Update();
}

//======================================.
//		描画処理関数.
//======================================.
void CTitle::Render()
{
	//カメラ座標.
	const D3DXVECTOR3 m_vCameraPos = m_pCCameraTitle->GetPos();

}

//======================================.
//		初期化処理関数.
//======================================.
void CTitle::Init()
{
	m_vBackColor = D3DXVECTOR4(0.5f, 0.0f, 0.0f, 1.0f);

	//クラスをインスタンス化.
	m_pCCameraTitle.reset(new CCameraTitle());
}

//======================================.
//		解放処理関数.
//======================================.
void CTitle::Release()
{

}