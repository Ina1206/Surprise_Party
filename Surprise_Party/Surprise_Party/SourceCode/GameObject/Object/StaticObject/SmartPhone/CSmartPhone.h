#ifndef CSMART_PHONE_H
#define CSMART_PHONE_H

#include "..\CStaticObjectBase.h"

/********************************************
*		スマートフォンクラス
*************/
class CSmartPhone
	: public CStaticObjectBase
{
public:
	CSmartPhone();
	~CSmartPhone();

	//=========================定数==============================//.
	const float			SCROLL_SPEED	= 0.05f;								//スクロール速度.
	const float			SCROLL_MAX		= 1.0f;									//スクロール最大値.
	const float			SCALE			= 0.05f;								//大きさ.
	const D3DXVECTOR3	ROT				= D3DXVECTOR3(-30.0f, 170.0f, -5.0f);	//傾き.

	//========================列挙体=============================//.
	//行動種類.
	enum class enMoveType {
		SeenGhsot,		//お化けに見られている時.
		Drop,			//落ちる
	};

	//=========================関数==============================//.
	void Update();		//更新処理関数.
	void Render();		//描画処理関数.

	

private:
	//=========================関数==============================//.
	void Init();		//初期化処理関数.
	void Release();		//解放処理関数.

	//=========================変数==============================//.
	D3DXVECTOR2	m_vUV;	//UV座標.

};

#endif	//#ifndef CSMART_PHONE_H.