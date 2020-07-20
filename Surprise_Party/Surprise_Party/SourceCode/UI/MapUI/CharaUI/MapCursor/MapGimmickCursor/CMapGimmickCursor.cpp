#include "CMapGimmickCursor.h"

/****************************************
*	�}�b�v��̃M�~�b�N�p�J�[�\���N���X.
********/
CMapGimmickCursor::CMapGimmickCursor()
{
	//�����������֐�.
	Init();
}

CMapGimmickCursor::~CMapGimmickCursor()
{
	//��������֐�.
	Release();
}

//============================================.
//		�X�V�����֐�.
//============================================.
void CMapGimmickCursor::UpDate()
{
	//�Q�[��������}�b�v���ɍ��W�ϊ������֐�.
	GameMapConversion();
	m_vPos.y = CURSOR_HEIGHT;
	m_vPos -= CURSOR_UI_ADJUSTMENT;
}

//============================================.
//		�����������֐�.
//============================================.
void CMapGimmickCursor::Init()
{
	//�A�h���X�擾.
	m_pCSpriteUI = m_pCResourceManager->GetSpriteUI(enSpriteUI::DispGimmick_Iccon);

	//�傫��.
	m_fScale = SCALE;
	//�F.
	m_vColor = COLOR;
}

//============================================.
//		��������֐�.
//============================================.
void CMapGimmickCursor::Release()
{
	m_pCSpriteUI = nullptr;
}