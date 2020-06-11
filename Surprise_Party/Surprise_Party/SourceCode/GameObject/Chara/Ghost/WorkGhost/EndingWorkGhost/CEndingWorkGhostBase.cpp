#include "CEndingWorkGhostBase.h"

/**************************************************
*		�G���f�B���O�������������N���X.
********************/
CEndingWorkGhostBase::CEndingWorkGhostBase()
	: m_fAcc	(0.0f)
{

}

CEndingWorkGhostBase::~CEndingWorkGhostBase()
{

}

//==========================================.
//		�W�����v�����֐�.
//==========================================.
void CEndingWorkGhostBase::Jump()
{
	m_fAcc -= m_fAccSpeed;
	m_vPos.y += m_fAcc - m_fGravity;


	if (m_vPos.y < m_vChangeBeforePos.y) {
		m_vPos.y = m_vChangeBeforePos.y;
		m_fAcc = m_fAccMax;
	}
}