#ifndef CSPRITE_EFFECT_BASE_H
#define CSPRITE_EFFECT_BASE_H

#include "..\Drawing\Resource\CResourceManager.h"
#include "..\..\Global.h"

/*********************************************
*		スプライトのエフェクト基底クラス.
********/
class CSpriteEffectBase
{
public:
	CSpriteEffectBase();
	virtual ~CSpriteEffectBase();

	//================定数====================//.
	const float			SCALE_MAX		= 1.0f;								//大きさ最大値.
	const float			SCALE_MIN		= 0.0f;								//大きさ最小値.
	const float			ALPHA_MAX		= 1.0f;								//透過値最大値.
	const float			ALPHA_MIN		= 0.0f;								//透過値最小値.

	const int			BUBBLE_MAX		= 4;								//泡最大数.
	const int			Z_MAX			= 3;								//Z最大数.
	const int			ALL_SPRITE_MAX	= BUBBLE_MAX + Z_MAX;				//全てのスプライト最大数.

	const D3DXVECTOR3	INIT_LOCAL_POS	= D3DXVECTOR3(-2.3f, 2.0f, 0.0f);	//初期のローカル座標.

	const int			CHANGE_ADD_SUB	= -1;								//加算減算変更数値.

	const float			PI				= 3.14159265358979323846264338f;	//円周率.

	//================関数====================//.
	virtual void Update() = 0;																				//更新処理関数.
	void	Render(const D3DXMATRIX& mView, const D3DXMATRIX& mProj, const D3DXVECTOR3& vCameraPos);	//描画処理関数.

	//==========情報置換処理関数==============//.
	void SetCenterPos(const D3DXVECTOR3& vPos) { m_vCenterPos = vPos; }		//中央座標.

protected:
	//================関数====================//.
	virtual void Init() = 0;		//初期化処理関数.
	virtual void Release() = 0;		//解放処理関数.

	//================変数====================//.
	std::vector<CSprite*>		m_pCSprite;			//スプライトクラス.
	std::vector<D3DXVECTOR3>	m_vPos;				//座標.
	std::vector<D3DXVECTOR3>	m_vRot;				//角度.
	std::vector<float>			m_fScale;			//大きさ.
	std::vector<float>			m_fAlpha;			//透過値.
	D3DXVECTOR3					m_vCenterPos;		//中央座標.
	CResourceManager*			m_pCResourceManager;//読み込み管理クラス.
	CDepth_Stencil*				m_pCDepthStencil;	//デプスステンシル.
	
	std::vector<bool>			m_bDispFlag;		//表示フラグ.
	int							m_DispCnt;			//表示カウント.
	int							m_ChangeAddSub;		//加算減算変更.

private:

};

#endif	//#ifndef CSPRITE_EFFECT_BASE_H.