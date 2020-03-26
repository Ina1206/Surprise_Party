#ifndef CPAUSE_H
#define CPAUSE_H

#include "..\SceneBase\CSceneBase.h"

/****************************************
*		一時停止クラス.
************/
class CPause
	: public CSceneBase
{
public:
	CPause();
	~CPause();

	//=====================関数=====================//.
	void UpDate();		//更新処理関数.
	void Render();		//描画処理関数.

private:
	//=====================関数=====================//.
	void Init();		//初期化処理関数.
	void Release();		//解放処理関数.

};

#endif	//#ifndef CPAUSE_H.