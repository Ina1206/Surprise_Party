#include "CTitleUI.h"

/*************************************
*		�^�C�g��UI�N���X.
****************/
CTitleUI::CTitleUI()
	: m_SelectTypeFlag	(0)
	, m_ControlFlag		(0)
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
		const int StartString = static_cast<int>(enSpriteUI::StartString);
		const enSpriteUI m_enSpriteUI = static_cast<enSpriteUI>(StartString + spriteNum);

		m_pCSpriteUI.emplace_back(m_pCResourceManager->GetSpriteUI(m_enSpriteUI));
	}
	m_pCSpriteUI.emplace_back(m_pCResourceManager->GetSpriteUI(enSpriteUI::Title));

	//�v�f�������������֐�.
	InitElementCounts();

	//���쎞�I�𕶏͍��W�ݒ菈���֐�.
	ControlSelectStringPos();

	//�J�[�\�������ݒ���W�����֐�.
	InitCursor();
}