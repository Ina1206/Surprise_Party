#include "CTitle.h"

/**********************************
*		�^�C�g���N���X.
******/
CTitle::CTitle()
	: m_pCCameraTitle			(nullptr)
	, m_pCFrontstageLight		(nullptr)
	, m_pCStaticObjectManager	(nullptr)
	, m_pCMoveObjectManager		(nullptr)
	, m_pCWorkGhostManager		(nullptr)
	, m_pCTitleUI				(nullptr)
{
	//�����������֐�.
	Init();
}

CTitle::~CTitle()
{
	//��������֐�.
	Release();
}

//======================================.
//		�X�V�����֐�.
//======================================.
void CTitle::UpDate()
{
	//�^�C�g���p�J�����̍X�V�����֐�.
	m_pCCameraTitle->Update();
	//�J�������W.
	const D3DXVECTOR3 m_vCameraPos = m_pCCameraTitle->GetPos();

	//���C�g�X�V�����֐�.
	m_pCFrontstageLight->SetCameraPos(m_vCameraPos);
	m_pCFrontstageLight->Update();

	//�ÓI�I�u�W�F�N�g�̍X�V�����֐�.
	m_pCStaticObjectManager->SetCameraPos(m_vCameraPos);
	m_pCStaticObjectManager->Updata();

	//���I�I�u�W�F�N�g�̍X�V�����֐�.
	m_pCMoveObjectManager->SetCameraPos(m_vCameraPos);
	m_pCMoveObjectManager->UpDate();

	//�������X�V�����֐�.
	m_pCWorkGhostManager->Update();

	//�^�C�g��UI�X�V�����֐�.
	m_pCTitleUI->Update();
}

//======================================.
//		�`�揈���֐�.
//======================================.
void CTitle::Render()
{
	//�J�������W.
	const D3DXVECTOR3 m_vCameraPos = m_pCCameraTitle->GetPos();
	//���C�g���.
	const LIGHT	m_Light = m_pCFrontstageLight->GetLight();

	//�r���[�s��̐ݒ菈���֐�.
	SettingView();

	//�������̕`�揈���֐�.
	m_pCWorkGhostManager->Render(m_mView, m_mProj, m_Light, m_vCameraPos);
	//�X�C�b�`�̕`�揈���֐�.
	m_pCMoveObjectManager->RenderSwitch(m_mView, m_mProj, m_Light);
	//�ÓI�I�u�W�F�N�g�̕`�揈���֐�.
	m_pCStaticObjectManager->Render(m_mView, m_mProj, m_vCameraPos, m_Light);
	//���I�I�u�W�F�N�g�̕`�揈���֐�.
	m_pCMoveObjectManager->Render(m_mView, m_mProj, m_Light);
	//���I�I�u�W�F�N�g�O�G�t�F�N�g�̕`�揈���֐�.
	m_pCMoveObjectManager->EffectRender();

	//�^�C�g��UI�`�揈���֐�.
	m_pCTitleUI->Render();
}

//======================================.
//		�����������֐�.
//======================================.
void CTitle::Init()
{
	const int FILE_NUM = 0;	//�t�@�C���ԍ�.
	const int STAGE_NUM = 0;//�X�e�[�W�ԍ�.

	//�N���X���C���X�^���X��.
	m_pCCameraTitle.reset(new CCameraTitle());
	m_pCFrontstageLight.reset(new CFrontstageLight());
	m_pCStaticObjectManager.reset(new CStaticObjectManager(FILE_NUM, STAGE_NUM));
	m_pCMoveObjectManager.reset(new CMoveObjectManager(FILE_NUM, STAGE_NUM));
	m_pCWorkGhostManager.reset(new CMainStageWorkGhostManager());
	m_pCTitleUI.reset(new CTitleUI());

	//���������֐�.
	m_pCWorkGhostManager->Init(6, STAGE_NUM, m_pCStaticObjectManager->OBJECT_WIDTH);

	//�X�e�[�W�̍ő�l.
	const float m_fStageDistanceMax = m_pCStaticObjectManager->GetStageDistanceMax();

	//�X�e�[�W�̍ő�l�ݒ�.
	m_pCFrontstageLight->SettingAllLightPos(m_fStageDistanceMax);

	//UI��`�悳���Ȃ�.
	m_pCMoveObjectManager->SetRenderUI(false);
}

//======================================.
//		��������֐�.
//======================================.
void CTitle::Release()
{

}

//=======================================.
//		�r���[�s��̐ݒ菈���֐�.
//=======================================.
void CTitle::SettingView()
{
	const D3DXVECTOR3 m_vCameraLook = m_pCCameraTitle->GetLook();
	const D3DXVECTOR3 m_vCameraPos = m_pCCameraTitle->GetPos();

	const D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);	//���(�x�N�g��).
	D3DXMatrixLookAtLH(
		&m_mView,								//(out)�r���[�v�Z����.
		&m_vCameraPos, &m_vCameraLook, &vUpVec);
}