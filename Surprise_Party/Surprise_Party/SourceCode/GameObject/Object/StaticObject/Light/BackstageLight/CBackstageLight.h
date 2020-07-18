#ifndef CBACKSTAGE_LIGHT_H
#define CBACKSTAGE_LIGHT_H

#include "..\CLightBase.h"

/*******************************************
*		舞台裏のライトクラス.
************/
class CBackstageLight
	: public CLightBase
{
public:
	CBackstageLight();
	~CBackstageLight();

	//=======================定数==========================//.
	const float			LIGHT_INTENSITY = 27.0f;								//ライトの強さ.
	const float			LIGHT_POS_WIDTH	= 20.0f;								//ライトの座標幅.
	const float			LIGHT_WIDTH		= 6.2f;									//ライトの幅.
	const float			LIGHT_MAX		= 1.0f;									//ライトの個数.
	const D3DXVECTOR3	LIGHT_COLOR		= D3DXVECTOR3(243.0f, 232.0f, 12.0f);	//ライトの色.
	const float			LIGHT_BASE_COLOR= 255.0f;								//色の基準値.
	const D3DXVECTOR3	LIGHT_POS		= D3DXVECTOR3(26.2f, 11.7f, 6.7f);		//ライトの座標.

	//=======================関数==========================//.
	void Update();		//更新処理関数.

private:
	//=======================関数==========================//.
	void Init();		//初期化処理関数.
	void Release();		//解放処理関数.


};

#endif	//#ifndef CBACKSTAGE_LIGHT_H.