#ifndef CMOVE_OBJECT_BASE_H
#define CMOVE_OBJECT_BASE_H

#include "..\CObjectBase.h"
#include "..\..\SpriteEffect\SmokeEffect\CSmokeEffect.h"

/***************************************************
*		動くオブジェクト基底クラス.
***********/
class CMoveObjectBase
	: public CObjectBase
{
public:
	CMoveObjectBase();
	~CMoveObjectBase();

	//==============定数===============//.
	const int	EFFECT_HANDLE_DEFAULT_VALUE = -1;		//エフェクトハンドル初期値.

	//==============関数===============//.
	void EffectRender();								//エフェクト描画処理関数.
	void AttachedObjRender();							//付属オブジェクト描画処理関数.

	//=========情報置換処理関数========//.
	//カメラ表示フラグ.
	void SetCameraDispFlag() { m_bCameraDisp = true; }
	//付属オブジェクト座標.
	void SetAttachedObjPos(const int objNum ,const D3DXVECTOR3& vPos) { m_vAttachedObjPos[objNum] = vPos; }
	//付属オブジェクト角度.
	void SetAttachedObjRot(const int objNum, const D3DXVECTOR3& vRot) { m_vAttachedObjRot[objNum] = vRot; }
	//オブジェクトが動いたときのエフェクトフラグ.
	void SetMoveObjectEffect(const bool& flag) { m_bMoveObjectEffect = flag; }
	//ポーズフラグ.
	void SetPauseFlag(const bool& bFlag) { m_bPauseFlag = bFlag; }
protected:
	//==============関数===============//.
	void Hit();											//当たり判定処理関数.
	void EffectUpdate();								//エフェクト更新処理関数.

	//==============変数===============//.
	CEffect*					m_pCEffect;				//エフェクト.
	int							m_EffectHandle;			//エフェクトハンドル.
	bool						m_bCameraDisp;			//カメラに表示しているフラグ.
	D3DXVECTOR3					m_vEffectPos;			//エフェクト座標.
	float						m_fEffectScale;			//エフェクト大きさ.
	std::vector<CDX9Mesh*>		m_pCAttachedObjMesh;	//付属オブジェクトメッシュ.
	std::vector<D3DXVECTOR3>	m_vAttachedObjPos;		//付属オブジェクト座標.
	std::vector<D3DXVECTOR3>	m_vAttachedObjRot;		//付属オブジェクト角度.
	bool						m_bMoveObjectEffect;	//オブジェクトが動いたときのエフェクトフラグ.

	bool						m_bPauseFlag;			//ポーズフラグ.

	std::vector<std::unique_ptr<CSpriteEffectBase>> m_pCSpriteEffect;

private:
	//===============関数===============//.
	void EffectPlay();									//エフェクト再生処理関数.
	void EffectStop();									//エフェクト停止処理関数.
};

#endif	//#ifndef CMOVE_OBJECT_BASE_H.