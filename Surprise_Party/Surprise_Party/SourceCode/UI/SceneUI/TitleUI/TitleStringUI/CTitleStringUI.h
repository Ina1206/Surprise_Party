#ifndef CTITLE_STRING_UI_H
#define CTITLE_STRING_UI_H

#include "..\..\..\CUI.h"

/*********************************************
*		タイトル文章UIクラス.
*******************/
class CTitleStringUI
	: public CUI
{
public:
	CTitleStringUI();
	~CTitleStringUI();

	//====================関数==========================//.
	void Update();		//更新処理関数.
	void Render();		//描画処理関数.

private:
	//====================関数==========================//.
	void Init();		//初期化処理関数.
	void Release();		//解放処理関数.

	//====================変数==========================//.

};

#endif	//#ifndef CTITLE_STRING_UI_H.