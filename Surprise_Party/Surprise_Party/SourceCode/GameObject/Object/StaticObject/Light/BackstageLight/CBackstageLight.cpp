#include "CBackstageLight.h"

/*******************************************
*		���䗠�̃��C�g�N���X.
************/
CBackstageLight::CBackstageLight()
{
	//�����������֐�.
	Init();
}

CBackstageLight::~CBackstageLight()
{
	//��������֐�.
	Release();
}

//=========================================.
//		�X�V�����֐�.
//=========================================.
void CBackstageLight::Update()
{

}

//=========================================.
//		�����������֐�.
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
//		��������֐�.
//=========================================.
void CBackstageLight::Release()
{

}