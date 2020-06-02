#include "CEndingStageBase.h"

/*******************************************
*		�G���f�B���O�X�e�[�W���N���X.
*****************/
CEndingStageBase::CEndingStageBase()
	: m_mView					()
	, m_mProj					()
	, m_Camera					()
	, m_pCBackstageLight		(nullptr)
	, m_pCBigGhost				(nullptr)
	, m_pCEndingWorkGhostBase	(0)
	, m_pCGhost					(0)
	, m_pCFloor					(nullptr)
{
	//���ʂ̒l�̏����������֐�.
	InitCommonValue();
}

CEndingStageBase::~CEndingStageBase()
{

}

//=========================================.
//		�`�揉���������֐�.
//=========================================.
void CEndingStageBase::RenderInitSetting( const D3DXMATRIX& mProj)
{
	m_mProj = mProj;

	D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);	//���(�x�N�g��).
	D3DXMatrixLookAtLH(
		&m_mView,								//(out)�r���[�v�Z����.
		&m_Camera.vPos, &m_Camera.vLook, &vUpVec);
}

//=========================================.
//		���̕`�揈���֐�.
//=========================================.
void CEndingStageBase::RenderFloor()
{
	//���C�g���.
	const LIGHT m_Light = m_pCBackstageLight->GetLight();

	m_pCFloor->SetScale(0.5f);
	m_pCFloor->SetCameraPos(m_Camera.vPos);
	m_pCFloor->RenderInitSetting(m_mView, m_mProj, m_Light);
	m_pCFloor->SetPos(D3DXVECTOR3(0.0f, -6.0f, 0.0f));
	m_pCFloor->Render();

}

//=========================================.
//		�r�b�O�S�[�X�g�`�揈���֐�.
//=========================================.
void CEndingStageBase::RenderBigGhost()
{
	//���C�g���.
	const LIGHT m_Light = m_pCBackstageLight->GetLight();

	m_pCBigGhost->SetCameraPos(m_Camera.vPos);
	m_pCBigGhost->RenderInitSetting(m_mView, m_mProj, m_Light);
	m_pCBigGhost->Render();
}

//=========================================.
//		�����������`�揈���֐�.
//=========================================.
void CEndingStageBase::RenderWorkGhost()
{
	//���C�g���.
	const LIGHT m_Light = m_pCBackstageLight->GetLight();

	for (unsigned int ghost = 0; ghost < m_pCEndingWorkGhostBase.size(); ghost++) {
		m_pCEndingWorkGhostBase[ghost]->RenderInitSetting(m_mView, m_mProj, m_Light);
	}
}

//=========================================.
//		�������`�揈���֐�.
//=========================================.
void CEndingStageBase::RenderGhost()
{
	//���C�g���.
	const LIGHT m_Light = m_pCBackstageLight->GetLight();

	for (unsigned int ghost = 0; ghost < m_pCEndingWorkGhostBase.size(); ghost++) {
		m_pCGhost[ghost]->RenderInitSetting(m_mView, m_mProj, m_Light);
		m_pCGhost[ghost]->SetCameraPos(m_Camera.vPos);
		m_pCGhost[ghost]->Render();
	}
}

//=========================================.
//		���ʒl�̏����������֐�.
//=========================================.
void CEndingStageBase::InitCommonValue()
{
	//�C���X�^���X��.
	m_pCBigGhost.reset(new CBigGhost());
	m_pCFloor.reset(new CFloor());
	m_pCBackstageLight.reset(new CBackstageLight());

	for (int ghost = 0; ghost < 5; ghost++) {
		m_pCEndingWorkGhostBase.emplace_back(new CEndingDispGhost());
	}
	for (int ghost = 0; ghost < 5; ghost++) {
		//�N���X����C���X�^���X���쐬���鏈���֐�.
		CreateInstanceFronClass(ghost);

		const float			RADIAN	= static_cast<float>(D3DXToRadian(-57.5 + (ghost * 50.0f)));
		const D3DXVECTOR3	vPos	= (D3DXVECTOR3(cos(RADIAN), 0.0f, sin(RADIAN)) * 3.0f) + D3DXVECTOR3(5.0f, -0.8f, 5.0f);
		m_pCGhost[ghost]->SetPos(vPos);

		//����ԍ�.
		const int m_EmotionType = static_cast<int>(CGhostBase::enEmotionType::ViewSmartphone);
		m_pCGhost[ghost]->SetEmotionNum(m_EmotionType);
	}
}

//==========================================.
//	�N���X����C���X�^���X���쐬���鏈���֐�.
//==========================================.
void CEndingStageBase::CreateInstanceFronClass(const int& num)
{
	if (num == 2) {
		m_pCGhost.emplace_back(new CBigGhost());
		return;
	}
	m_pCGhost.emplace_back(new CEndingDispGhost());
}