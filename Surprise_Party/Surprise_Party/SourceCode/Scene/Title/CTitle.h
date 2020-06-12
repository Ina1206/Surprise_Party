#ifndef CTITLE_H
#define CTITLE_H

#include "..\SceneBase\CSceneBase.h"
#include "..\..\Camera\CameraTitle\CCameraTitle.h"

/**********************************
*		タイトルクラス.
******/
class CTitle
	: public CSceneBase
{
public:
	CTitle();
	~CTitle();

	//====================関数========================//.
	void UpDate();		//更新処理関数.
	void Render();		//描画処理関数.
protected:
	//====================関数========================//.
	void Init();		//初期化処理関数.
	void Release();		//解放処理関数.

	//====================変数========================//.
	std::unique_ptr<CCameraTitle>	m_pCCameraTitle;	//タイトル用カメラクラス.
};


#endif	//#ifndef CTITLE_H.