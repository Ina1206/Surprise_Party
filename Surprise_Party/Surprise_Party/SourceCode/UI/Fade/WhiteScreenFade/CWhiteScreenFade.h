#ifndef CWHITE_SCREEN_FADE_H
#define CWHITE_SCREEN_FADE_H

#include "..\CFade.h"

/******************************************
*		白スクリーンフェードクラス.
************/
class CWhiteScreenFade
	: public CFade
{
public:
	CWhiteScreenFade();
	~CWhiteScreenFade();

	//========================関数=========================//.
	void Update();		//更新処理関数.
	void Render();		//描画処理関数.

private:
	//========================関数=========================//.
	void Init();		//初期化処理関数.
	void Release();		//解放処理関数.

	//========================変数=========================//.
	CSpriteUI*	m_pCSpriteUI;		//スプライトUIクラス.

};

#endif	//#ifndef CWHITE_SCREEN_FADE_H.