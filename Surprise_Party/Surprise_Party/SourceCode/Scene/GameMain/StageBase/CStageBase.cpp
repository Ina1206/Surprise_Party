#include "CStageBase.h"

CStageBase::CStageBase()
	: m_mView			()
	, m_mProj			()
	, m_Camera			()
	, m_bChangeStageFlag(false)
	, m_StageNum		(0)
	, m_enBeforeStageEndingType()
	, m_FinishFlag		(0)
	, m_TutorialFlag	(false)
{

}

CStageBase::~CStageBase()
{

}

//==========================================.
//		�`�揉���ݒ菈���֐�.
//==========================================.
void CStageBase::RenderInitSetting(const D3DXMATRIX& mView, const D3DXMATRIX& mProj, const D3DXVECTOR3& vCameraPos)
{
	m_mView			= mView;
	m_mProj			= mProj;
	//m_vCameraPos	= vCameraPos;

	D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);	//���(�x�N�g��).
	D3DXMatrixLookAtLH(
		&m_mView,								//(out)�r���[�v�Z����.
		&m_Camera.vPos, &m_Camera.vLook, &vUpVec);
}

//==========================================.
//		�f�o�b�O�p�X�e�[�W�ύX�����֐�.
//==========================================.
void CStageBase::DebugStageChange()
{
	if (GetAsyncKeyState(VK_SPACE) & 0x0001) {
		m_bChangeStageFlag = true;
	}
}