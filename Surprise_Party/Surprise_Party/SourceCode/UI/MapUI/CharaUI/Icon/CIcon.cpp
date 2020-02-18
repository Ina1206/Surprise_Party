#include "CIcon.h"

CIcon::CIcon()
	: m_bSelectingFlag	(false)
{
	
}

CIcon::~CIcon()
{

}

//===================================.
//		選択中の表示処理関数.
//===================================.
void CIcon::SelectingDisplay()
{
	if (m_bSelectingFlag == true) {
		m_fScale = SELECTING_SCALE;
		m_fAlpha = SELECTION_ALPHA;
	}
	else {
		m_fScale = BASIC_SCALE;
		m_fAlpha = BASIC_ALPHA;
	}

	m_bSelectingFlag = false;
}