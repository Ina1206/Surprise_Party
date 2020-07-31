#include "CEndingStageBase.h"

/*******************************************
*		�G���f�B���O�X�e�[�W���N���X.
*****************/
CEndingStageBase::CEndingStageBase()
	: CEndingStageBase(0)
{

}

CEndingStageBase::CEndingStageBase(const int& EvaluationNum)
	: m_mView					()
	, m_mProj					()
	, m_pCBackstageLight		(nullptr)
	, m_pCGhost					(0)
	, m_pCCameraEnding			(nullptr)
	, m_pCWhiteScreenFade		(nullptr)
	, m_Evaluation				(EvaluationNum)
	, m_OldEvaluation			(INIT_EVALUATION_NUM)
	, m_bChangeStage			(false)
	, m_vObjLookPos				(0.0f, 0.0f, 0.0f)
	, m_UpdateFlag				(0)
	, m_bDisplayAllAtOnce		(false)
	, m_pCFloor					(nullptr)
	, m_pCPlaySoundManager		(nullptr)
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

	const D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);	//���(�x�N�g��).
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

	m_pCFloor->SetScale(SCALE);
	m_pCFloor->SetCameraPos(m_pCCameraEnding->GetPos());
	m_pCFloor->RenderInitSetting(m_mView, m_mProj, m_Light);
	m_pCFloor->SetPos(FLOOR_POS);
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
//		BGM�̉��ʂ�ݒ菈���֐�.
//=========================================.
void CEndingStageBase::SettingBGMVolume()
{
	m_BGMVolume = m_pCPlaySoundManager->VOLUME_MAX;
	//���ߒl��BGM�𒲐�.
	if (m_pCWhiteScreenFade->GetFadeFlag() != 0) {
		m_BGMVolume = static_cast<int>(m_pCWhiteScreenFade->GetAlphaRatio() * m_pCPlaySoundManager->VOLUME_MAX);
	}

	m_pCPlaySoundManager->SetPlayingBGMVolume(m_BGMVolume);
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

	//�ȍĐ��Ǘ��N���X.
	m_pCPlaySoundManager = CPlaySoundManager::GetPlaySoundManager();

	m_vObjLookPos = LOOK_POS;

	for (int ghost = 0; ghost < GHOST_MAX; ghost++) {
		//�N���X����C���X�^���X���쐬���鏈���֐�.
		CreateInstanceFronClass(ghost);

		const float			RADIAN	= static_cast<float>(D3DXToRadian(START_RADIAN + (ghost * RADIAN_WIDTH)));
		const D3DXVECTOR3	vPos	= (D3DXVECTOR3(cos(RADIAN), 0.0f, sin(RADIAN)) * POS_WIDTH) + D3DXVECTOR3(ADD_POS.x, ADD_POS.y + ((ghost % 2) * ADD_HIGHT), ADD_POS.z);

		m_pCGhost[ghost]->SetPos(vPos);
		m_pCGhost[ghost]->SetChangeBeforePos(vPos);
		//����ԍ�.
		const int m_EmotionType = static_cast<int>(CGhostBase::enEmotionType::ViewSmartphone);
		m_pCGhost[ghost]->SetEmotionNum(m_EmotionType);

		m_pCGhost[ghost]->SetLookAtPos(m_vObjLookPos);

		//��x�����X�V�������s��.
		m_pCGhost[ghost]->Update();
	}

}

//==========================================.
//	�N���X����C���X�^���X���쐬���鏈���֐�.
//==========================================.
void CEndingStageBase::CreateInstanceFronClass(const int& num)
{
	if (num == BIG_GHOST_NUM) {
		m_pCGhost.emplace_back(new CBigGhost());
		return;
	}

	if (num % WORK_GHOST_TYPE_MAX == 0) {
		m_pCGhost.emplace_back(new CEndingDispGhost());
		return;
	}
	m_pCGhost.emplace_back(new CEndingSwitchGhost());
	
}