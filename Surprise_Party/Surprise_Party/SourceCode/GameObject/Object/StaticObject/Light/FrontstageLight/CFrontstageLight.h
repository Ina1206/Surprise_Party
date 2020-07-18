#ifndef CFRONTSTAGE_LIGHT_H
#define CFRONTSTAGE_LIGHT_H

#include "..\CLightBase.h"

/*********************************
*		表舞台のライトクラス.
*************/
class CFrontstageLight
	: public CLightBase
{
public:
	CFrontstageLight();
	~CFrontstageLight();

	//======================定数========================//.
	const float			REFLECTION_RANGE	= 16.0f;							//写る範囲.
	const D3DXVECTOR3	LIGHT_POS			= D3DXVECTOR3(0.0f, 21.7f, -0.5f);	//座標.
	const float			LIGHT_INTENSITY		= 119.0f;							//ライトの強さ.
	const float			LIGHT_WIDTH			= 10.9f;							//ライト幅.
	const float			LIGHT_POS_WIDHT		= 20.0f;							//ライトの座標幅.
	const D3DXVECTOR3	LIGHT_COLOR			= D3DXVECTOR3(0.5f, 0.5f, 1.0f);	//ライトの色.
	const float			LIGHT_MAX			= 3.0f;								//ライトの最大値.

	//======================関数========================//.
	void Update();										//更新処理関数.
	void SettingAllLightPos(const float& fDistance);	//全てのライトの座標設定処理関数.

	//================情報置換処理関数==================//.
	void SetCameraPos(const D3DXVECTOR3& vCameraPos) { m_vCameraPos = vCameraPos; }

private:
	//======================関数========================//.
	void Init();										//初期化処理関数.
	void Release();										//解放処理関数.

	//======================変数========================//.
	std::vector<D3DXVECTOR3>	m_vLightPos;			//ライト複数座標.
	D3DXVECTOR3					m_vCameraPos;			//カメラ座標.
};

#endif	//#ifndef CFRONTSTAGE_LIGHT_H.