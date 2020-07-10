#include "CPuaseUI.h"

/**************************************
*		�|�[�YUI�̃N���X.
****************/
CPauseUI::CPauseUI()
{
	//�����������֐�.
	Init();
}

CPauseUI::~CPauseUI()
{

}

//=====================================.
//		�X�V�����֐�.
//=====================================.
void CPauseUI::Update()
{
	//�J�[�\���̍X�V�����֐�.
	m_pCCursor->SetChangeWaitFlag(true);
	m_pCCursor->SetControlFlag(true);
	m_pCCursor->Update();

	//�I�����̍X�V�����֐�.
	m_pCSelectStringUI->SetMoveFlag(m_pCSelectStringUI->CONTROL_FLAG);
	m_pCSelectStringUI->Update();
}

//=====================================.
//		�����������֐�.
//=====================================.
void CPauseUI::Init()
{
	//�V�[���^�C�g��.
	m_pCSpriteUI = m_pCResourceManager->GetSpriteUI(enSpriteUI::Pause);

	//�I����UI�N���X�C���X�^���X��.
	m_pCSelectStringUI.reset(new CSelectStringUI(false));
}

//====================================.
//		�V�[���^�C�g���`�揈���֐�.
//====================================.
void CPauseUI::RenderSceneTitle()
{
	m_pCSpriteUI->SetPosition(PAUSE_POS);
	m_pCSpriteUI->Render();
}