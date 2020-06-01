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
	m_stLight.fIntensity		= 27.0f;
	m_stLight.fLightPosWidth	= 20.0f;
	m_stLight.m_fLightWidth		= 6.2f;
	m_stLight.m_fLightMax		= 1.0f;
	m_stLight.vLightColor		= D3DXVECTOR3(243.0f, 232.0f, 12.0f) / 255.0f;
	m_stLight.vPos				= D3DXVECTOR3(26.2f, 11.7f, 6.7f);
	D3DXMatrixRotationYawPitchRoll(&m_stLight.mRot, 0.0f, 0.0f, 0.0f);
}

//=========================================.
//		��������֐�.
//=========================================.
void CBackstageLight::Release()
{

}