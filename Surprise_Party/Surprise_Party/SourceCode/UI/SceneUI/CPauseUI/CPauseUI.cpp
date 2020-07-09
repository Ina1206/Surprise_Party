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
	//���쏈���֐�.
	Control(true);
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

	//�J�[�\�������ݒ菈���֐�.
	InitCursor();
	//�J�[�\���ԍ�.
	const int CURSOR_NUM = static_cast<int>(m_pCSpriteUI.size()) - 1;
	m_vUIPos[CURSOR_NUM] = CURSOR_POS;
}