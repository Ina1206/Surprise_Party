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
//		カーソル動き処理関数.
//======================================.
void CGameWorldCursor::CursorUpDown()
{
	//加速度.
	m_fUpDownSpeed += ADD_SPEED * m_Direction;

	//それぞれの最大最小値になると変更.
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

	//距離計算.
	m_fUpDownDistance += m_fUpDownSpeed * m_Direction;
}

//===============================================.
//		透過値変更処理関数.
//===============================================.
void CGameWorldCursor::AlphaChange(bool flag)
{
	if (flag == true) {
		m_fAlpha = UNSELECTABLE_ALPHA;
		return;
	}
	m_fAlpha = ALPHA_MAX;
}