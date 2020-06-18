#ifndef CPAUSE_H
#define CPAUSE_H

#include "..\SceneBase\CSceneBase.h"
#include "..\..\Drawing\Resource\CResourceManager.h"

/****************************************
*		一時停止クラス.
************/
class CPause
	: public CSceneBase
{
public:
	CPause();
	~CPause();

	//=====================定数=====================//.
	//const int	UI_MAX				= 4;		//UI最大数.
	//const int	SELECT_STRING_MAX	= 2;		//選択スプライト.
	//const int	CURSOR_NUM			= 2;		//カーソル番号.
	const int	PAUSE_NUM			= 3;		//ポーズ番号.
	//const float	SELECT_STRING_WIDHT = 100.0f;	//選択文章幅.
	const float CHANGE_CNT_MAX		= 10;		//変更カウント最大数.

	//const D3DXVECTOR3	SELECT_STRING_POS	= D3DXVECTOR3(700.0f, 400.0f, 0.0f);	//選択文章座標.
	//const D3DXVECTOR3	CURSOR_POS			= D3DXVECTOR3(800.0f, 450.0f, 0.0f);	//カーソル座標.
	//const D3DXVECTOR3	INIT_POS			= D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//初期座標.
	//const D3DXVECTOR3	INIT_ROT			= D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//初期角度.
	//const D3DXVECTOR3	CURSOR_ROT			= D3DXVECTOR3(0.0f, 3.0f, 0.0f);		//カーソル角度.
	//const D3DXVECTOR2	INIT_UV				= D3DXVECTOR2(0.0f, 0.0f);				//初期UV座標.
	//const D3DXVECTOR2	NORMAL_UV_POS		= D3DXVECTOR2(0.0f, 0.0f);				//通常UV座標.
	//const D3DXVECTOR2	ENTER_UV_POS		= D3DXVECTOR2(0.0f, 1.0f);				//決定時のUV座標.

	//=====================関数=====================//.
	void UpDate();		//更新処理関数.
	void Render();		//描画処理関数.

private:
	//=====================関数=====================//.
	void Init();		//初期化処理関数.
	void Release();		//解放処理関数.

	//=====================定数=====================//.
	//std::vector<CSpriteUI*>			m_pCSpriteUI;		//スプライトUI.
	//std::unique_ptr<D3DXVECTOR3[]>	m_vPos;				//座標.
	//std::unique_ptr<D3DXVECTOR3[]>	m_vRot;				//角度.
	//std::unique_ptr<D3DXVECTOR2[]>	m_vUV;				//UV座標.
	//CResourceManager*				m_pCResourceManager;//読み込み管理クラス.
	//CDepth_Stencil*					m_pCDepthStenceil;	//デプスステンシル.

	//int								m_SelectNum;		//選択番号.
	//int								m_ChangeCnt;		//変更カウント.
};

#endif	//#ifndef CPAUSE_H.