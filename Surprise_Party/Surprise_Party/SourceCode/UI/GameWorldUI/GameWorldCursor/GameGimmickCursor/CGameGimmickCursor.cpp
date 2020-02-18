#include "CGameGimmickCursor.h"

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
	m_vPos.z = -3.0f;
	m_vPos.y = 4.0f + m_fUpDownDistance;

	//���ߒl�ύX�����֐�.
	AlphaChange(m_bUnSelectableFlag);
}

//======================================.
//		�����������֐�.
//======================================.
void CGameGimmickCursor::Init()
{
	m_pCSprite = m_pCResourceManager->GetSprite(enSprite::Cursol);
	m_fScale = 2.5f;
	m_vColor = D3DXVECTOR3(0.5f, 1.0f, 0.5f);
}

//======================================.
//		��������֐�.
//======================================.
void CGameGimmickCursor::Release()
{

}