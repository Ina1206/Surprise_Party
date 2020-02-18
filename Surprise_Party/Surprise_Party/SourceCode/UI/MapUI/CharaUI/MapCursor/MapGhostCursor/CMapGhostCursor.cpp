#include "CMapGhostCursor.h"

CMapGhostCursor::CMapGhostCursor()
{
	//�����������֐�.
	Init();
}

CMapGhostCursor::~CMapGhostCursor()
{
	//��������֐�.
	Release();
}

//=======================================.
//		�X�V�����֐�.
//=======================================.
void CMapGhostCursor::UpDate()
{
	//�Q�[��������}�b�v���ɍ��W�ϊ������֐�.
	GameMapConversion();
	m_vPos.y = 0.0f;
	m_vPos -= CURSOR_UI_ADJUSTMENT;
}

//=======================================.
//		�����������֐�.
//=======================================.
void CMapGhostCursor::Init()
{
	//�ǂݍ��񂾃e�N�X�`���̃A�h���X�擾.
	m_pCSpriteUI = m_pCResourceManager->GetSpriteUI(enSpriteUI::Ghost_Icon);

	//�傫���ݒ�.
	m_fScale = 1.3f;
	//�F�ݒ�.
	m_vColor = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
}

//=======================================.
//		��������֐�.
//=======================================.
void CMapGhostCursor::Release()
{
	m_pCSpriteUI = nullptr;
}