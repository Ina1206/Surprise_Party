#include "CGameWorldCursor.h"

CGameWorldCursor::CGameWorldCursor()
	: m_fUpDownDistance	(0.0f)
	, m_enUpDownType	(enUpDownType::Down)
	, m_fUpDownSpeed	(0.0f)
	, m_Direction		(CHANGE_DIRECTION)
{

}

CGameWorldCursor::~CGameWorldCursor()
{

}

//======================================.
//		�J�[�\�����������֐�.
//======================================.
void CGameWorldCursor::CursorUpDown()
{
	//�����x.
	m_fUpDownSpeed += ADD_SPEED * m_Direction;

	//���ꂼ��̍ő�ŏ��l�ɂȂ�ƕύX.
	switch (m_enUpDownType) {
	case enUpDownType::Up:

		if (m_fUpDownDistance > MOVE_DISTANCE_MAX) {
			m_enUpDownType = enUpDownType::Down;
			m_Direction *= CHANGE_DIRECTION;
			m_fUpDownSpeed = 0.0f;
		}

		break;
	case enUpDownType::Down:

		if (m_fUpDownDistance < MOVE_DISTANCE_MIN) {
			m_enUpDownType = enUpDownType::Up;
			m_Direction *= CHANGE_DIRECTION;
		}

		break;
	}

	//�����v�Z.
	m_fUpDownDistance += m_fUpDownSpeed * m_Direction;
}

//===============================================.
//		���ߒl�ύX�����֐�.
//===============================================.
void CGameWorldCursor::AlphaChange(bool flag)
{
	if (flag == true) {
		m_fAlpha = UNSELECTABLE_ALPHA;
		return;
	}
	m_fAlpha = ALPHA_MAX;
}