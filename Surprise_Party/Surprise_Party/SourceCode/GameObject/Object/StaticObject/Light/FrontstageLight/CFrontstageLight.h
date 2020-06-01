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