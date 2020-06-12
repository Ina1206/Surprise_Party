#include "CEndingStageBase.h"

/*******************************************
*		�G���f�B���O�X�e�[�W���N���X.
*****************/
CEndingStageBase::CEndingStageBase()
	: m_mView					()
	, m_mProj					()
	, m_pCBackstageLight		(nullptr)
	, m_pCGhost					(0)
	, m_pCCameraEnding			(nullptr)
	, m_pCWhiteScreenFade		(nullptr)
	, m_Evaluation				(0)
	, m_OldEvaluation			(INIT_EVALUATION_NUM)
	, m_bChangeStage			(false)
	, m_vObjLookPos				(0.0f, 0.0f, 0.0f)
	, m_pCFloor					(nullptr)
	, m_pCPushEnterUI			(nullptr)
	, m_fPushEnterUIAlpha		(0.0f)
	, m_AlphaAddDecDirect		(1)
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
		&m_pCCameraEnding->GetPos(), &m_pCCameraEnding->GetLook(), &vUpVec);
}

//=========================================.
//		���̕`�揈���֐�.
//=========================================.
void CEndingStageBase::RenderFloor()
{
	//���C�g���.
	const LIGHT m_Light = m_pCBackstageLight->GetLight();

	m_pCFloor->SetScale(0.5f);
	m_pCFloor->SetCameraPos(m_pCCameraEnding->GetPos());
	m_pCFloor->RenderInitSetting(m_mView, m_mProj, m_Light);
	m_pCFloor->SetPos(D3DXVECTOR3(0.0f, -6.0f, 0.0f));
	m_pCFloor->Render();

}

//=========================================.
//		�������`�揈���֐�.
//=========================================.
void CEndingStageBase::RenderGhost()
{
	//���C�g���.
	const LIGHT m_Light = m_pCBackstageLight->GetLight();

	for (unsigned int ghost = 0; ghost < m_pCGhost.size(); ghost++) {
		m_pCGhost[ghost]->RenderInitSetting(m_mView, m_mProj, m_Light);
		m_pCGhost[ghost]->SetCameraPos(m_pCCameraEnding->GetPos());
		m_pCGhost[ghost]->Render();
	}
}

//=========================================.
//		PushEnter�̍X�V�����֐�.
//=========================================.
void CEndingStageBase::UpdatePushEnter()
{
	m_fPushEnterUIAlpha += 0.05f * m_AlphaAddDecDirect;

	if (m_fPushEnterUIAlpha > ALPHA_MAX) {
		m_fPushEnterUIAlpha = ALPHA_MAX;
		m_AlphaAddDecDirect *= -1;
		return;
	}

	if (m_fPushEnterUIAlpha < ALPHA_MIN) {
		m_fPushEnterUIAlpha = ALPHA_MIN;
		m_AlphaAddDecDirect *= -1;
	}
	
}

//=========================================.
//		���ʒl�̏����������֐�.
//=========================================.
void CEndingStageBase::InitCommonValue()
{
	//�C���X�^���X��.
	m_pCFloor.reset(new CFloor());
	m_pCBackstageLight.reset(new CBackstageLight());
	m_pCCameraEnding.reset(new CCameraEnding());
	m_pCWhiteScreenFade.reset(new CWhiteScreenFade());

	m_vObjLookPos = D3DXVECTOR3(5.0f, 1.5f, 8.0f);

	for (int ghost = 0; ghost < 5; ghost++) {
		//�N���X����C���X�^���X���쐬���鏈���֐�.
		CreateInstanceFronClass(ghost);

		const float			RADIAN	= static_cast<float>(D3DXToRadian(-7.0f + (ghost * 55.0f)));
		const D3DXVECTOR3	vPos	= (D3DXVECTOR3(cos(RADIAN), 0.0f, sin(RADIAN)) * 2.5f) + D3DXVECTOR3(5.0f, 1.5f + ((ghost % 2) * 0.5f), 8.0f);

		m_pCGhost[ghost]->SetPos(vPos);
		m_pCGhost[ghost]->SetChangeBeforePos(vPos);
		//����ԍ�.
		const int m_EmotionType = static_cast<int>(CGhostBase::enEmotionType::ViewSmartphone);
		m_pCGhost[ghost]->SetEmotionNum(m_EmotionType);

		m_pCGhost[ghost]->SetLookAtPos(m_vObjLookPos);
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

	if (num % 2 == 0) {
		m_pCGhost.emplace_back(new CEndingDispGhost());
		return;
	}
	m_pCGhost.emplace_back(new CEndingSwitchGhost());
	
}