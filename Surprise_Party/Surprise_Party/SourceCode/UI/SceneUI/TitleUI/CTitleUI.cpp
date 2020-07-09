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
	ControlTitlePos();

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
	//�I����.
	for (int spriteNum = 0; spriteNum < SELECT_STRING_MAX; spriteNum++) {
		const int StartString = static_cast<int>(enSpriteUI::StartString);
		const enSpriteUI m_enSpriteUI = static_cast<enSpriteUI>(StartString + spriteNum);

		m_pCSpriteUI.emplace_back(m_pCResourceManager->GetSpriteUI(m_enSpriteUI));
	}

	//�^�C�g��.
	for (int title = 0; title < TITLE_MAX; title++) {
		m_pCSpriteUI.emplace_back(m_pCResourceManager->GetSpriteUI(enSpriteUI::Title));
	}

	//�v�f�������������֐�.
	InitElementCounts();

	//���쎞�I�𕶏͍��W�ݒ菈���֐�.
	ControlSelectStringPos();

	//�J�[�\�������ݒ���W�����֐�.
	InitCursor();
	//�J�[�\���ԍ�.
	const int CURSOR_NUM = static_cast<int>(m_pCSpriteUI.size()) - 1;
	m_vUIPos[CURSOR_NUM] = CURSOR_POS;

	//�^�C�g��.
	for (int title = 0; title < TITLE_MAX; title++) {
		const int TitleNum = title + SELECT_STRING_MAX;
		D3DXVECTOR2 TitleUV = INIT_UV;
		TitleUV.y += 1.0f * title;
		m_vUV[TitleNum] = TitleUV;

	}
}

//=======================================.
//		���쎞�^�C�g�����W�ݒ菈���֐�.
//=======================================.
void CTitleUI::ControlTitlePos()
{
	static D3DXVECTOR3 a(0.0f, 0.0f, 0.0f);

	if (GetAsyncKeyState('L') & 0x8000) {
		a.x += 2.1f;
	}
	if (GetAsyncKeyState('J') & 0x8000) {
		a.x -= 2.1f;
	}
	if (GetAsyncKeyState('I') & 0x8000) {
		a.y += 2.1f;
	}
	if (GetAsyncKeyState('K') & 0x8000) {
		a.y -= 2.1f;
	}

	//�^�C�g���ԍ�.
	const int TitleStartNum = SELECT_STRING_MAX;
	for (int title = 0; title < TITLE_MAX; title++) {
		const int TitleNum = title + TitleStartNum;
		D3DXVECTOR3 vPos = D3DXVECTOR3(100.0f, 200.0f, 0.0f) + a;
		SPRITE_STATE ss = m_pCResourceManager->GetSpriteUIState(enSpriteUI::Title);
		vPos.x += ss.Stride.w * title;
		m_vUIPos[TitleNum] = vPos;
	}
}