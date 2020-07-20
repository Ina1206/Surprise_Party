#ifndef CPAUSE_H
#define CPAUSE_H

#include "..\SceneBase\CSceneBase.h"
#include "..\..\Drawing\Resource\CResourceManager.h"
#include "..\..\UI\SceneUI\CPauseUI\CPuaseUI.h"

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
	const int	SELECT_TITLE_NUM = 1;	//選択タイトル番号.

	//=====================関数=====================//.
	void UpDate();		//更新処理関数.
	void Render();		//描画処理関数.

private:
	//=====================関数=====================//.
	void Init();		//初期化処理関数.
	void Release();		//解放処理関数.

	//=====================変数=====================//.
	std::unique_ptr<CPauseUI>			m_pCPauseUI;		//ポーズUI.
};

#endif	//#ifndef CPAUSE_H.