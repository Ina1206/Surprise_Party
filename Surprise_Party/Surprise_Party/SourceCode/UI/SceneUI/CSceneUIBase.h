#ifndef CSCENE_UI_BASE_H
#define CSCENE_UI_BASE_H

#include "..\CUI.h"

/*****************************************
*		シーンUIの基底クラス.
****************/
class CSceneUIBase
	: public CUI
{
public:
	CSceneUIBase();
	virtual ~CSceneUIBase();

	//===================定数========================//.
	const D3DXVECTOR3	SELECT_STRING_POS = D3DXVECTOR3(700.0f, 400.0f, 0.0f);	//選択文章座標.
	const D3DXVECTOR3	CURSOR_POS = D3DXVECTOR3(800.0f, 450.0f, 0.0f);	//カーソル座標.
	const D3DXVECTOR3	INIT_POS = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//初期座標.
	const D3DXVECTOR3	INIT_ROT = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//初期角度.
	const D3DXVECTOR3	CURSOR_ROT = D3DXVECTOR3(0.0f, 3.0f, 0.0f);		//カーソル角度.
	const D3DXVECTOR2	INIT_UV = D3DXVECTOR2(0.0f, 0.0f);				//初期UV座標.
	const D3DXVECTOR2	NORMAL_UV_POS = D3DXVECTOR2(0.0f, 0.0f);				//通常UV座標.
	const D3DXVECTOR2	ENTER_UV_POS = D3DXVECTOR2(0.0f, 1.0f);				//決定時のUV座標.
	const float	SELECT_STRING_WIDHT = 100.0f;	//選択文章幅.
	const int	UI_MAX = 4;		//UI最大数.
	const int	SELECT_STRING_MAX = 2;		//選択スプライト.
	const int	CURSOR_NUM = 2;		//カーソル番号.
	const int	CHANGE_CNT_MAX = 10;		//変更カウント最大数.

	//===================関数========================//.
	void Update();		//更新処理関数.
	void Render();		//描画処理関数.

	//=============情報取得処理関数==================//.
	//選択終了フラグ.
	bool GetSelectFinishFlag() const { return m_bSelectFinishFlag; }

protected:
	//===================変数========================//.
	std::vector<CSpriteUI*>		m_pCSpriteUI;	//スプライトUI.

private:
	//===================関数========================//.
	void InitPos();		//初期座標設定処理関数.

	//===================変数========================//.
	std::vector<D3DXVECTOR3>	m_vUIPos;				//座標.
	std::vector<D3DXVECTOR2>	m_vUV;					//UV座標.
	std::vector<D3DXVECTOR3>	m_vUIRot;				//角度.

	int							m_SelectNum;			//選択番号.
	int							m_ChangeCnt;			//変更カウント.
	bool						m_bSelectFinishFlag;	//選択終了フラグ.
};

#endif	//#ifndef CSCENE_UI_BASE_H.