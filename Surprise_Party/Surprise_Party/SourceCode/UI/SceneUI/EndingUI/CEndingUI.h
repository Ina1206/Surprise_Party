#ifndef CENDING_UI_H
#define CENDING_UI_H


/*******************************************
*		エンディングUIクラス.
********************/
class CEndingUI
{
public:
	CEndingUI();
	~CEndingUI();

	//======================関数==========================//.
	void Update();		//更新処理関数.
	void Render();		//描画処理関数.

private:
	//======================関数==========================//.
	void Init();		//初期化処理関数.
	void Release();		//解放処理関数.


};


#endif	//#ifndef CENDING_UI_H.