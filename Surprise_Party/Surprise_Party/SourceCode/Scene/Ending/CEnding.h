#ifndef CENDING_H
#define CENDING_H

#include "..\SceneBase\CSceneBase.h"

#include "BeforeResultStage\CBeforeResultStage.h"

/************************************************
*		エンディングクラス.
***********/
class CEnding
	: public CSceneBase
{
public:
	CEnding();
	~CEnding();

	//========================関数===========================//.
	void UpDate();		//更新処理関数.
	void Render();		//描画処理関数.
private:
	//========================関数===========================//.
	void Init();		//初期化処理関数.
	void Release();		//解放処理関数.

	//========================変数===========================//.
	std::unique_ptr<CEndingStageBase>	m_pCEndingStageBase;	//エンディングステージ基底クラス.

};

#endif	//#ifndef CENDING_H.