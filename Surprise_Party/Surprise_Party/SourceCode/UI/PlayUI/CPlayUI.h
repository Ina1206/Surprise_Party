#ifndef CPLAY_UI_H
#define CPLAY_UI_H

#include "..\CUI.h"

/*************************************
*	プレイ中のUIクラス.
*****/
class CPlayUI
	: public CUI
{
public:
	CPlayUI();
	virtual ~CPlayUI();

	//=====================定数========================//.
	const float	ALPHA_MAX				= 1.0f;								//透過値最大数.
	const float	ALPHA_MIN				= 0.0f;								//透過値最小値.

	const D3DXVECTOR3	SCALE_MAX		= D3DXVECTOR3(1.0f, 1.0f, 1.0f);	//大きさ最大数.
	const D3DXVECTOR3	SCALE_MIN		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//大きさ最小値.
	const D3DXVECTOR2	INIT_PATTARN_NO = D3DXVECTOR2(0.0f, 0.0f);			//基本パターン番号.

	//=====================関数========================//.
	virtual void UpDate() = 0;	//更新処理関数.
	
	void Render();				//描画処理関数.

protected:
	//=====================変数=========================//.
	std::vector<CSpriteUI*>		m_pCSpriteUI;	//スプライトUI.
	std::vector<D3DXVECTOR3>	m_vUIPos;		//UI座標.
	std::vector<D3DXVECTOR3>	m_vUIScale;		//UI大きさ.
	std::vector<D3DXVECTOR2>	m_vPatternNo;	//パターン番号.
	std::vector<float>			m_fUIAlpha;		//透過値.

private:

};

#endif	//#ifndef CPLAY_UI_H.	