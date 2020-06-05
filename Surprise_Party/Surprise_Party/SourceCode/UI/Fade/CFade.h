#ifndef CFADE_H
#define CFADE_H

#include "..\CUI.h"

/******************************************
*		フェードクラス.
***********/
class CFade
	: public CUI
{
public:
	CFade();
	virtual ~CFade();

	//======================関数==========================//.
	virtual void Update() = 0;	//更新処理関数.
	virtual void Render() = 0;	//描画処理関数.


protected:
	//======================関数===========================//.
	virtual void Init() = 0;	//初期化処理関数.
	virtual void Release() = 0;	//解放処理関数.

	//======================変数===========================//.
	CResourceManager*	m_pCResourceManager;	//リソース管理クラス.

};

#endif	//#ifndef CFADE_H.