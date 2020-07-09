#ifndef CSCENE_UI_BASE_H
#define CSCENE_UI_BASE_H

#include "..\CUI.h"
#include "ChangeSceneCursorUI\CChangeSceneCursorUI.h"

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
	const D3DXVECTOR3	SELECT_STRING_POS	= D3DXVECTOR3(700.0f, 400.0f, 0.0f);	//選択文章座標.
	const D3DXVECTOR3	INIT_POS			= D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//初期座標.
	const D3DXVECTOR3	INIT_ROT			= D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//初期角度.
	const D3DXVECTOR2	INIT_UV				= D3DXVECTOR2(0.0f, 0.0f);				//初期UV座標.
	const int			UI_MAX				= 4;									//UI最大数.
	const int			SELECT_STRING_MAX	= 2;									//選択スプライト.

	//===================関数========================//.
	virtual void Update() = 0;										//更新処理関数.
	void Render();													//描画処理関数.

	//=============情報取得処理関数==================//.
	//選択終了フラグ.
	bool GetSelectFinishFlag() const { return m_pCCursor->GetSelectFinishFlag(); }

protected:
	//===================関数========================//.
	void Control(const bool& bChangeWaitFlag);						//操作処理関数.
	void InitElementCounts();										//要素数初期化処理関数.
	void ControlSelectStringPos();									//操作時選択文章座標設定処理関数.
	void InitCursor();												//カーソル初期設定処理関数.

	//===================変数========================//.
	std::vector<CSpriteUI*>					m_pCSpriteUI;			//スプライトUI.
	std::vector<D3DXVECTOR3>				m_vUIPos;				//座標.
	std::vector<D3DXVECTOR2>				m_vUV;					//UV座標.
	std::vector<D3DXVECTOR3>				m_vUIRot;				//角度.
	std::unique_ptr<CChangeSceneCursorUI>	m_pCCursor;				//カーソルクラス.

private:
	//===================関数========================//.
	void Release();													//解放処理関数.

	////===================変数========================//.
	//int							m_ChangeCnt;						//変更カウント.
};

#endif	//#ifndef CSCENE_UI_BASE_H.