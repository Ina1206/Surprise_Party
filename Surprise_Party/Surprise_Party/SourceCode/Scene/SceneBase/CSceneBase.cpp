#include "CSceneBase.h"

CSceneBase::CSceneBase()
	: m_mView		()
	, m_mProj		()
	, m_vLightPos	(0.0f, 0.0f, 0.0f)
	, m_vCameraPos	(0.0f, 0.0f, 0.0f)
	, m_vBackColor	(0.0f, 0.0f, 0.0f, 0.0f)
	, m_bChangeScene(false)
	, m_bPauseFlag	(false)
{

}

CSceneBase::~CSceneBase()
{

}

//===========================================.
//		�`�揉���ݒ菈���֐�.
//===========================================.
void CSceneBase::RenderInitSetting(const D3DXMATRIX& mProj)
{
	m_mProj			= mProj;
}

//===========================================.
//		�f�o�b�O�p�V�[���ύX�����֐�.
//===========================================.
void CSceneBase::DebugSceneChange()
{
	if (GetAsyncKeyState('A') & 0x8000) {
		m_bChangeScene = true;
	}
}