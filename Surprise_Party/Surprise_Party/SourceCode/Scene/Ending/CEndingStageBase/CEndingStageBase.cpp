#include "CEndingStageBase.h"

/*******************************************
*		�G���f�B���O�X�e�[�W���N���X.
*****************/
CEndingStageBase::CEndingStageBase()
	: m_mView				()
	, m_mProj				()
	, m_Camera				()
	, m_pCBigGhost			(nullptr)
	, m_pCBackstageLight	(nullptr)
	, m_pCFloor				(nullptr)
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
void CEndingStageBase::RenderInitSetting(const D3DXMATRIX& mView, const D3DXMATRIX& mProj)
{
	m_mView = mView;
	m_mProj = mProj;
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
//		���ʒl�̏����������֐�.
//=========================================.
void CEndingStageBase::InitCommonValue()
{
	//�C���X�^���X��.
	m_pCBigGhost.reset(new CBigGhost());
	m_pCFloor.reset(new CFloor());
	m_pCBackstageLight.reset(new CBackstageLight());
}