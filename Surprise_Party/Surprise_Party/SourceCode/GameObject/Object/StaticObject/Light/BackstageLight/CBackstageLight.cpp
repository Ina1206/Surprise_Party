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
	m_stLight.fIntensity		= 27.0f;
	m_stLight.fLightPosWidth	= 20.0f;
	m_stLight.m_fLightWidth		= 6.2f;
	m_stLight.m_fLightMax		= 1.0f;
	m_stLight.vLightColor		= D3DXVECTOR3(243.0f, 232.0f, 12.0f) / 255.0f;
	m_stLight.vPos				= D3DXVECTOR3(26.2f, 11.7f, 6.7f);
	D3DXMatrixRotationYawPitchRoll(&m_stLight.mRot, 0.0f, 0.0f, 0.0f);
}

//=========================================.
//		解放処理関数.
//=========================================.
void CBackstageLight::Release()
{

}