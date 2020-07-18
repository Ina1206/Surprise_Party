#include "CBackstageLight.h"

/*******************************************
*		舞台裏のライトクラス.
************/
CBackstageLight::CBackstageLight()
{
	//初期化処理関数.
	Init();
}

CBackstageLight::~CBackstageLight()
{
	//解放処理関数.
	Release();
}

//=========================================.
//		更新処理関数.
//=========================================.
void CBackstageLight::Update()
{

}

//=========================================.
//		初期化処理関数.
//=========================================.
void CBackstageLight::Init()
{
	m_stLight.fIntensity		= LIGHT_INTENSITY;
	m_stLight.fLightPosWidth	= LIGHT_POS_WIDTH;
	m_stLight.m_fLightWidth		= LIGHT_WIDTH;
	m_stLight.m_fLightMax		= LIGHT_MAX;
	m_stLight.vLightColor		= LIGHT_COLOR / LIGHT_BASE_COLOR;
	m_stLight.vPos				= LIGHT_POS;
	D3DXMatrixRotationYawPitchRoll(&m_stLight.mRot, 0.0f, 0.0f, 0.0f);
}

//=========================================.
//		解放処理関数.
//=========================================.
void CBackstageLight::Release()
{

}