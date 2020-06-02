#include "CEndingStageBase.h"

/*******************************************
*		�G���f�B���O�X�e�[�W���N���X.
*****************/
CEndingStageBase::CEndingStageBase()
	: m_pCBigGhost			(nullptr)
	, m_pCFloor				(nullptr)
	, m_pCBackstageLight	(nullptr)
{
	//���ʂ̒l�̏����������֐�.
	InitCommonValue();
}

CEndingStageBase::~CEndingStageBase()
{

}

//=========================================.
//		���̕`�揈���֐�.
//=========================================.
void CEndingStageBase::RenderFloor()
{
	m_pCFloor->SetScale(0.5f);
	m_pCFloor->SetCameraPos(m_Camera.vPos);
	m_pCFloor->RenderInitSetting(m_mView, m_mProj, m_Light);
	m_pCFloor->SetPos(D3DXVECTOR3(0.0f, -6.0f, 0.0f));
	m_pCFloor->Render();

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