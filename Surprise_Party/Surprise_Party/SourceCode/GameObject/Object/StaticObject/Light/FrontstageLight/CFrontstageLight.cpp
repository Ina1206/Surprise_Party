#include "CFrontstageLight.h"

/*********************************
*		�\����̃��C�g�N���X.
*************/
CFrontstageLight::CFrontstageLight()
	: m_vLightPos			()
	, m_vCameraPos			(0.0f, 0.0f, 0.0f)
{
	//�����������֐�.
	Init();
}

CFrontstageLight::~CFrontstageLight()
{
	//��������֐�.
	Release();
}

//=======================================.
//		�X�V�����֐�.
//=======================================.
void CFrontstageLight::Update()
{
	for (unsigned int light = 0; light < m_vLightPos.size(); light++) {
		if (m_vCameraPos.x + 16.0f > m_vLightPos[light].x &&
			m_vCameraPos.x - 16.0f < m_vLightPos[light].x) {
			m_stLight.vPos = m_vLightPos[light];
			break;
		}
	}
}

//=======================================.
//		�S�Ẵ��C�g�̍��W�ݒ菈���֐�.
//=======================================.
void CFrontstageLight::SettingAllLightPos(const float& fDistance)
{
	//���C�g�̔z�u����.
	float m_LightWidth = m_stLight.fLightPosWidth;
	for (int Light = 0; m_LightWidth * Light <= fDistance; Light++) {
		D3DXVECTOR3 vLightPos = m_stLight.vPos;
		vLightPos.x = m_LightWidth * Light;
		m_vLightPos.push_back(vLightPos);
	}

}

//=======================================.
//		�����������֐�.
//=======================================.
void CFrontstageLight::Init()
{
	//���C�g��񏉊��ݒ�.
	m_stLight.vPos				= D3DXVECTOR3(0.0f, 21.7f, -0.5f);
	m_stLight.fIntensity		= 119.0f;
	m_stLight.m_fLightWidth		= 10.9f;
	m_stLight.fLightPosWidth	= 20.0f;
	m_stLight.vLightColor		= D3DXVECTOR3(0.5f, 0.5f, 1.0f);
	m_stLight.m_fLightMax		= 3.0f;
	D3DXMatrixIdentity(&m_stLight.mRot);

	D3DXMATRIX mYaw, mPich, mRoll;
	D3DXMatrixRotationY(&mYaw, 0.0f);
	D3DXMatrixRotationX(&mPich, 0.0f);
	D3DXMatrixRotationZ(&mRoll, 0.0f);
	m_stLight.mRot = mYaw * mPich * mRoll;


}

//=======================================.
//		��������֐�.
//=======================================.
void CFrontstageLight::Release()
{

}