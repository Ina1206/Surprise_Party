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
}

//=====================================.
//		�����������֐�.
//=====================================.
void CPauseUI::Init()
{
	//�X�v���C�g�ݒ�.
	for (int sprite = 0; sprite < SELECT_STRING_MAX; sprite++) {
		//�I�𕶏�.
		int SpriteNum = static_cast<int>(enSpriteUI::Continue) + sprite;
		m_pCSpriteUI.emplace_back(m_pCResourceManager->GetSpriteUI(static_cast<enSpriteUI>(SpriteNum)));
	}
	//�V�[���^�C�g��.
	m_pCSpriteUI.emplace_back(m_pCResourceManager->GetSpriteUI(enSpriteUI::Pause));

	//�v�f�������������֐�.
	InitElementCounts();

	//���쎞�I�����W�ݒ菈���֐�.
	ControlSelectStringPos();
}