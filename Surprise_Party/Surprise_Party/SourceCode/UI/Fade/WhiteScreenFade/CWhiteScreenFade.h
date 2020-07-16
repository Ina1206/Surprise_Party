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

	//========================定数=========================//.
	const unsigned int FADE_IN_FLAG		= (1 << 0);		//フェードインフラグ.
	const unsigned int FADE_OUT_FLAG	= (1 << 1);		//フェードアウトフラグ.
	const unsigned int FADE_FINISH_FLAG = (1 << 2);		//フェード終了フラグ.

	const float			ALPHA_MIN	= 0;			//透過値最小値.
	const float			ALPHA_SPEED = 0.009f;		//透過速度.

	//========================関数=========================//.
	void Update();		//更新処理関数.
	void Render();		//描画処理関数.

	//==================情報置換処理関数===================//.
	//フェードフラグ.
	void SetFadeFlag(const unsigned int& FadeFlag) { m_FadeFlag = FadeFlag; }

	//==================情報取得処理関数===================//.
	//フェードフラグ.
	unsigned int GetFadeFlag() const { return m_FadeFlag; }
	//透過値の割合.
	float GetAlphaRatio() const { return m_fAlphaRatio; }

private:
	//========================関数=========================//.
	void Init();		//初期化処理関数.
	void Release();		//解放処理関数.
	void FadeIn();		//フェードイン処理関数.
	void FadeOut();		//フェードアウト処理関数.
	void InitFade();	//フェード前の初期化処理関数.

	//========================変数=========================//.
	CSpriteUI*		m_pCSpriteUI;		//スプライトUIクラス.
	D3DXVECTOR3		m_vPos;				//座標.
	float			m_fAlpha;			//透過値.
	unsigned int	m_FadeFlag;			//フェードフラグ.			
	unsigned int	m_OldFadeFlag;		//差分用フェードフラグ.
	float			m_fAlphaRatio;		//透過値の割合.
};

#endif	//#ifndef CWHITE_SCREEN_FADE_H.