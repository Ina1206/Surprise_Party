#include "CGameGimmickCursor.h"

/***********************************
*		�M�~�b�N�J�[�\���N���X.
********/
CGameGimmickCursor::CGameGimmickCursor()
	: m_bUnSelectableFlag	(false)
{
	//�����������֐�.
	Init();
}

CGameGimmickCursor::~CGameGimmickCursor()
{
	//��������֐�.
	Release();
}

//=====================================.
//		�X�V�����֐�.
//=====================================.
void CGameGimmickCursor::UpDate()
{
	//�J�[�\���㉺����.
	CursorUpDown();

	m_vPos = m_vCharacterPos;
	m_vPos.z = ADJUST_HEIGHT;
	m_vPos.y = ADJUST_WIDTH + m_fUpDownDistance;

	//���ߒl�ύX�����֐�.
	AlphaChange(m_bUnSelectableFlag);
}

//======================================.
//		�����������֐�.
//======================================.
void CGameGimmickCursor::Init()
{
	m_pCSprite = m_pCResourceManager->GetSprite(enSprite::Cursol);
	m_fScale = SCALE;
	m_vColor = COLOR;
}

//======================================.
//		��������֐�.
//======================================.
void CGameGimmickCursor::Release()
{

}