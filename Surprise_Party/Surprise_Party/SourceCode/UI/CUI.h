#ifndef CUI_H
#define CUI_H

#include "..\Global.h"
#include "..\Drawing\Resource\CResourceManager.h"
#include "..\Drawing\Sprite\CDepth_Stencil.h"

/*************************************
*		UIクラス.
*****/
class CUI
{
public:
	CUI();
	virtual ~CUI();

	//=====================定数=========================//.
	const float	ALPHA_MAX		= 1.0f;			//透過値最大値.
	const float	UI_INIT_SCALE	= 1.0f;			//初期の大きさ.

	//=====================関数=========================//.
	virtual void Render() = 0;		//描画処理関数.

protected:
	//=====================関数=========================//.
	virtual void Init() = 0;		//初期化処理関数.
	virtual void Release() = 0;		//解放処理関数.

	//=====================変数=========================//.
	CResourceManager*	m_pCResourceManager;//読み込み管理クラス.
	CDepth_Stencil*		m_pCDepthStencil;	//デプスステンシルクラス.
	D3DXVECTOR3			m_vPos;				//座標.
	D3DXVECTOR3			m_vRot;				//角度.
	float				m_fScale;			//大きさ.
	float				m_fAlpha;			//透過値.
};

#endif	//#ifndef CUI_H.