#include "CGameGhostCursor.h"

/*********************************************
*	�Q�[�����̂������̃J�[�\���N���X.
*************/
CGameGhostCursor::CGameGhostCursor()
	: m_bRestFlag	(false)
{
	//�����������֐�.
	Init();
}

CGameGhostCursor::~CGameGhostCursor()
{
	//��������֐�.
	Release();
}

//=========================================.
//		�X�V�����֐�.
//=========================================.
void CGameGhostCursor::UpDate()
{
	//�J�[�\���㉺���������֐�.
	CursorUpDown();

	m_vPos = m_vCharacterPos;
	m_vPos.y = CURSOL_BASE_HIGHT + m_fUpDownDistance;

	//���ߒl�ύX�����֐�.
	AlphaChange(m_bRestFlag);
}

//=========================================.
//		�����������֐�.
//=========================================.
void CGameGhostCursor::Init()
{
	m_pCSprite = m_pCResourceManager->GetSprite(enSprite::Cursol);
	m_fScale = SCALE;
}

//=========================================.
//		��������֐�.
//=========================================.
void CGameGhostCursor::Release()
{
	m_pCSprite = nullptr;
}