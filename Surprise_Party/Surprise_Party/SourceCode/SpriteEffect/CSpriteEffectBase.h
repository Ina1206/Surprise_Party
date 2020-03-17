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
	std::vector<CSprite*>		m_pCSprite;		//スプライトクラス.
	std::vector<D3DXVECTOR3>	m_vPos;			//座標.
	std::vector<D3DXVECTOR3>	m_vRot;			//角度.
	std::vector<D3DXVECTOR3>	m_vScale;		//大きさ.
	D3DXVECTOR3					m_vCenterPos;	//中央座標.

private:

};

#endif	//#ifndef CSPRITE_EFFECT_BASE_H.