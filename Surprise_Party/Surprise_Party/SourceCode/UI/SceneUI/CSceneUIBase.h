#ifndef CSCENE_UI_BASE_H
#define CSCENE_UI_BASE_H

#include "..\CUI.h"
#include "ChangeSceneCursorUI\CChangeSceneCursorUI.h"
#include "SelectStringUI\CSelectStringUI.h"
#include "..\..\Sound\PlaySoundManager\CPlaySoundManager.h"

/*****************************************
*		シーンUIの基底クラス.
****************/
class CSceneUIBase
	: public CUI
{
public:
	CSceneUIBase();
	virtual ~CSceneUIBase();

	//===================関数========================//.
	virtual void Update() = 0;										//更新処理関数.
	void Render();													//描画処理関数.

	//=============情報取得処理関数==================//.
	//選択終了フラグ.
	bool GetSelectFinishFlag() const { return m_pCCursor->GetSelectFinishFlag(); }

protected:
	//===================関数========================//.
	virtual void RenderSceneTitle();								//シーンタイトル描画処理関数.

	//===================変数========================//.
	CSpriteUI*								m_pCSpriteUI;			//スプライトUI.
	std::unique_ptr<CChangeSceneCursorUI>	m_pCCursor;				//カーソルクラス.
	std::unique_ptr<CSelectStringUI>		m_pCSelectStringUI;		//選択文章UIクラス.
	CPlaySoundManager*						m_pCPlaySoundManager;	//音再生管理クラス.

private:
	//===================関数========================//.
	void Release();													//解放処理関数.

};

#endif	//#ifndef CSCENE_UI_BASE_H.