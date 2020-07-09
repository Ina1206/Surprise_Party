#include "CTitleUI.h"

/*************************************
*		�^�C�g��UI�N���X.
****************/
CTitleUI::CTitleUI()
	: m_SelectTypeFlag	(0)
{
	//�����������֐�.
	Init();
}

CTitleUI::~CTitleUI()
{

}

//=====================================.
//		�X�V�����֐�.
//=====================================.
void CTitleUI::Update()
{
	//���쏈���֐�.
	Control(false);
}

//=====================================.
//		�I����ރt���O�擾�����֐�.
//=====================================.
unsigned int CTitleUI::GetSelectTypeFlag() const 
{
	if (m_bSelectFinishFlag == false) {
		return 0;
	}

	//�Q�[���J�n.
	if (m_SelectNum == 0) {
		return GAME_START_FLAG;
	}

	//�Q�[���I��.
	return GAME_FINISH_FLAG;
}

//=====================================.
//		�����������֐�.
//=====================================.
void CTitleUI::Init()
{
	for (int spriteNum = 0; spriteNum < SELECT_STRING_MAX; spriteNum++) {
		int StartString = static_cast<int>(enSpriteUI::StartString);
		enSpriteUI m_enSpriteUI = static_cast<enSpriteUI>(StartString + spriteNum);

		m_pCSpriteUI[spriteNum] = m_pCResourceManager->GetSpriteUI(m_enSpriteUI);
	}
	m_pCSpriteUI[SCENE_TITLE_NUM] = m_pCResourceManager->GetSpriteUI(enSpriteUI::Title);
}