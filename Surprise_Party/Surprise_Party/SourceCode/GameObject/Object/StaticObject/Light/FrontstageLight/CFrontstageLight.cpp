#include "CFrontstageLight.h"

/*********************************
*		表舞台のライトクラス.
*************/
CFrontstageLight::CFrontstageLight()
	: m_vLightPos			()
	, m_vCameraPos			(0.0f, 0.0f, 0.0f)
{
	//初期化処理関数.
	Init();
}

CFrontstageLight::~CFrontstageLight()
{
	//解放処理関数.
	Release();
}

//=======================================.
//		更新処理関数.
//=======================================.
void CFrontstageLight::Update()
{
	for (unsigned int light = 0; light < m_vLightPos.size(); light++) {
		if (m_vCameraPos.x + REFLECTION_RANGE > m_vLightPos[light].x &&
			m_vCameraPos.x - REFLECTION_RANGE < m_vLightPos[light].x) {
			m_stLight.vPos = m_vLightPos[light];
			break;
		}
	}
}

//=======================================.
//		全てのライトの座標設定処理関数.
//=======================================.
void CFrontstageLight::SettingAllLightPos(const float& fDistance)
{
	//ライトの配置横幅.
	float m_LightWidth = m_stLight.fLightPosWidth;
	for (int Light = 0; m_LightWidth * Light <= fDistance; Light++) {
		D3DXVECTOR3 vLightPos = m_stLight.vPos;
		vLightPos.x = m_LightWidth * Light;
		m_vLightPos.push_back(vLightPos);
	}

}

//=======================================.
//		初期化処理関数.
//=======================================.
void CFrontstageLight::Init()
{
	//ライト情報初期設定.
	m_stLight.vPos				= LIGHT_POS;
	m_stLight.fIntensity		= LIGHT_INTENSITY;
	m_stLight.m_fLightWidth		= LIGHT_WIDTH;
	m_stLight.fLightPosWidth	= LIGHT_POS_WIDHT;
	m_stLight.vLightColor		= LIGHT_COLOR;
	m_stLight.m_fLightMax		= LIGHT_MAX;
	D3DXMatrixIdentity(&m_stLight.mRot);

	D3DXMATRIX mYaw, mPich, mRoll;
	D3DXMatrixRotationY(&mYaw, 0.0f);
	D3DXMatrixRotationX(&mPich, 0.0f);
	D3DXMatrixRotationZ(&mRoll, 0.0f);
	m_stLight.mRot = mYaw * mPich * mRoll;


}

//=======================================.
//		解放処理関数.
//=======================================.
void CFrontstageLight::Release()
{

}