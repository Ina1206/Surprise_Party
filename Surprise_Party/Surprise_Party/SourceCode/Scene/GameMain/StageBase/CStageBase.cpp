#include "CStageBase.h"

/*****************************************
*		�X�e�[�W���N���X.
********/
CStageBase::CStageBase()
	: m_mView					()
	, m_mProj					()
	, m_bChangeStageFlag		(false)
	, m_StageNum				(0)
	, m_enBeforeStageEndingType	()
	, m_FinishFlag				(0)
	, m_TutorialFlag			(false)
	, m_pCCamera				(nullptr)
	, m_bPauseFlag				(false)
	, m_pCPlaySoundManager		(CPlaySoundManager::GetPlaySoundManager())
{

}

CStageBase::~CStageBase()
{

}

//==========================================.
//		�`�揉���ݒ菈���֐�.
//==========================================.
void CStageBase::RenderInitSetting(const D3DXMATRIX& mView, const D3DXMATRIX& mProj)
{
	m_mView			= mView;
	m_mProj			= mProj;

	const D3DXVECTOR3 m_vCameraLook = m_pCCamera->GetLook();
	const D3DXVECTOR3 m_vCameraPos = m_pCCamera->GetPos();

	const D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);	//���(�x�N�g��).
	D3DXMatrixLookAtLH(
		&m_mView,								//(out)�r���[�v�Z����.
		&m_vCameraPos, &m_vCameraLook, &vUpVec);
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