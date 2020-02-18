#include "CMapGimmickCursor.h"

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
	m_vPos.y = 60.0f;
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
	m_fScale = 1.3f;
	//�F.
	m_vColor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
}

//============================================.
//		��������֐�.
//============================================.
void CMapGimmickCursor::Release()
{
	m_pCSpriteUI = nullptr;
}